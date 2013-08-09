#include "stdafx.h"
#include "DBManager.h"
#include "ODBCInterface.h"
#include "TimeManager.h"

DBManager *g_pDBManager = NULL;

DBManager::DBManager()
{
    mCharDBInterface = new ODBCInterface();
    m_Active = TRUE;
}

DBManager::~DBManager()
{
    SAFE_DELETE(mCharDBInterface);
}


BOOL DBManager::Init()
{
    __ENTER_FUNCTION
    
        //从Config 读取 Char DB 相关的数据
        CHAR    szCharDBHost[ HOST_STR_LEN ] ;
        strncpy( szCharDBHost, g_Config.m_ShareMemInfo.m_DBIP,HOST_STR_LEN ) ;                        //连接对端IP
        szCharDBHost[ HOST_STR_LEN - 1 ] = '\0' ;

        UINT    uCharDBPort =    g_Config.m_ShareMemInfo.m_DBPort ;                                   //连接对端端口
        
        CHAR    szCharDBDatabase[ DATABASE_STR_LEN ] ;
        strncpy( szCharDBDatabase, g_Config.m_ShareMemInfo.m_DBName, DATABASE_STR_LEN ) ;              //数据库名称
        szCharDBDatabase[ DATABASE_STR_LEN - 1 ] = '\0' ;

        CHAR    szCharDBUser[ DB_USE_STR_LEN ] ;                                                       //用户名称
        strncpy( szCharDBUser, g_Config.m_ShareMemInfo.m_DBUser, DB_USE_STR_LEN ) ;
        szCharDBUser[ DB_USE_STR_LEN - 1 ] = '\0' ;

        CHAR    szCharDBPassword[ DB_PASSWORD_STR_LEN ] ;                                              //密码
        strncpy( szCharDBPassword, g_Config.m_ShareMemInfo.m_DBPassword, DB_PASSWORD_STR_LEN ) ;
        szCharDBPassword[ DB_PASSWORD_STR_LEN - 1 ] = '\0' ;
    
        Assert( mCharDBInterface );

        mCharDBInterface->Connect( szCharDBDatabase, szCharDBUser, szCharDBPassword ) ;
    
        if( !mCharDBInterface->IsConnected() )
        {
            Log::SaveLog( LOGIN_LOGFILE,"mCharDBInterface->Connect()... Get Errors: %s ",
                mCharDBInterface->GetErrorMsg() );
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

ODBCInterface*    DBManager::GetInterface(DB_NAMES name)
{
    __ENTER_FUNCTION
        
        switch(name) 
        {
        case CHARACTER_DATABASE:
            return mCharDBInterface;
            break;
        default:
            return NULL;

        }

    __LEAVE_FUNCTION
}


