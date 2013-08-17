#include "DBGeneralSet.h"

INT DBGeneralSet::GetValue( const CHAR* szKeyName )
{
    __ENTER_FUNCTION

        Assert( g_pDBManager ) ;
        CHAR szSqlStr[ MAX_SQL_LENGTH ] = { 0 } ;
        sprintf( szSqlStr, "SELECT `sVal` FROM `t_general_set` WHERE `sKey` = '%s'" ) ;

        strcpy( ( CHAR* )g_pDBManager->GetInterface( CHARACTER_DATABASE )->m_Query.m_SqlStr, szSqlStr ) ;
        g_pDBManager->GetInterface( CHARACTER_DATABASE )->Clear() ;
        if( g_pDBManager->GetInterface( CHARACTER_DATABASE )->Execute() )
        {
            if( g_pDBManager->GetInterface( CHARACTER_DATABASE )->mAffectCount > 0 )
            {
                LERR( "sVal: %d, sKey: %s", g_pDBManager->GetInterface( CHARACTER_DATABASE )->Col[ 0 ][ 0 ], szKeyName ) ;
                return TRUE ;
            }
        }
        else
        {
            return FALSE ;
        }
    
    __LEAVE_FUNCTION 
}
