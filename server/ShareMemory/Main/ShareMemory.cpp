#include "stdafx.h"
#include "ShareMemory.h"
#include "Log.h"
#include "Config.h"
#include "TimeManager.h"
#include "SMUManager.h"
#include "SMULogicManager.h"
#include "ShareDBManager.h"
#include "ODBCInterface.h"
#include "CommandThread.h"
#include "PlayerShopDefine.h"

#if defined ( __LINUX__ )
#include <stdlib.h>
#include <sys/types.h> 
#include <signal.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <errno.h>
#elif defined ( __WINDOWS__ )
#include <WinBase.h>
#endif


ShareMemory            g_ShareMemory ;

using namespace PLAYER_SHOP ;
INT                    g_CmdInput ;


BOOL                CheckSaveAllFile() ;
BOOL                CheckExitFile() ;

INT main( INT argc, CHAR* argv[] )
{
#if defined(__WINDOWS__)
    _CrtSetDbgFlag( _CrtSetDbgFlag( 0 ) | _CRTDBG_LEAK_CHECK_DF ) ;
#endif
    g_CmdInput = FALSE ;

    if ( 1 < argc )
    {
        for ( INT i = 1; i < argc; i++ )
        {
            if ( 0 == strcmp( argv[ i ], "-clear" ) )
            {
                g_CmdArgv = CMD_MODE_CLEARALL ;
                printf( "Cmd enter clear mode!%s", LF ) ;
            }
            if ( 0 == strcmp( argv[ i ], "-loaddump" ) )
            {
                g_CmdArgv = CMD_MODE_LOADDUMP ;
                printf( "Cmd enter loaddump mode!%s", LF ) ;
            }
            if ( 0 == strcmp( argv[ i ], "-enablecmd" ) )
            {    
                g_CmdInput = TRUE ;
            }
            if ( 0 == strcmp( argv[ i ], "-ignoreassert" ) )
            {
                g_Command_Assert = 1 ;
            }
            else if ( 0 == strcmp( argv[ i ], "-retryassert" ) )
            {
                g_Command_Assert = 2 ;
            }
            if ( 0 == strcmp( argv[ i ], "-ignoremessagebox" ) )
            {
                g_Command_IgnoreMessageBox = TRUE ;
            }
                    
        }
    }
    
    
    g_pTimeManager = new TimeManager ;
    Assert( g_pTimeManager ) ;
    g_pTimeManager->Init()  ;

    BOOL bRet ;

    Log::SaveLog( "ShareMemory", "(###) main...%s", LF ) ;
    Log::SaveLog( "ShareMemory", "ShareMemory Start...%s", LF ) ;

    bRet = g_ShareMemory.Init() ;
    if ( FALSE == bRet )
    {
        Assert( FALSE ) ;
        return 1 ;
    }
    
    bRet = g_ShareMemory.Loop() ;
    if ( FALSE == bRet )
    {
        Assert( FALSE ) ;
        return 1 ;
    }

    bRet = g_ShareMemory.Exit() ;
    if ( FALSE == bRet )
    {
        Assert( FALSE ) ;
        return 1 ;
    }
    
    SAFE_DELETE( g_pTimeManager ) ;

    return 0 ;
}

ShareMemory::ShareMemory() : m_bExited( FALSE )
{   
}

ShareMemory::~ShareMemory()
{
}

BOOL ShareMemory::Init()
{

    BOOL bRet ;

    Log::SaveLog( "ShareMemory", "Start Read Config Files..." ) ;
    bRet = g_Config.Init() ;
    Assert( bRet ) ;

    Log::SaveLog( "ShareMemory", "Read Config Files...OK!" ) ;
    
    
    Log::SaveLog( "ShareMemory", "Start New Managers..." ) ;
    bRet = NewStaticManager() ;
    Assert( bRet ) ;
    Log::SaveLog( "ShareMemory", "New Managers...OK!" ) ;

    Log::SaveLog( "ShareMemory", "Start Init Managers..." ) ;
    bRet = InitStaticManager() ;
    Assert( bRet ) ;
    Log::SaveLog( "ShareMemory", "Init Managers...OK!" ) ;
    return TRUE ;
}

