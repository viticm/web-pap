#include "stdafx.h"

#include "LoginMain.h"
#include "TimeManager.h"
#include "Log.h"
#include "Config.h"
#include "Login.h"

INT main( INT argc, CHAR* argv[] )
{
#if defined( __WINDOWS__ )
    _CrtSetDbgFlag( _CrtSetDbgFlag(0) | _CRTDBG_LEAK_CHECK_DF ) ;
#endif
    
    __ENTER_FUNCTION
        
            if ( 1 < argc )
            {
                for ( INT i = 1 ; i < argc ; i++ )
                {
                    if ( 0 == strcmp( "-ignoreassert" == argv[i] ) )
                    {
                        g_Command_Assert = 1 ;
                    }
                    else if ( 0 == strcmp( "-retryassert", argv[i] ) )
                    {
                        g_Command_Assert = 2 ;
                    }

                    if ( 0 == strcmp( "-ignoremessagebox", argv[i] ) )
                    {
                        g_Command_IgnoreMessageBox=TRUE ;
                    }
                }
            }    
            
        //时间管理器
        g_pTimeManager = new TimeManager ;
        g_pTimeManager->Init() ;
                
        Log::SaveLog( "Login", "%s(###) main...", LF ) ;
        g_pTimeManager->SetTime( ) ;
            
        Log::SaveLog( "Login", "Login Starting... (%.10d)(%d)",
            g_pTimeManager->Time2DWORD(), g_pTimeManager->StartTime() ) ;
        srand( g_pTimeManager->CurrentTime() ) ;
        BOOL bRet = g_Login.Init() ;
        Assert( bRet ) ;
            
        bRet = g_Login.Loop() ;    
        Assert( bRet ) ;

        bRet = g_Login.Exit() ;
        Assert( bRet ) ;

        return 0 ;

    __LEAVE_FUNCTION

        return -1 ;
}
