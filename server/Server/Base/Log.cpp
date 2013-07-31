#include "stdafx.h"

#include "Log.h"
#include "TimeManager.h"
#include "stdarg.h"
#include "Config.h"

CHAR* g_pLogFileName[] =
{
    "login",                //0        LOG_FILE_0
    "debug",                //1        LOG_FILE_1
    "error",                //2        LOG_FILE_2
    "functions",            //3        LOG_FILE_3
    "world",                //4        LOG_FILE_4
    "item",                 //5        LOG_FILE_5
    "send",                 //6        LOG_FILE_6
    "money",                //7        LOG_FILE_7
    "pet",                  //8        LOG_FILE_8
    "skill",                //9        LOG_FILE_9
    "xinfa",                //10       LOG_FILE_10
    "ability",              //11       LOG_FILE_11
    "chat",                 //12       LOG_FILE_12
    "mission",              //13       LOG_FILE_13
    "Login",                //14       LOG_FILE_14
    "Billing",              //15       LOG_FILE_15
    "Debug",                //16       LOG_FILE_16
    "Error",                //17       LOG_FILE_17
    "Functions",            //18       LOG_FILE_18
    "World",                //19       LOG_FILE_19
    "Config",               //20       LOG_FILE_20
    "assert",               //21       LOG_FILE_21
    "RecyclePlayer",        //22       LOG_FILE_22
    '\0'
};

MyLock g_log_lock ;

Log* g_pLog=NULL ;

Log::Log( )
{
__ENTER_FUNCTION

    for( INT i=0; i<LOG_FILE_NUMBER; i++ )
    {
        m_LogCache[i] = NULL ;
        m_LogPos[i] = 0 ;
    }
    m_CacheSize = 0 ;
    m_DayTime= 0 ;

__LEAVE_FUNCTION
}

Log::~Log( )
{
__ENTER_FUNCTION

    for( INT i=0; i<LOG_FILE_NUMBER; i++ )
    {
        SAFE_DELETE_ARRAY(m_LogCache[i])  ;
    }
    m_CacheSize = 0 ;

__LEAVE_FUNCTION
}

BOOL Log::Init( )
{
__ENTER_FUNCTION

    m_CacheSize = DEFAULT_LOG_CACHE_SIZE ;
    //最小化内存占用
    //______________________
    if( g_Config.m_ConfigInfo.m_SystemModel != 0 )
    {
        for( INT i=0; i<LOG_FILE_NUMBER; i++ )
        {
            m_LogCache[i] = new CHAR[m_CacheSize] ;
            if( m_LogCache[i] == NULL )
            {
                return FALSE ;
            }
            m_LogPos[i] = 0 ;
        }
    }
    //______________________
    if( g_pTimeManager )
        m_DayTime = g_pTimeManager->GetDayTime() ;
    else
        m_DayTime = 6000 ;

    return TRUE ;

__LEAVE_FUNCTION

    return FALSE ;
}

VOID Log::FastSaveLog( INT logid, CHAR* msg, ... )
{
__ENTER_FUNCTION

    if( logid<0 || logid >=LOG_FILE_NUMBER )
        return ;

    CHAR buffer[2048];
    va_list argptr;

    try
    {
        va_start(argptr, msg);
        vsprintf(buffer,msg,argptr);
        va_end(argptr);

        if( g_pTimeManager )
        {
            CHAR szTime[84] ;
            #ifdef __LINUX__
            sprintf( szTime, " (%d)(T0=%s T1=%.4f)\n",
                MyGetCurrentThreadID(), g_pTimeManager->GetCurrentFormatTime(), 
                (FLOAT)(g_pTimeManager->RunTime())/1000.0 ) ;
            #else
            sprintf( szTime, " (%d)(T0=%s T1=%.4f)\r\n",
                MyGetCurrentThreadID(), g_pTimeManager->GetCurrentFormatTime(), 
                (FLOAT)(g_pTimeManager->RunTime())/1000.0 ) ;
            #endif
            
            strcat( buffer, szTime ) ;
     
        }
    }
    catch(...)
    {
        Assert(FALSE) ;
        return ;
    }

    INT iLen = (INT)strlen(buffer) ;
    if( iLen<=0 )
        return ;

    //最小化内存占用
    //______________________
    if( g_Config.m_ConfigInfo.m_SystemModel == 0 )
    {
        CHAR szName[_MAX_PATH] ;
        GetLogName( logid, szName ) ;

        SaveLog( szName, buffer );
        return;
    }
    //______________________

    m_LogLock[logid].Lock() ;
    try
    {
        memcpy( m_LogCache[logid]+m_LogPos[logid], buffer, iLen ) ;
        m_LogPos[logid] += iLen ;
        printf( buffer ) ;
    }
    catch(...)
    {
    }
    m_LogLock[logid].Unlock() ;

    

    if( m_LogPos[logid] > (DEFAULT_LOG_CACHE_SIZE*2)/3 )
    {
        FlushLog( logid ) ;
    }
    return ;

__LEAVE_FUNCTION

    return ;
}

