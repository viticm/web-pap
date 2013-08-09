#include "stdafx.h"
#include "DBManager.h"
#include "Config.h"
#include "ODBCInterface.h"
#include "TimeManager.h"
#include "Log.h"

DBManager *g_pDBManager = NULL;

DBManager::DBManager()
{
    mUserDBInterface = new ODBCInterface();
    m_Active = TRUE;
}

DBManager::~DBManager()
{
    SAFE_DELETE( mUserDBInterface );
}

BOOL    DBManager::Init()
{
    __ENTER_FUNCTION
    
        //从Config 读取Login DB 相关的数据
        CHAR    szUserDBHost[ HOST_STR_LEN ];
        strncpy( szUserDBHost, g_Config.m_BillingInfo.m_DBIP, HOST_STR_LEN ) ;            //连接对端IP
        szUserDBHost[ HOST_STR_LEN - 1 ] = '\0' ;

        UINT    uUserDBPort =    g_Config.m_BillingInfo.m_DBPort ;                        //连接对端端口
        CHAR    szUserDBDatabase[ DATABASE_STR_LEN ];
        strncpy( szUserDBDatabase, g_Config.m_BillingInfo.m_DBName, DATABASE_STR_LEN ) ;  //数据库名称
        szUserDBDatabase[ DATABASE_STR_LEN - 1 ] = '\0' ;

        CHAR    szUserDBUser[ DB_USE_STR_LEN ] ;                                          //用户名称
        strncpy( szUserDBUser, g_Config.m_BillingInfo.m_DBUser,DB_USE_STR_LEN ) ;
        szUserDBUser[ DB_USE_STR_LEN - 1 ] = '\0' ;

        CHAR    szUserDBPassword[ DB_PASSWORD_STR_LEN ] ;                                 //密码
        strncpy( szUserDBPassword, g_Config.m_BillingInfo.m_DBPassword, DB_PASSWORD_STR_LEN );
        szUserDBPassword[ DB_PASSWORD_STR_LEN - 1 ] = '\0';
    
        Assert( mUserDBInterface ) ;

        mUserDBInterface->Connect( szUserDBDatabase, szUserDBUser, szUserDBPassword ) ;
    
        if( !mUserDBInterface->IsConnected() )
        {
            Log::SaveLog( BILLING_LOGFILE, "mUserDBInterface->Connect()... Get Errors: %s ",
                mUserDBInterface->GetErrorMsg() ) ;
        }

    
        return TRUE;
                            
    __LEAVE_FUNCTION

        return FALSE;
}


VOID DBManager::run()
{
    __ENTER_FUNCTION
    
    
    /*
        UINT uTime = g_pTimeManager->CurrentTime();
          
            g_DBLogicManager.m_ThreadID    = getTID();
          
            while (IsActive())
            {
               MySleep(100);
              
              if(!mCharDBInterface->IsConnected())
              {
                  mCharDBInterface->Connect();
              }
      
              g_DBLogicManager.HeartBeat(uTime);
            }*/
      
      

    __LEAVE_FUNCTION
}

ODBCInterface*    DBManager::GetInterface( DB_NAMES name )
{
    __ENTER_FUNCTION
        
        switch(name) 
        {
            case USER_DATABASE:
                return mUserDBInterface ;
                break;
            default:
                return NULL;
        }

    __LEAVE_FUNCTION
}


