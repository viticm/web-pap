/**
 * PAP Server Engine ( https://github.com/viticm/web-pap )
 * $Id DBManager.cpp
 * @link https://github.com/viticm/web-pap/tree/master/server for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-8-9 15:25:01
 * @uses the database manager
 */
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
        CHAR    szDBCharHost[ HOST_STR_LEN ] ;
        strncpy( szDBCharHost, g_Config.m_ShareMemInfo.m_DBIP,HOST_STR_LEN ) ;                        //连接对端IP
        szDBCharHost[ HOST_STR_LEN - 1 ] = '\0' ;

        UINT    uDBCharPort =    g_Config.m_ShareMemInfo.m_DBPort ;                                   //连接对端端口
        
        CHAR    szDBCharDatabase[ DATABASE_STR_LEN ] ;
        strncpy( szDBCharDatabase, g_Config.m_ShareMemInfo.m_DBName, DATABASE_STR_LEN ) ;              //数据库名称
        szDBCharDatabase[ DATABASE_STR_LEN - 1 ] = '\0' ;

        CHAR    szDBCharUser[ DB_USE_STR_LEN ] ;                                                       //用户名称
        strncpy( szDBCharUser, g_Config.m_ShareMemInfo.m_DBUser, DB_USE_STR_LEN ) ;
        szDBCharUser[ DB_USE_STR_LEN - 1 ] = '\0' ;

        CHAR    szDBCharPassword[ DB_PASSWORD_STR_LEN ] ;                                              //密码
        strncpy( szDBCharPassword, g_Config.m_ShareMemInfo.m_DBPassword, DB_PASSWORD_STR_LEN ) ;
        szDBCharPassword[ DB_PASSWORD_STR_LEN - 1 ] = '\0' ;
    
        Assert( mCharDBInterface );

        mCharDBInterface->Connect( szDBCharDatabase, szDBCharUser, szDBCharPassword ) ;
    
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


