#include "DBGeneralSet.h"

INT DBGeneralSet::GetValue( const CHAR* szKeyName )
{
    __ENTER_FUNCTION

        Assert( g_pDBManager ) ;
        sprinf( m_szSqlStr, "SELECT * FROM `t_general_set`" ) ;

        strcpy( ( CHAR* )g_pDBManager->GetInterface( USER_DATABASE )->m_Query.m_SqlStr, m_strSql) ;
        g_pDBManager->GetInterface( USER_DATABASE )->Clear() ;
        if( g_pDBManager->GetInterface( USER_DATABASE )->Execute() )
        {
            if( g_pDBManager->GetInterface( USER_DATABASE )->mAffectCount > 0 )
                return TRUE ;
        }
        else
        {
            return FALSE ;
        }
    
    __LEAVE_FUNCTION 
}