BOOL ShareMemory::Loop()
{
    if ( g_CmdInput )
    {
        g_CommandThread.start();
        Log::SaveLog( "ShareMemory", "g_CommandThread.start()" ) ;
    }

    Log::SaveLog( "ShareMemory", "Loop...Start" ) ;
    while ( TRUE )
    {
        DoWork() ;
        MySleep( 1000 ) ;
    }
    Log::SaveLog( "ShareMemory", "Loop...End" ) ;

    return TRUE ;
}

BOOL ShareMemory::Exit()
{
    DelStaticManager() ;
    m_bExited= FALSE ;
    return TRUE ;
}

BOOL ShareMemory::DoWork()
{   
    _MY_TRY
    {  
        BOOL  bExit = FALSE ;

        ODBCInterface* pInterface = g_pDBManager->GetInterface( CHARACTER_DATABASE ) ;
        Assert( pInterface ) ;

        if ( !pInterface->IsConnected() )
        {
            Log::SaveLog( "ShareMemory", "connect database is fails" ) ;
            BOOL bRet = pInterface->Connect() ;
            if ( !bRet )
            {
                Log::SaveLog( "ShareMemory", "Can't connect database" ) ;
                MySleep( 5000 ) ;
                if ( CMD_UNKNOW == g_CommandThread.m_SMConfig.Commands.cmdType )
                {
                    return FALSE ;
                }
            }
            else
            {
                Log::SaveLog( "ShareMemory", "Reconnect database" ) ;
            }
        }
        if ( CheckSaveAllFile() )
        {
            g_CommandThread.m_SMConfig.Commands.cmdType = CMD_SAVE_ALL ;
        }

        if ( CheckExitFile() )
        {
            g_CommandThread.m_SMConfig.Commands.cmdType = CMD_SAVE_ALL ;
            bExit = TRUE ;
            Log::SaveLog( "ShareMemory", "Get Exit Commands" ) ;
        }
        if ( CMD_UNKNOW != g_CommandThread.m_SMConfig.Commands.cmdType )
        {
            g_SMConfig = g_CommandThread.m_SMConfig ;
            g_CommandThread.m_SMConfig.Commands.cmdType = CMD_UNKNOW ;
        }

        for ( UINT i = 0; MAX_SM_OBJ_NUM > i; i++ )
        {
            if ( m_SMULogicManager[ i ].m_SMULogicManager )
            {
                SHAREMEM_TYPE Type = m_SMULogicManager[ i ].m_Type;

                switch ( Type ) 
                {
                case ST_HUMAN_SMU:
                    {
                        SMULogicManager< HumanSMU >* pHumanSMULogicMgr = static_cast< SMULogicManager< HumanSMU >* >( m_SMULogicManager[ i ].m_SMULogicManager ) ;
                        if ( pHumanSMULogicMgr )
                            pHumanSMULogicMgr->HeartBeat() ;
                        else
                        {
                            AssertEx( FALSE, "Runtime Type error" ) ;
                        }

                        break ;
                    }
                case ST_GUILD_SMU:
                    {
                        SMULogicManager< GuildSMU >* pGuildSMULogicMgr = static_cast< SMULogicManager< GuildSMU >* >( m_SMULogicManager[ i ].m_SMULogicManager ) ; 
                        if ( pGuildSMULogicMgr )
                            pGuildSMULogicMgr->HeartBeat() ;
                        else
                        {
                            AssertEx( FALSE, "Runtime Type error" ) ;
                        }

                        break ;
                    }
                case ST_MAIL_SMU:
                    {
                        SMULogicManager< MailSMU >* pMailSMULogicMgr = static_cast< SMULogicManager< MailSMU >* >( m_SMULogicManager[ i ].m_SMULogicManager ) ;
                        if ( pMailSMULogicMgr )
                            pMailSMULogicMgr->HeartBeat() ;
                        else
                        {
                            AssertEx( FALSE, "Runtime Type error" ) ;
                        }

                        break ;    
                    }
                case ST_PSHOP_SMU:
                    {
                        SMULogicManager< PlayerShopSM >* pPShopSMULogicMgr = static_cast< SMULogicManager< PlayerShopSM >* >( m_SMULogicManager[ i ].m_SMULogicManager ) ;
                        if ( pPShopSMULogicMgr )
                            pPShopSMULogicMgr->HeartBeat() ;
                        else
                        {
                            AssertEx( FALSE, "Runtime Type error" ) ;
                        }
                        break;
                    }

                case ST_ITEMSERIAL_SMU:
                    {
                        SMULogicManager< ItemSerialKeySMU >* pItemSerialSMULogicMgr = static_cast< SMULogicManager< ItemSerialKeySMU >* >( m_SMULogicManager[ i ].m_SMULogicManager ) ;
                        if ( pItemSerialSMULogicMgr )
                            pItemSerialSMULogicMgr->HeartBeat() ;
                        else
                        {
                            AssertEx( FALSE, "Runtime Type error" ) ;
                        }
                        break ;

                    }
                case ST_USERDATA_SMU:
                    {
                        AssertEx( FALSE, "Unknow SMU Type" ) ;
                        break ;
                    }
                case ST_HUMANEXT_SMU:
                    {
                        AssertEx( FALSE, "Unknow SMU Type" ) ;
                        break ;
                    }
                default:
                    {
                        AssertEx( FALSE, "Unknow SMU Type" ) ;
                    }
                }
            }
        }

        if ( CMD_CLEAR_ALL == g_SMConfig.Commands.cmdType )
        {
            exit( 0 ) ;
        }

        
        g_SMConfig.Commands.cmdType = CMD_UNKNOW;

        if( bExit )
        {
            Log::SaveLog( "ShareMemory", "Exit ShareMemory Program" ) ;
            exit( 0 ) ;
        }

        return TRUE ;

    }
    _MY_CATCH
    {
        Log::SaveLog( "ShareMemory", "ShareMemory::DoWork() Get Error" ) ;
    
    }

    return FALSE ;

}



