#include "DBGeneralSet.h"

INT DBGeneralSet::GetValue( const CHAR* szKeyName )
{
    __ENTER_FUNCTION

        Assert( g_pDBManager ) ;
        CHAR szSqlStr[ MAX_SQL_LENGTH ] = { 0 } ;
        sprintf( szSqlStr, "SELECT `nVal` FROM `t_general_set` WHERE `sKey` = '%s'", szKeyName ) ;
        ODBCInterface* pInterface = g_pDBManager->GetInterface( CHARACTER_DATABASE ) ;
        strcpy( ( CHAR* )pInterface->m_Query.m_SqlStr, szSqlStr ) ;
        pInterface->Clear() ;
        if( pInterface->Execute() )
        {
            pInterface->Fetch() ;

            if( 0 < pInterface->mAffectCount )
            {
                INT iValue = atoi( pInterface->Col[ 0 ] ) ;
                return iValue ;
            }
            return ERROR_VALUE ;
        }
        else
        {
            return ERROR_VALUE ;
        }
    
    __LEAVE_FUNCTION 
        
        return ERROR_VALUE ;
}
