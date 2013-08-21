#include "stdafx.h"
#include "DBPlayerShopInfo.h"
#include "ODBCInterface.h"
#include "SqlTemplate.h"
#include "DB_Struct.h"
#include "DBManager.h"
#include "GameStruct.h"
#include "SMUManager.h"
#include "PlayerShopDefine.h"

using namespace PLAYER_SHOP ;

DBPlayerShopInfo::DBPlayerShopInfo( ODBCInterface* pInterface )
{
    mDBName            = CHARACTER_DATABASE ;
    mResult            = 0 ;
    mResultCount       = 0 ;
    Assert(pInterface);
    mInterface         =    pInterface ;
}

BOOL DBPlayerShopInfo::Load()
{
    __ENTER_FUNCTION

        LONG_DB_QUERY* pQuery = GetLongInterQuery() ;
        if ( !pQuery )
        {
            Assert( FALSE ) ;
        }
        pQuery->Clear() ;

        pQuery->Parse( LoadPlayerShopInfo, PLAYER_SHOP_TABLE ) ;

        return ODBCBase::LongLoad() ;

    __LEAVE_FUNCTION

        return FALSE ;
}

BOOL DBPlayerShopInfo::Save( VOID* pSource )
{
    __ENTER_FUNCTION

        enum 
        {
            DB_SID    =    1,
            DB_PoolID,
            DB_ShopGuid,
            DB_Type,
            DB_Stat,
            DB_MaxbMoney,
            DB_BaseMoney,
            DB_CreateTime,
            DB_ShopName,
            DB_ShopDesc,
            DB_OwnerName,
            DB_OwnerGuid,
            DB_IsOpen,
            DB_Sale,
            DB_SalePrice,
            DB_Partner,
            DB_Recoder,
            DB_IsValid,
            DB_PartNum,
            DB_SubType,
            DB_Profit,
            DB_Freeze,
            DB_BuyDesc,
            DB_BuyReserver,
        } ;

        INT Result;
    
        SMUPool< PlayerShopSM >* pPoolPtr = static_cast< SMUPool< PlayerShopSM >* >( pSource ) ;
        Assert( pPoolPtr ) ;

        // 保存玩家商店数据

        PLAYER_SHOP_DB SavePlayerShop;
        do
        {
            INT SmuCount = pPoolPtr->GetPoolMaxSize();
            if ( MAX_GUILD_SIZE < SmuCount )
                Assert( FALSE ) ;

            INT UseStats ;
            for (INT i = 0; i < SmuCount; i++ )
            {
                PlayerShopSM* pSMU = pPoolPtr->GetPoolObj( i ) ;
                if ( !pSMU )
                {
                    Assert( pSMU ) ;
                    return FALSE ;
                }

                UseStats = pSMU->GetUseStatus( SM_C_READ ) ;
        
                pSMU->Lock( SM_C_READ ) ;
                PLAYER_SHOP_DB* pPlayerShop = &( pSMU->m_PlayerShopSM );
                if ( NULL = pPlayerShop )
                {
                    pSMU->UnLock( SM_C_READ ) ;
                    Assert( FALSE ) ;
                }
                
                memcpy( &SavePlayerShop, pPlayerShop, sizeof( PLAYER_SHOP_DB ) ) ;
                pSMU->m_SMUHead.UseStatus = GUILD_SAVED ;
                if ( PLAYER_SHOP_DELETE == UseStats )
                {
                    pPlayerShop->CleanUp() ;
                }

                pSMU->UnLock( SM_C_READ ) ;

                if ( INVALID_ID == SavePlayerShop.m_iSID )
                    continue ;
                
            
                LONG_DB_QUERY* pQuery = GetLongInterQuery() ;
                if ( !pQuery )
                {
                    Assert( FALSE ) ;
                }
                pQuery->Clear();
                pQuery->Parse( SavePlayerShopInfo,
                               SavePlayerShop.m_iSID,
                               SavePlayerShop.m_iPoolID,
                               SavePlayerShop.m_szShopGuid,
                               SavePlayerShop.m_iType,
                               SavePlayerShop.m_iStat,
                               SavePlayerShop.m_iMaxbMoney,
                               SavePlayerShop.m_iBaseMoney,
                               SavePlayerShop.m_iProfit,
                               SavePlayerShop.m_iCreateTime,
                               SavePlayerShop.m_szShopName,
                               SavePlayerShop.m_szShopDesc,
                               SavePlayerShop.m_szOwnerName,
                               SavePlayerShop.m_iOwnerGuid,
                               SavePlayerShop.m_iIsOpen,
                               SavePlayerShop.m_iSale,
                               SavePlayerShop.m_iSalePrice,
                               SavePlayerShop.m_szPartner,
                               ( ( PLAYER_SHOP_DELETE != UseStats ) ? 1 : 0 ),
                               SavePlayerShop.m_iPartNum,
                               SavePlayerShop.m_iSubType,
                               SavePlayerShop.m_iFreeze )

                    if ( !ODBCBase::LongSave( &Result ) )
                        return FALSE ;
                }

            } while( 0 ) ;
    
    
        return TRUE ;

    __LEAVE_FUNCTION

        return FALSE ;
}

BOOL DBPlayerShopInfo::Delete()
{
    __ENTER_FUNCTION

        return TRUE;

    __LEAVE_FUNCTION

        return FALSE;
}