BOOL ShareMemory::NewStaticManager()
{
    __ENTER_FUNCTION

        g_pDBManager = new ShareDBManager() ;
        AssertEx( g_pDBManager, "分配数据库管理器失败!" ) ;
        Log::SaveLog( "ShareMemory", "new ShareDBManager ...OK" ) ;
  
        for ( UINT i = 0; i< g_Config.m_ShareMemInfo.m_SMUObjCount; i++ )
        {
            m_SMUPool[ i ].m_Data = g_Config.m_ShareMemInfo.m_pShareData[ i ] ;

            SHAREMEM_TYPE type = g_Config.m_ShareMemInfo.m_pShareData[ i] .m_Type ;
            switch ( type ) 
            {
                case ST_HUMAN_SMU:
                {
                    m_SMUPool[ i ].m_Pool = new SMUPool< HumanSMU >() ;
                    Assert( m_SMUPool[ i ].m_Pool ) ;
                    Log::SaveLog( "ShareMemory", "new SMUPool< HumanSMU >()...OK" ) ;
                    m_SMULogicManager[ i ].m_SMULogicManager = new SMULogicManager< HumanSMU >() ;
                    Assert( m_SMULogicManager[ i ].m_SMULogicManager ) ;
                    Log::SaveLog( "ShareMemory", "new SMULogicManager< HumanSMU >()...OK" ) ;
                    m_SMULogicManager[ i ].m_Type    =    ST_HUMAN_SMU ;
                }
                    break ;
                case ST_GUILD_SMU:
                {
                    m_SMUPool[ i ].m_Pool = new SMUPool< GuildSMU >() ;
                    Assert( m_SMUPool[ i ].m_Pool ) ;
                    Log::SaveLog( "ShareMemory", "new SMUPool< GuildSMU >()...OK" ) ;
                    m_SMULogicManager[ i ].m_SMULogicManager = new SMULogicManager< GuildSMU >() ;
                    Assert( m_SMULogicManager[ i ].m_SMULogicManager ) ;
                    Log::SaveLog( "ShareMemory", "new SMULogicManager< GuildSMU >()...OK" ) ;
                    m_SMULogicManager[ i ].m_Type    =    ST_GUILD_SMU ;
                }
                    break ;
                case ST_MAIL_SMU:
                {
                    m_SMUPool[ i ].m_Pool = new SMUPool< MailSMU >() ;
                    Assert( m_SMUPool[ i ].m_Pool ) ;
                    Log::SaveLog( "ShareMemory", "new SMUPool< MailSMU >()...OK" ) ;
                    m_SMULogicManager[ i ].m_SMULogicManager = new SMULogicManager< MailSMU >() ;
                    Assert( m_SMULogicManager[ i ].m_SMULogicManager ) ;
                    Log::SaveLog( "ShareMemory", "new SMULogicManager< MailSMU >()...OK" ) ;
                    m_SMULogicManager[ i ].m_Type    =    ST_MAIL_SMU ;    
                }
                    break ;
                case ST_PSHOP_SMU:
                {
                    m_SMUPool[ i ].m_Pool = new SMUPool< PlayerShopSM >();
                    Assert( m_SMUPool[ i ].m_Pool ) ;
                    Log::SaveLog( "ShareMemory", "new SMUPool< PlayerShopSM >()...OK" ) ;
                    m_SMULogicManager[ i ].m_SMULogicManager = new SMULogicManager< PlayerShopSM >() ;
                    Assert( m_SMULogicManager[ i ].m_SMULogicManager ) ;
                    Log::SaveLog( "ShareMemory", "new SMULogicManager< PlayerShopSM >()...OK" ) ;
                    m_SMULogicManager[ i ].m_Type    =    ST_PSHOP_SMU ;    
                }
                    break ;
                case ST_ITEMSERIAL_SMU:
                {
                    m_SMUPool[ i ].m_Pool = new SMUPool< ItemSerialKeySMU >() ;
                    Assert( m_SMUPool[ i ].m_Pool ) ;
                    Log::SaveLog( "ShareMemory", "new SMUPool< ItemSerialKeySMU >()...OK" ) ;
                    m_SMULogicManager[ i ].m_SMULogicManager = new SMULogicManager< ItemSerialKeySMU >() ;
                    Assert( m_SMULogicManager[ i ].m_SMULogicManager ) ;
                    Log::SaveLog( "ShareMemory", "new SMULogicManager< ItemSerialKeySMU >()...OK" ) ;
                    m_SMULogicManager[ i ].m_Type    =    ST_ITEMSERIAL_SMU ;    
                }
                    break ;
                case ST_USERDATA_SMU:
                    AssertEx( FALSE, "Unimplement Type: ST_USERDATA_SMU" ) ;
                    break ;
                case ST_HUMANEXT_SMU:
                    AssertEx( FALSE, "Unimplement Type: ST_HUMANEXT_SMU" ) ;
                    break ;
                default:
                    break ;
            }
        
        }

        //Log::SaveLog( "ShareMemory", "new SMUPool< HumanSMU >()...OK" ) ;

        return TRUE ;

    __LEAVE_FUNCTION    

        return FALSE;
}