VOID Log::FlushLog( INT logid )
{
__ENTER_FUNCTION

    CHAR szName[_MAX_PATH] ;
    GetLogName( logid, szName ) ;

    m_LogLock[logid].Lock() ;
    try
    {
        FILE* f = fopen( szName, "ab" ) ;
        if ( f )
        {
            fwrite( m_LogCache[logid], 1, m_LogPos[logid], f ) ;
            fclose(f) ;
            m_LogPos[logid] = 0 ;
        }
    }
    catch(...)
    {
    }
    m_LogLock[logid].Unlock() ;
    return ;

__LEAVE_FUNCTION
}

VOID Log::FlushLog_All( )
{
__ENTER_FUNCTION

    for( INT i=0; i<LOG_FILE_NUMBER; i++ )
    {
        FlushLog(i) ;
    }

__LEAVE_FUNCTION
}


VOID Log::GetLogName( INT logid, CHAR* szName )
{
__ENTER_FUNCTION

    sprintf( szName, "%s%s_%d.log", LOG_SAVE_PATH, g_pLogFileName[logid], m_DayTime ) ;

__LEAVE_FUNCTION
}

VOID Log::SaveLog( CHAR* szFileName, CHAR* szMsg, ... )
{
__ENTER_FUNCTION
    
    g_log_lock.Lock( ) ;

    INT iLogId = GetLogId( szFileName );
    CHAR szBuffer[ 2048 ];
    memset( szBuffer, 0, 2048 ) ;

    va_list argptr;

    _MY_TRY
    {
        va_start( argptr, szMsg );
        vsprintf( szBuffer, szMsg, argptr );
        va_end( argptr );

        if( g_pTimeManager )
        {
            CHAR szTime[84] ;
            #ifdef __LINUX__
            sprintf( szTime, " (%d)(T0=%s T1=%.4f)\n",
                MyGetCurrentThreadID(), g_pTimeManager->GetCurrentFormatTime(), 
                (FLOAT)(g_pTimeManager->RunTime())/1000.0 ) ;
            #else
            sprintf( szTime, " (%d)(T0=%s T1=%.4f)\r\n",
                MyGetCurrentThreadID(), g_pTimeManager->GetCurrentFormatTime(), 
                (FLOAT)(g_pTimeManager->RunTime())/1000.0 ) ;
            #endif
            
            strcat( szBuffer, szTime ) ;
        }
        if ( -1 != iLogId )
        {
            char szLogFileName[ _MAX_PATH ];
            GetLogName( iLogId, szLogFileName );
            szFileName = szLogFileName;
        }
        FILE* f = fopen( szFileName, "ab" ) ;
        if ( f )
        {
            fwrite( szBuffer, 1, strlen( szBuffer ), f ) ;
            fclose(f) ;
        }
        printf( szBuffer ) ;
    }
    _MY_CATCH
    {
        printf("a big error here");
    }

    g_log_lock.Unlock( ) ;
    return ;

__LEAVE_FUNCTION

    g_log_lock.Unlock( ) ;
    return ;
}

VOID Log::RemoveLog( CHAR* filename )
{
__ENTER_FUNCTION

    g_log_lock.Lock( ) ;

    FILE* f = fopen( filename, "w" ) ;
    fclose(f) ;

    g_log_lock.Unlock( ) ;
    return ;

__LEAVE_FUNCTION

    g_log_lock.Unlock( ) ;
    return ;
}

INT Log::GetLogId( CHAR* szBaseFileName )
{
    INT iLogId = -1
    for( INT i = 0; i < LOG_FILE_NUMBER; i++ )
    {
        if( szBaseFileName == g_pLogFileName[ i ] )
        {
            iLogId = i;
            break;
        }
    }
    return iLogId;
}
