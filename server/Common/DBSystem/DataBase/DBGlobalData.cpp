#include "stdafx.h"
#include "DBGlobalData.h"
#include "ODBCInterface.h"
#include "SqlTemplate.h"
#include "DB_Struct.h"
#include "DBManager.h"

DBGlobalData::DBGlobalData( ODBCInterface* pInterface )
{
    mDBName            = CHARACTER_DATABASE ;
    mResult            = 0 ;
    mResultCount       = 0 ;
    Assert(pInterface);
    mInterface         = pInterface ;
}

BOOL DBGlobalData::Load()
{
    __ENTER_FUNCTION

        DB_QUERY* pQuery = GetInternalQuery() ;

        if ( !pQuery )
        {
            Assert( FALSE ) ;
        }

        pQuery->Clear() ;

        if( INVALID_ID == m_iPoolID )
        {
            return FALSE ;
        }

        pQuery->Parse( LoadGlobalData, GLOBAL_TABLE ) ;

        return ODBCBase::Load();

    __LEAVE_FUNCTION

        return FALSE;
}

BOOL DBGlobalData::Save( VOID* pSource )
{
    __ENTER_FUNCTION

        enum 
        {
            DB_PoolID = 1,
            DB_Data1,
        } ;


        Assert( pSource ) ;

        UINT  uData1 = *( ( UINT* )pSource ) ;

        //保存全局数据
        do
        {
            DB_QUERY* pQuery = GetInternalQuery() ;

            if ( !pQuery )
            {
                Assert( FALSE ) ;
            }

            pQuery->Clear() ;
        
            pQuery->Parse( SaveGlobalData, GLOBAL_TABLE, m_iPoolID, uData1 ) ;

            if ( !ODBCBase::Save( pSource ) )
                return FALSE ;

        } while ( 0 ) ;
    
        return TRUE ;

    __LEAVE_FUNCTION

        return FALSE ;
}

BOOL DBGlobalData::Delete()
{
    __ENTER_FUNCTION

        return TRUE ;

    __LEAVE_FUNCTION

        return FALSE ;
}

BOOL DBGlobalData::ParseResult( VOID* pResult )
{
    __ENTER_FUNCTION

        switch( mOPType )
        {
            case DB_LOAD:
            {
                Assert( pResult ) ;
                enum 
                {
                    DB_PoolID = 1,
                    DB_Data1,
                };

                Assert( mInterface );
                INT iErrorCode ;
                for( INT i = 0; 1 > i; i++ )
                {
                    if( !mInterface->Fetch() )
                        break ;
                    UINT iPoolID = mInterface->GetUInt( DB_PoolID, iErrorCode ) ;
                    *( ( UINT* )pResult ) = mInterface->GetUInt( DB_Data1, iErrorCode ) ;
                }
                mInterface->Clear() ;
            }
                break ;
            case DB_DELETE:
            {
    
            }
                break ;
            default:
                break ;
        }
    

        return TRUE ;

    __LEAVE_FUNCTION

        return FALSE ;
}

ID_t DBGlobalData::GetPoolID()
{
    return m_iPoolID ;
}

VOID DBGlobalData::SetPoolID( ID_t iPoolID )
{
    m_iPoolID = iPoolID ;
}