BOOL ShareMemory::InitStaticManager()
{

    __ENTER_FUNCTION

        BOOL bRet = FALSE ;

        //DB 的初始化,连接数据库
        Assert( g_pDBManager ) ;
        bRet = g_pDBManager->Init() ;
        if ( !bRet )
        {
            Log::SaveLog( "ShareMemory", "g_pDBManager->Init()...Fails" ) ;
        }
        else
            Log::SaveLog( "ShareMemory", "g_pDBManager->Init()...OK" ) ;

        for ( UINT i = 0; i < g_Config.m_ShareMemInfo.m_SMUObjCount; i++ )
        {
            SHAREMEM_TYPE type = g_Config.m_ShareMemInfo.m_pShareData[i].m_Type ;
            switch ( type )
            {
                case ST_HUMAN_SMU:
                {
                
                    SMUPool< HumanSMU >* pHumanSMUPool = static_cast< SMUPool< HumanSMU >* >( m_SMUPool[ i ].m_Pool ) ;
                    Assert( pHumanSMUPool ) ;
                    SM_KEY key = m_SMUPool[ i ].m_Data.m_Key ;
                    bRet = pHumanSMUPool->Init( MAX_POOL_SIZE, key, SMPT_SHAREMEM ) ;
                    Assert( bRet ) ;
                    SMULogicManager< HumanSMU >* pHumanSMULogicMgr = static_cast< SMULogicManager< HumanSMU >* >( m_SMULogicManager[ i ].m_SMULogicManager ) ;
                    Assert( pHumanSMULogicMgr ) ;
                    bRet = pHumanSMULogicMgr->Init( pHumanSMUPool ) ;
                    Assert( bRet ) ;
                }
                    break ;
                case ST_GUILD_SMU:
                {
                    SMUPool< GuildSMU >* pGuildSMUPool = static_cast< SMUPool< GuildSMU >* >( m_SMUPool[ i ].m_Pool ) ;
                    Assert( pGuildSMUPool ) ;
                    SM_KEY key = m_SMUPool[ i ].m_Data.m_Key ;
                    bRet = pGuildSMUPool->Init( MAX_GUILD_SIZE, key, SMPT_SHAREMEM ) ;
                    Assert( bRet ) ;
                    SMULogicManager< GuildSMU >* pGuildSMULogicMgr = static_cast< SMULogicManager< GuildSMU >* >( m_SMULogicManager[ i ].m_SMULogicManager ) ;
                    Assert( pGuildSMULogicMgr ) ;
                    bRet = pGuildSMULogicMgr->Init( pGuildSMUPool ) ;
                    Assert( bRet ) ;
                }
                    break ;
                case ST_MAIL_SMU:
                {
                    SMUPool< MailSMU >* pMailSMUPool = static_cast< SMUPool< MailSMU >* >( m_SMUPool[ i ].m_Pool ) ;
                    Assert( pMailSMUPool ) ;
                    SM_KEY key = m_SMUPool[ i ].m_Data.m_Key ;
                    bRet = pMailSMUPool->Init( MAX_MAILNODE_SIZE, key, SMPT_SHAREMEM ) ;
                    Assert( bRet ) ;
                    SMULogicManager< MailSMU >* pMailSMULogicMgr = static_cast< SMULogicManager< MailSMU >* >( m_SMULogicManager[ i ].m_SMULogicManager ) ;
                    Assert( pMailSMULogicMgr ) ;
                    bRet = pMailSMULogicMgr->Init( pMailSMUPool ) ;
                    Assert( bRet ) ;
                }
                    break ;
                case ST_PSHOP_SMU:
                {
                    SMUPool< PlayerShopSM >* pPlayerShopSMUPool = static_cast< SMUPool< PlayerShopSM >* >( m_SMUPool[ i ].m_Pool ) ;
                    Assert( pPlayerShopSMUPool ) ;
                    SM_KEY key = m_SMUPool[ i ].m_Data.m_Key ;
                    bRet = pPlayerShopSMUPool->Init( MAX_PLAYER_SHOP_POOL_PER_SERVER, key, SMPT_SHAREMEM ) ;
                    Assert( bRet ) ;
                    SMULogicManager< PlayerShopSM >* pPlayerShopSMULogicMgr = static_cast< SMULogicManager< PlayerShopSM >* >( m_SMULogicManager[ i ].m_SMULogicManager ) ;
                    Assert( pPlayerShopSMULogicMgr ) ;
                    bRet = pPlayerShopSMULogicMgr->Init( pPlayerShopSMUPool ) ;
                    Assert( bRet ) ;
                }    
                    break ;
                case ST_ITEMSERIAL_SMU:
                {
                    SMUPool< ItemSerialKeySMU >* pItemSerialSMUPool = static_cast< SMUPool< ItemSerialKeySMU >* >( m_SMUPool[ i ].m_Pool ) ;
                    Assert( pItemSerialSMUPool ) ;
                    SM_KEY key = m_SMUPool[ i ].m_Data.m_Key ;
                    bRet = pItemSerialSMUPool->Init( 1, key, SMPT_SHAREMEM ) ;
                    Assert( bRet ) ;
                    SMULogicManager< ItemSerialKeySMU >* pItemSerialSMULogicMgr = static_cast< SMULogicManager< ItemSerialKeySMU >* >( m_SMULogicManager[ i ].m_SMULogicManager ) ;
                    Assert( pItemSerialSMULogicMgr ) ;
                    bRet = pItemSerialSMULogicMgr->Init( pItemSerialSMUPool ) ;
                    Assert( bRet ) ;
                }
                    break ;
                case ST_USERDATA_SMU:
                    AssertEx( FALSE, "Unimplement Type: ST_USERDATA_SMU" ) ;
                    break ;
                case ST_HUMANEXT_SMU:
                    AssertEx( FALSE, "Unimplement Type: ST_HUMANEXT_SMU" ) ;
                    break ;
                default:
                    AssertEx( bRet, "ShareMemory::InitStaticManager fails" ) ;
                    break ;
            }
        }


        return bRet ;

    __LEAVE_FUNCTION    

        return FALSE ;
}