BOOL DBPlayerShopInfo::ParseResult( VOID* pResult )
{
    __ENTER_FUNCTION

        switch ( mOPType )
        {
            case DB_LOAD:
            {
                SMUPool<GuildSMU>* pPoolPtr = static_cast<SMUPool<GuildSMU>*>(pResult);
                Assert(pPoolPtr);
                enum 
                {
                    DB_SID    =    1,
                    DB_PoolID,
                    DB_ShopGuid,
                    DB_Type,
                    DB_Stat,
                    DB_MaxbMoney,
                    DB_BaseMoney,
                    DB_CreateTime,
                    DB_ShopName,
                    DB_ShopDesc,
                    DB_OwnerName,
                    DB_OwnerGuid,
                    DB_IsOpen,
                    DB_Sale,
                    DB_SalePrice,
                    DB_Partner,
                    DB_Recoder,
                    DB_IsValid,
                    DB_PartNum,
                    DB_SubType,
                    DB_Profit,
                    DB_Freeze,
                    DB_BuyDesc,
                    DB_BuyReserver,
                } ;

                // 玩家商店数据
                Assert( mInterface ) ;
                INT iErrorCode ;
                INT iSmuCount = pPoolPtr->GetPoolMaxSize() ;
                INT iPlayerShopIndex ;

                for ( INT i = 0; MAX_GUILD_SIZE > i; i++ )
                {
                    if ( !mInterface->LongFetch() ) 
                        break ;

                    if ( i >= iSmuCount )
                        Assert( FALSE ) ;

                    iPlayerShopIndex = mInterface->GetUInt( DB_SID, ErrorCode ) ;

                    if ( iPlayerShopIndex >= iSmuCount )
                        Assert( FALSE ) ;

                    PlayerShopSM* pSMU = pPoolPtr->GetPoolObj( iPlayerShopIndex ) ;
                    if ( !pSMU )
                    {
                        Assert( pSMU ) ;
                        return FALSE ;
                    }
                    PLAYER_SHOP_DB* pPlayerShop = &pSMU->m_PlayerShopSM ;
                    Assert( pPlayerShop ) ;
                
                    pPlayerShop->m_iSID         = mInterface->GetInt( DB_SID, iErrorCode ) ;
                    pPlayerShop->m_iPoolID      = mInterface->GetInt( DB_PoolID, iErrorCode ) ;
                    mInterface->GetString( DB_ShopGuid, pPlayerShop->m_szShopGuid, MAX_PLAYER_SHOP_GUID_SIZE,
                        iErrorCode ) ;
                    pPlayerShop->m_iType        = mInterface->GetInt( DB_Type, iErrorCode ) ;
                    pPlayerShop->m_iStat        = mInterface->GetInt( DB_Stat, iErrorCode ) ;
                    pPlayerShop->m_iMaxbMoney   = mInterface->GetInt( DB_MaxbMoney, iErrorCode ) ;
                    pPlayerShop->m_iBaseMoney   = mInterface->GetInt( DB_BaseMoney, iErrorCode ) ;
                    pPlayerShop->m_iCreateTime  = mInterface->GetInt( DB_CreateTime, iErrorCode ) ;
                    mInterface->GetString( DB_ShopName, pPlayerShop->m_szShopName, MAX_PLAYER_SHOP_NAME_SIZE,
                        iErrorCode ) ;
                    mInterface->GetString( DB_ShopDesc, pPlayerShop->m_szShopDesc, MAX_PLAYER_SHOP_DESC_SIZE,
                        iErrorCode ) ;
                    mInterface->GetString( DB_OwnerName, pPlayerShop->m_szOwnerName, MAX_CHARACTER_NAME,
                        iErrorCode ) ;
                    pPlayerShop->m_iOwnerGuid   = mInterface->GetInt( DB_OwnerGuid, iErrorCode ) ;
                    pPlayerShop->m_iIsOpen      = mInterface->GetInt( DB_IsOpen, iErrorCode ) ;
                    pPlayerShop->m_iSale        = mInterface->GetInt( DB_Sale, iErrorCode ) ;
                    pPlayerShop->m_iSalePrice   = mInterface->GetInt( DB_SalePrice, iErrorCode ) ;
                    mInterface->GetString( DB_Partner, pPlayerShop->m_szPartner, MAX_PLAYER_SHOP_PARTNER_SIZE,
                        iErrorCode ) ;
                    mInterface->GetString( DB_Recoder, pPlayerShop->m_szRecoder, MAX_PLAYER_SHOP_RECODER_SIZE,
                        iErrorCode ) ;
                    pPlayerShop->m_iIsValid     = mInterface->GetInt( DB_IsValid, iErrorCode ) ;
                    pPlayerShop->m_iPartNum     = mInterface->GetInt( DB_PartNum, iErrorCode ) ;
                    pPlayerShop->m_iSubType     = mInterface->GetInt( DB_SubType, iErrorCode ) ;
                    pPlayerShop->m_iProfit      = mInterface->GetInt( DB_Profit, iErrorCode ) ;
                    pPlayerShop->m_iFreeze      = mInterface->GetInt( DB_Freeze, iErrorCode ) ;
                    mInterface->GetString( DB_BuyDesc, pPlayerShop->m_szBuyDesc, MAX_PLAYER_SHOP_BUY_DESC_SIZE,
                        iErrorCode ) ;
                    mInterface->GetString( DB_BuyReserver, pPlayerShop->m_szBuyReserver, MAX_PLAYER_SHOP_BUY_RESERVER_SIZE,
                        iErrorCode ) ;
                    pSMU->SetUseStatus( PLAYER_SHOP_SAVED, SM_C_WRITE ) ;

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
