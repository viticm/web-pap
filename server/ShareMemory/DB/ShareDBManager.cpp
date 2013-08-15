#include "stdafx.h"
#include "ShareDBManager.h"
#include "Config.h"
#include "ODBCInterface.h"
#include "TimeManager.h"
#include "Log.h"

BOOL    ShareDBManager::Init()
{
    __ENTER_FUNCTION

        //从Config 读取Login DB 相关的数据
        CHAR    szCharDBHost[ HOST_STR_LEN ] ;
        strncpy( szCharDBHost, g_Config.m_ShareMemInfo.m_DBIP, HOST_STR_LEN ) ;                      //连接对端IP
        szCharDBHost[ HOST_STR_LEN - 1 ] = '\0' ;

        UINT    uCharDBPort = g_Config.m_ShareMemInfo.m_DBPort ;                                     //连接对端端口
        CHAR    szCharDBDatabase[ DATABASE_STR_LEN ] ;
        strncpy( szCharDBDatabase, g_Config.m_ShareMemInfo.m_DBName, DATABASE_STR_LEN ) ;            //数据库名称
        szCharDBDatabase[ DATABASE_STR_LEN - 1 ] = '\0' ;

        CHAR    szCharDBUser[ DB_USE_STR_LEN ] ;                                                     //用户名称
        strncpy( szCharDBUser, g_Config.m_ShareMemInfo.m_DBUser, DB_USE_STR_LEN ) ;
        szCharDBUser[ DB_USE_STR_LEN - 1 ] = '\0' ;

        CHAR    szCharDBPassword[ DB_PASSWORD_STR_LEN ] ;                                            //密码
        strncpy( szCharDBPassword, g_Config.m_ShareMemInfo.m_DBPassword, DB_PASSWORD_STR_LEN ) ;
        szCharDBPassword[ DB_PASSWORD_STR_LEN - 1 ] = '\0' ;

        Assert( mCharDBInterface ) ;

        mCharDBInterface->Connect( szCharDBDatabase, szCharDBUser, szCharDBPassword ) ;

        if( !mCharDBInterface->IsConnected() )
        {
            Log::SaveLog( "ShareMemory", "mCharDBInterface->Connect()... Get Errors: %s ", mCharDBInterface->GetErrorMsg() ) ;
        }

        return mCharDBInterface->IsConnected() ;

    __LEAVE_FUNCTION

        return FALSE ;
}

VOID ShareDBManager::run()
{
    __ENTER_FUNCTION
       
    __LEAVE_FUNCTION
}