BOOL ShareMemory::DelStaticManager()
{

    __ENTER_FUNCTION

        for ( UINT i = 0; i < g_Config.m_ShareMemInfo.m_SMUObjCount; i++ )
        {
            SHAREMEM_TYPE type = g_Config.m_ShareMemInfo.m_pShareData[ i ].m_Type ;
            switch ( type )
            {
                case ST_HUMAN_SMU:
                {
                    SMUPool< HumanSMU >* pHumanSMUPool = 
                        static_cast< SMUPool< HumanSMU >* >( m_SMUPool[ i ].m_Pool ) ;
                    SMULogicManager< HumanSMU >* pHumanSMULogicMgr = 
                        static_cast< SMULogicManager< HumanSMU >* >( m_SMULogicManager[ i ].m_SMULogicManager ) ;
                
                    SAFE_DELETE( pHumanSMUPool ) ;
                    SAFE_DELETE( pHumanSMULogicMgr ) ;
                }
                    break ;
                case ST_GUILD_SMU:
                {
                    SMUPool< GuildSMU >* pGuildSMUPool = 
                        static_cast< SMUPool< GuildSMU >* >( m_SMUPool[ i ].m_Pool ) ;
                    SMULogicManager< GuildSMU >* pGuildSMULogicMgr = 
                        static_cast< SMULogicManager< GuildSMU >* >( m_SMULogicManager[ i ].m_SMULogicManager ) ;

                    SAFE_DELETE( pGuildSMUPool ) ;
                    SAFE_DELETE( pGuildSMULogicMgr ) ;
                }
                    break ;
                case ST_MAIL_SMU:
                {
                    SMUPool< MailSMU >* pMailSMUPool = 
                        static_cast< SMUPool< MailSMU >* >( m_SMUPool[ i ].m_Pool ) ;
                    SMULogicManager< MailSMU >* pMailSMULogicMgr = 
                        static_cast< SMULogicManager< MailSMU >* >( m_SMULogicManager[ i ].m_SMULogicManager ) ;

                    SAFE_DELETE( pMailSMUPool ) ;
                    SAFE_DELETE( pMailSMULogicMgr ) ;

                }
                    break ;
                case ST_ITEMSERIAL_SMU:
                {
                    SMUPool< ItemSerialKeySMU >* pSMUPool = 
                        static_cast< SMUPool< ItemSerialKeySMU >* >( m_SMUPool[ i ].m_Pool ) ;
                    SMULogicManager< ItemSerialKeySMU >* pSMULogicMgr = 
                        static_cast< SMULogicManager< ItemSerialKeySMU >* >( m_SMULogicManager[ i ].m_SMULogicManager ) ;

                    SAFE_DELETE( pSMUPool ) ;
                    SAFE_DELETE( pSMULogicMgr ) ;
                }
                    break ;
                case ST_USERDATA_SMU:
                    AssertEx( FALSE, "Unimplement Type: ST_USERDATA_SMU" ) ;
                    break ;
                case ST_HUMANEXT_SMU:
                    AssertEx( FALSE, "Unimplement Type: ST_HUMANEXT_SMU" ) ;
                    break ;
                default:
                    AssertEx( FALSE, "ShareMemory::InitStaticManager fails" ) ;
                    break ;
            }
           
        }

        //Log::SaveLog( "ShareMemory", "new SMUPool< HumanSMU >()...OK" ) ;
        
        return TRUE ;

    __LEAVE_FUNCTION    
    
        return FALSE;
}

