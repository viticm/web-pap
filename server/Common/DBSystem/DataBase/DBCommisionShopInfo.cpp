#include "stdafx.h"
#include "DBCommisionShopInfo.h"
#include "ODBCInterface.h"
#include "SqlTemplate.h"
#include "DB_Struct.h"
#include "DBManager.h"
#include "GameStruct.h"
#include "SMUManager.h"

DBCommisionShopInfo::DBCommisionShopInfo( ODBCInterface* pInterface )
{
    mDBName            = CHARACTER_DATABASE ;
    mResult            = 0 ;
    mResultCount       = 0 ;
    m_iServerId        = INVALID_ID ;
    m_iWorldId         = INVALID_ID ;
    Assert(pInterface);
    mInterface         =    pInterface ;
}

BOOL DBCommisionShopInfo::Load()
{
    __ENTER_FUNCTION

        LONG_DB_QUERY* pQuery = GetLongInterQuery() ;
        if ( !pQuery )
        {
            Assert( FALSE ) ;
        }
        pQuery->Clear() ;

        pQuery->Parse( LoadCommisionShopInfo, CSHOP_TABLE ) ;

        return ODBCBase::LongLoad() ;

    __LEAVE_FUNCTION

        return FALSE ;
}

BOOL DBCommisionShopInfo::Save( VOID* pSource )
{
    __ENTER_FUNCTION

        enum 
        {
            DB_WorldId = 1,
            DB_ServerId,
            DB_PoolId,
            DB_CShopId,
        } ;

        INT iResult;
    
        SMUPool< CShopSMU >* pPoolPtr = static_cast< SMUPool< CShopSMU >* >( pSource ) ;
        Assert( pPoolPtr ) ;

        // 保存委托商店数据

        CSHOP_DB SaveCShop ;
        do
        {
            INT iSmuCount = pPoolPtr->GetPoolMaxSize();
            if ( MAX_CSHOP_SIZE < iSmuCount )
                Assert( FALSE ) ;

            INT iUseStats ;
            for ( INT i = 0; i < iSmuCount; i++ )
            {
                CShopSMU* pSMU = pPoolPtr->GetPoolObj( i ) ;
                if ( !pSMU )
                {
                    Assert( pSMU ) ;
                    return FALSE ;
                }

                iUseStats = pSMU->GetUseStatus( SM_C_READ ) ;
        
                pSMU->Lock( SM_C_READ ) ;
                CSHOP_DB* pCShop = &( pSMU->m_CShop );
                if ( NULL == pCShop )
                {
                    pSMU->UnLock( SM_C_READ ) ;
                    Assert( FALSE ) ;
                }
                
                memcpy( &SaveCShop, pCShop, sizeof( CSHOP_DB ) ) ;
                pSMU->m_SMUHead.UseStatus = CSHOP_SAVED ;

                if ( CSHOP_DELETE == iUseStats )
                {
                    pCShop->CleanUp() ;
                }

                pSMU->UnLock( SM_C_READ ) ;

                if ( INVALID_ID == SaveCShop.m_iServerId )
                    continue ;
                
            
                LONG_DB_QUERY* pQuery = GetLongInterQuery() ;
                
                if ( !pQuery )
                {
                    Assert( FALSE ) ;
                }
                pQuery->Clear();
                pQuery->Parse( SaveCommisionShopInfo,
                               SaveCShop.m_iWorldId,
                               SaveCShop.m_iServerId,
                               SaveCShop.m_iPoolId,
                               SaveCShop.m_iCShopId ) ;

                    if ( !ODBCBase::LongSave( &iResult ) )
                        return FALSE ;
                }

            } while( 0 ) ;
    
        return TRUE ;

    __LEAVE_FUNCTION

        return FALSE ;
}

BOOL DBCommisionShopInfo::Delete()
{
    __ENTER_FUNCTION

        return TRUE;

    __LEAVE_FUNCTION

        return FALSE;
}

BOOL DBCommisionShopInfo::ParseResult( VOID* pResult )
{
    __ENTER_FUNCTION

        switch ( mOPType )
        {
            case DB_LOAD:
            {
                SMUPool< CShopSMU >* pPoolPtr = static_cast< SMUPool < CShopSMU >* >( pResult ) ;
                Assert( pPoolPtr ) ;
                enum 
                {
                    DB_WorldId = 1,
                    DB_ServerId,
                    DB_PoolId,
                    DB_CShopId,
                } ;

                // 玩家商店数据
                Assert( mInterface ) ;
                INT iErrorCode ;
                INT iSmuCount = pPoolPtr->GetPoolMaxSize() ;
                INT iCShopIndex ;

                for ( INT i = 0; MAX_CSHOP_SIZE > i; i++ )
                {
                    if ( !mInterface->LongFetch() ) 
                        break ;

                    if ( i >= iSmuCount )
                        Assert( FALSE ) ;

                    iCShopIndex = mInterface->GetUInt( DB_ServerId, iErrorCode ) ;

                    if ( iCShopIndex >= iSmuCount )
                        Assert( FALSE ) ;

                    CShopSMU* pSMU = pPoolPtr->GetPoolObj( iCShopIndex ) ;
                    if ( !pSMU )
                    {
                        Assert( pSMU ) ;
                        return FALSE ;
                    }
                    CSHOP_DB* pCShop = &pSMU->m_CShop ;
                    Assert( pCShop ) ;
                
                    pCShop->m_iWorldId          = mInterface->GetInt( DB_WorldId, iErrorCode ) ;
                    pCShop->m_iServerId         = mInterface->GetInt( DB_ServerId, iErrorCode ) ;
                    pCShop->m_iPoolId           = mInterface->GetInt( DB_PoolId, iErrorCode ) ;
                    pCShop->m_iCShopId          = mInterface->GetInt( DB_CShopId, iErrorCode ) ;

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

VOID DBCommisionShopInfo::SetServerId( ID_t iServerId )
{
    m_iServerId = iServerId ;
}

ID_t DBCommisionShopInfo::GetServerId()
{
    return m_iServerId ;
}

VOID DBCommisionShopInfo::SetWorldId( ID_t iWorldId )
{
    m_iWorldId = iWorldId ;
}

ID_t DBCommisionShopInfo::GetWorldId()
{
    return m_iWorldId ;
}
