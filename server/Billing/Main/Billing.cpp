/**
 * PAP Server Engine ( https://github.com/viticm/web-pap )
 * $Id Billing.cpp
 * @link https://github.com/viticm/web-pap/tree/master/server for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-8-8 19:59:10
 * @uses the main file for Billing module
 */
#include "stdafx.h"
#include "Billing.h"
#include "TimeManager.h"
#include "Log.h"
#include "Config.h"
#include "ServerManager.h"
#include "WebPlayer.h"
#include "PacketFactoryManager.h"
#include "PlayerPool.h"
#include "UserDBManager.h"

#ifdef __LINUX__
    #include <signal.h>
#endif

Billing            g_Billing ;

INT main( INT argc, CHAR* argv[] )
{
#if defined(__WINDOWS__)
    _CrtSetDbgFlag( _CrtSetDbgFlag(0) | _CRTDBG_LEAK_CHECK_DF ) ;
#endif

    __ENTER_FUNCTION

        if( argc > 1 )
        {
            for( INT i = 1; i < argc; i++ )
            {
                if( 0 == strcmp( argv[ i ], "-ignoreassert" ) )
                {
                    g_Command_Assert = 1 ;
                }
                if( 0 == strcmp( argv[ i ], "-retryassert" ) )
                {
                    g_Command_Assert = 2 ;
                }
                else if( 0 == strcmp( argv[ i ], "-ignoremessagebox" ) )
                {
                    g_Command_IgnoreMessageBox = TRUE ;
                }
            }
        }


        BOOL bRet ;

        //时间模块需要最开始的时候设置
        g_pTimeManager = new TimeManager ;
        Assert( g_pTimeManager ) ;
        g_pTimeManager->Init() ;

        Log::SaveLog( "Billing", "(###) main..." ) ;
        Log::SaveLog( "Billing", "Billing Start... " ) ;



        bRet = g_Billing.Init() ;
        if( FALSE == bRet )
        {
            Assert( FALSE ) ;
            return 1 ;
        }

        bRet = g_Billing.Loop() ;
        if( FALSE == bRet )
        {
            Assert( FALSE ) ;
            return 1 ;
        }

        bRet = g_Billing.Exit() ;
        if( FALSE == bRet )
        {
            Assert( FALSE ) ;
            return 1 ;
        }

    __LEAVE_FUNCTION

            return 0 ;
}

Billing::Billing()
{
    __ENTER_FUNCTION

#if defined(__WINDOWS__)
        WORD wVersionRequested ;
        WSADATA wsaData ;
        INT err ;
        wVersionRequested = MAKEWORD( 2, 2 ) ;
        err = WSAStartup( wVersionRequested, &wsaData ) ; 
#endif

    __LEAVE_FUNCTION
}

Billing::~Billing()
{
    __ENTER_FUNCTION

#if defined(__WINDOWS__)
        WSACleanup();
#endif

    __LEAVE_FUNCTION
}

BOOL Billing::Init()
{
    __ENTER_FUNCTION

    BOOL bRet ;

    Log::SaveLog( "Billing", "Start Read Config Files..." ) ;
    bRet = g_Config.Init() ;
    Assert( bRet ) ;
    Log::SaveLog( "Billing", "Read Config Files...OK!" ) ;

    Log::SaveLog( "Billing", "Start New Managers..." ) ;
    bRet = NewStaticManager() ;
    Assert( bRet ) ;
    Log::SaveLog( "Billing", "New Managers...OK!" ) ;

    Log::SaveLog( "Billing", "Start Init Managers..." ) ;
    bRet = InitStaticManager() ;
    Assert( bRet ) ;
    Log::SaveLog( "Billing", "Init Managers...OK!" ) ;

    return TRUE ;

    __LEAVE_FUNCTION

    return FALSE ;
}

BOOL Billing::Loop()
{
    __ENTER_FUNCTION

        Log::SaveLog( "Billing", "Loop..." ) ;
        g_pServerManager->Loop() ;

    __LEAVE_FUNCTION

        return TRUE ;
}

BOOL Billing::Exit( )
{
    __ENTER_FUNCTION

        BOOL bRet ;

        Log::SaveLog( "Billing", "Start Exit..." ) ;
        bRet = DelStaticManager() ;
        Assert( bRet ) ;
        Log::SaveLog( "Billing", "Exit...OK!" ) ;


    __LEAVE_FUNCTION

        return TRUE ;
}

BOOL Billing::NewStaticManager()
{
    __ENTER_FUNCTION

        g_pServerManager = new ServerManager ;
        Assert( g_pServerManager ) ;
        Log::SaveLog( "Billing", "new ServerManager...OK" ) ;
    
        g_pPlayerPool = new PlayerPool ;
        Assert( g_pPlayerPool ) ;
        Log::SaveLog( "Billing", "new PlayerPool...OK" ) ;

        g_pWebPlayer = new WebPlayer ;
        Assert( g_pWebPlayer ) ;
        Log::SaveLog( "Billing", "new g_pWebPlayer...OK" ) ;

        g_pPacketFactoryManager = new PacketFactoryManager ;
        Assert( g_pPacketFactoryManager ) ;
        Log::SaveLog( "Billing", "new PacketFactoryManager...OK" ) ;
    
    __LEAVE_FUNCTION

        return TRUE ;
}

BOOL Billing::InitStaticManager()
{
    __ENTER_FUNCTION

        BOOL ret ;
        INT nTemp = 0 ;
    //ret = g_UserDBManager.Init();
    //Assert( ret ) ;
    //Log::SaveLog( "Billing", "g_UserDBManager->Init()...OK" ) ;

        ret = g_pServerManager->Init() ;
        Assert( ret ) ;
        Log::SaveLog( "Billing", "g_pServerManager->Init()...OK" ) ;

        ret = g_pWebPlayer->Init();
        Assert( ret ) ;
        Log::SaveLog( "Billing", "g_pWebPlayer->Init()...OK" ) ;

        if( g_Config.m_ConfigInfo.m_SystemModel == 0 )
        {
            nTemp = 5;
        }
        else
        {
            nTemp = MAX_POOL_SIZE;
        }
        ret = g_pPlayerPool->Init( nTemp ) ;
        Assert( ret ) ;
        Log::SaveLog( "Billing", "g_pPlayerPool->Init()...OK" ) ;
    
        ret = g_pPacketFactoryManager->Init( ) ;
        Assert( ret ) ;
        Log::SaveLog( "Billing", "g_pPacketFactoryManager->Init()...OK" ) ;

    
    __LEAVE_FUNCTION

        return TRUE ;
}

BOOL Billing::DelStaticManager()
{
    __ENTER_FUNCTION

        SAFE_DELETE( g_pTimeManager ) ;
        Log::SaveLog( "Billing", "g_pTimeManager delete...OK" ) ;
        //
        //以下模块放后面删除
        //
        SAFE_DELETE( g_pPacketFactoryManager ) ;
        Log::SaveLog( "Billing", "g_pPacketFactoryManager delete...OK" ) ;
    
        SAFE_DELETE( g_pPlayerPool ) ;
        Log::SaveLog( "Billing", "g_pPlayerPool delete...OK" ) ;

        SAFE_DELETE(g_pWebPlayer);
        Log::SaveLog( "Billing", "g_pWebPlayer delete...OK" ) ;
    
        SAFE_DELETE( g_pServerManager ) ;
        Log::SaveLog( "Billing", "g_pServerManager delete...OK" ) ;

    __LEAVE_FUNCTION

        return TRUE ;
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

BillingExceptionHandler::BillingExceptionHandler()
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

BillingExceptionHandler g_BillingExcetionHandler ;