BOOL    CheckSaveAllFile()
{
    __ENTER_FUNCTION
    
        if( -1 ==  remove( "saveall.cmd" ) )
        {
            return FALSE;
        }
            
        return TRUE ;


    __LEAVE_FUNCTION

        return FALSE ;
}

BOOL    CheckExitFile()
{
    __ENTER_FUNCTION


        if( -1 == remove( "exit.cmd" ) )
        {
            return FALSE ;
        }
        extern BOOL g_LockTimeOutEnable ;
        g_LockTimeOutEnable = TRUE ;
        return TRUE ;

    __LEAVE_FUNCTION

        return FALSE ;
}


VOID INTHandler( INT )
{
    DumpStack( "INT exception:" ) ;
    exit( 0 ) ;
}
VOID TERMHandler( INT )
{
    DumpStack( "TERM exception:" ) ;
    exit( 0 ) ;

}
VOID ABORTHandler( INT )
{
    DumpStack( "ABORT exception:" ) ;
    exit( 0 ) ;
}

VOID ILLHandler( INT )
{
    DumpStack( "ILL exception:" ) ;
    exit( 0 ) ;
}

VOID FPEHandler( INT )
{
    DumpStack( "FPE exception:" ) ;
    exit( 0 ) ;
}

VOID SEGHandler( INT )
{
    DumpStack( "SEG exception:" ) ;
    exit( 0 ) ;
}
VOID XFSZHandler( INT )
{
    DumpStack( "XFSZ exception:" ) ;
    exit( 0 ) ;
}

ShmExceptionHandler::ShmExceptionHandler()
{
#ifdef __LINUX__
    signal( SIGSEGV, SEGHandler ) ;
    signal( SIGFPE,  FPEHandler ) ;
    signal( SIGILL,  ILLHandler ) ;
    signal( SIGINT,  INTHandler ) ;  
    signal( SIGTERM, TERMHandler ) ; 
    signal( SIGABRT, ABORTHandler ) ;
    signal( SIGXFSZ, XFSZHandler ) ;
#endif
}

ShmExceptionHandler g_ShmExceptionHandler ;
