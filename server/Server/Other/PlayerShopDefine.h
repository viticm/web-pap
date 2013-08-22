#ifndef _PLAYER_SHOP_DEFINE_H_
#define _PLAYER_SHOP_DEFINE_H_
#include "Type.h"
#include "DB_Struct.h"
#include "Record.h"
#define MAX_PLAYER_SHOP_POOL_PER_SERVER    1000

namespace PLAYER_SHOP
{
    //-------------------------------------------------------------------------------------------------
    //枚举定义
    enum STATUS_PLAYER_SHOP
    {
        STATUS_PLAYER_SHOP_INVALID = 0,        // 无效，还没有分配出去
        STATUS_PLAYER_SHOP_CLOSE,              // 打烊，店主暂时关闭该店
        STATUS_PLAYER_SHOP_OPEN,               // 开张，店主正在经营此店
        STATUS_PLAYER_SHOP_SHUT_DOWN,          // 倒闭，经营不善导致被系统强行关闭
        STATUS_PLAYER_SHOP_ON_SALE,            // 被盘出，别人可以自由买卖此商店
    } ;
    enum TYPE_PLAYER_SHOP
    {
        TYPE_PLAYER_SHOP_INVALID = 0,         // 无效类别，还没有分配出去
        TYPE_PLAYER_SHOP_ITEM,                // 物品店
        TYPE_PLAYER_SHOP_GEM,                 // 宝石店
        TYPE_PLAYER_SHOP_WEAPON,              // 武器店
        TYPE_PLAYER_SHOP_ARMOR,               // 护甲店
        TYPE_PLAYER_SHOP_MATERIAL,            // 材料店
        TYPE_PLAYER_SHOP_PET,                 // 宠物店
    } ;
    enum TYPE_STALL
    {
        TYPE_STALL_INVALID = 0,               // 无效类别，还没有分配出去
        TYPE_STALL_ITEM,                      // 物品柜台
        TYPE_STALL_PET,                       // 宠物柜台
    } ;
    enum RET_TYPE_PARTNER
    {
        RET_TYPE_INVALID = -1,                // 非法错误
        RET_TYPE_ALREADY_IN_LIST,             // 合作者已在列表中
        RET_TYPE_NOT_FIND_IN_WORLD,           // 合作者没有找到
        RET_TYPE_NOT_FIND_IN_LIST,            // 合作者不在列表
        RET_TYPE_LIST_FULL,                   // 列表已满
        RET_TYPE_LIST_EMPTY,                  // 列表已满
        RET_TYPE_SUCCESS,                     // 操作成功
    };

    //-------------------------------------------------------------------------------------------------
    //数据结构
    //供数据库访问的柜台结构
    struct StallBoxDB_t
    {
        struct StallData 
        {
            UINT            m_nFirstPage;                            //起始页
            BOOL            m_bItemIsOnSale[STALL_BOX_SIZE];        //标示该位置的商品是否上架
            UINT            m_ItemPrice[STALL_BOX_SIZE];            //标示该位置的商品的价格
            _ITEM            m_ItemList[STALL_BOX_SIZE];                //物品数据
            _PET_DB_LOAD    m_PetList[STALL_PET_BOX_SIZE];            //宠物数据
        };

        BYTE            m_StallStatus;                            //当前柜台的状态（开张，打烊，开放）
        BYTE            m_StallType;                            //当前柜台的类型（物品1，宠物2）
        UINT            m_nFirstPage;                            //起始页
        BOOL            m_bItemIsOnSale[STALL_BOX_SIZE];        //标示该位置的商品是否上架
        UINT            m_ItemPrice[STALL_BOX_SIZE];            //标示该位置的商品的价格
        _ITEM            m_ItemList[STALL_BOX_SIZE];                //物品数据
        _PET_DB_LOAD    m_PetList[STALL_PET_BOX_SIZE];            //宠物数据

        VOID CleanUp()
        {
            memset(this, 0, sizeof(StallBoxDB_t));
            m_StallType    = 1;                                    //默认是物品柜台
        }
    };

    //合作伙伴
    struct Partner_t
    {
        GUID_t        m_Guid;
        CHAR        m_szName[MAX_CHARACTER_NAME];
        VOID        CleanUp()
        {
            m_Guid = INVALID_GUID;
            memset(m_szName, 0, MAX_CHARACTER_NAME);
        }
    };

    //供数据库访问的商店结构
    struct PlayerShopDB_t
    {
        BYTE                            m_ShopStatus;                                //此商店所处的状态
        BYTE                            m_ShopType;                                    //商店类别
        _PLAYERSHOP_GUID                m_ShopGUID;                                    //每个商店的唯一ID
        UINT                            m_MaxBaseMoney;                                //商店本金上限
        UINT                            m_BaseMoney;                                //商店本金
        UINT                            m_ProfitMoney;                                //商店盈利金
        BYTE                            m_FoundedSec;                                //开店的时间
        BYTE                            m_FoundedMin;                                //开店的时间
        BYTE                            m_FoundedHour;                                //开店的时间
        BYTE                            m_FoundedDay;                                //开店的时间
        BYTE                            m_FoundedMonth;                                //开店的时间
        UINT                            m_FoundedYear;                                //开店的时间
        CHAR                            m_szShopName[MAX_SHOP_NAME_SIZE];            //标示商店名
        CHAR                            m_szShopDesc[MAX_SHOP_DESC_SIZE];            //标示商店的描述
        CHAR                            m_szOwnerName[MAX_CHARACTER_NAME];            //标示店主名
        GUID_t                          m_OwnerGuid;                                //店主guid
        BYTE                            m_NumStallOpened;                            //已经开放的柜台数
        BYTE                            m_NumStallOnSale;                            //已经开张的柜台数
        UINT                            m_uSaleOutPrice;                            //盘出价格
        StallBoxDB_t                    m_StallListData[MAX_STALL_NUM_PER_SHOP];    //柜台数据列表
        //ServerBBS                        m_StallBBS;                                    //商店留言板
        RecordContainer_t               m_ExchangeRecord;                            //交易记录
        RecordContainer_t               m_ManagerRecord;                            //管理记录
        Partner_t                       m_PartnerList[MAX_PARTNER_PER_SHOP];        //合作伙伴
        BYTE                            m_PartnerNum;

        VOID CleanUp()
        {
 
            m_ShopStatus        =    0 ;                                                // 此商店所处的状态
            m_ShopType          =    0 ;                                                // 商店类别
            m_MaxBaseMoney      =    0 ;                                                // 商店本金上限
            m_BaseMoney         =    0 ;                                                // 商店本金
            m_ProfitMoney       =    0 ;                                                // 商店盈利金
            m_FoundedSec        =    0 ;                                                // 开店的时间
            m_FoundedMin        =    0 ;                                                // 开店的时间
            m_FoundedHour       =    0 ;                                                // 开店的时间
            m_FoundedDay        =    0 ;                                                // 开店的时间
            m_FoundedMonth      =    0 ;                                                // 开店的时间
            m_FoundedYear       =    0 ;                                                // 开店的时间
            memset( m_szShopName, 0, MAX_SHOP_NAME_SIZE ) ;                             // 标示商店名
            memset( m_szShopDesc, 0, MAX_SHOP_DESC_SIZE ) ;                             // 标示商店的描述
            memset( m_szOwnerName, 0, MAX_CHARACTER_NAME ) ;                            // 标示店主名
            m_OwnerGuid         =    INVALID_ID ;                                       // 店主guid
            m_NumStallOpened    =    0 ;                                                // 已经开放的柜台数
            m_NumStallOnSale    =    0 ;                                                // 已经开张的柜台数
            m_uSaleOutPrice     =    0 ;                                                // 盘出价格
            for ( UINT i = 0; MAX_STALL_NUM_PER_SHOP > i; i++ )
            {
                m_StallListData[i].CleanUp() ;                                          // 柜台数据列表
            }
            for ( UINT i = 0; MAX_PARTNER_PER_SHOP > i; i++ )
            {
                m_PartnerList[i].CleanUp() ;                                            // 合作伙伴
            }
            m_PartnerNum = 0;
            //m_StallBBS.CleanUp();                                                    //柜台留言板
            //m_ExchangeRecord.CleanUp();                                                //交易记录
            //m_ManagerRecord.CleanUp();                                                //管理记录
            m_ShopGUID.Reset() ;
        }
    } ;

    struct PLAYER_SHOP_DB
    {
        INT                m_iSID ;                                                // 标识ID
        INT                m_iPoolID ;                                             // 区间ID
        CHAR               m_szShopGuid[ MAX_PLAYER_SHOP_GUID_SIZE ] ;             // 商店guid   
        INT                m_iType ;                                               // 商店类型
        INT                m_iStat ;                                               // 
        INT                m_iMaxbMoney ;                                          // 
        INT                m_iBaseMoney ;                                          //
        INT                m_iCreateTime ;                                         // 建立时间
        CHAR               m_szShopName[ MAX_PLAYER_SHOP_NAME_SIZE ] ;             // 商店名称
        CHAR               m_szShopDesc[ MAX_PLAYER_SHOP_DESC_SIZE ] ;             // 商店描述
        CHAR               m_szOwnerName[ MAX_CHARACTER_NAME ] ;                   // 拥有者名称
        INT                m_iOwnerGuid ;                                          // 拥有者GUID
        INT                m_iIsOpen ;                                             // 是否开放
        INT                m_iSale ;                                               // 
        INT                m_iSalePrice ;                                          // 出售价格
        CHAR               m_szPartner[ MAX_PLAYER_SHOP_PARTNER_SIZE ] ;           // 合作伙伴
        CHAR               m_szRecoder[ MAX_PLAYER_SHOP_RECODER_SIZE ] ;           // 
        INT                m_iIsValid ;                                            // 验证情况
        INT                m_iPartNum ;                                            //
        INT                m_iSubType ;                                            //
        INT                m_iProfit ;                                             //
        INT                m_iFreeze ;                                             //
        CHAR               m_szBuyDesc[ MAX_PLAYER_SHOP_BUY_DESC_SIZE ] ;          //
        CHAR               m_szBuyReserver[ MAX_PLAYER_SHOP_BUY_RESERVER_SIZE ] ;  //

        PLAYER_SHOP_DB()
        {
            CleanUp() ;    
        }

        VOID CleanUp()
        {
            m_iSID     = INVALID_ID ;
            m_iPoolID  = INVALID_ID ;
            memset( m_szShopGuid, 0, MAX_PLAYER_SHOP_GUID_SIZE * sizeof( CHAR ) ) ;
            memset( m_szShopName, 0, MAX_PLAYER_SHOP_NAME_SIZE * sizeof( CHAR ) ) ;
            memset( m_szShopDesc, 0, MAX_PLAYER_SHOP_DESC_SIZE * sizeof( CHAR ) ) ;
            memset( m_szOwnerName, 0, MAX_CHARACTER_NAME * sizeof( CHAR ) ) ;
            memset( m_szPartner, 0, MAX_PLAYER_SHOP_PARTNER_SIZE * sizeof( CHAR ) ) ;
            memset( m_szRecoder, 0, MAX_PLAYER_SHOP_RECODER_SIZE * sizeof( CHAR ) ) ;
            memset( m_szBuyDesc, 0, MAX_PLAYER_SHOP_BUY_DESC_SIZE * sizeof( CHAR ) ) ;
            memset( m_szBuyReserver, 0, MAX_PLAYER_SHOP_BUY_RESERVER_SIZE * sizeof( CHAR ) ) ;
        }
    } ;
    enum PLAYER_SHOP_USE_STATS
    {
        PLAYER_SHOP_ADDNEW    =0,        // 新加的需要保存
        PLAYER_SHOP_DELETE,              // 删除的需要保存
        PLAYER_SHOP_SAVED,               // 已经保存过
    } ;


    struct PlayerShopSM
    {
        SMUHead            m_SMUHead ;
        PlayerShopDB_t     m_PlayerShop ;
        PLAYER_SHOP_DB     m_PlayerShopDb ;

        VOID Lock( CHAR Type )
        {
            sm_lock( m_SMUHead.flag, Type ) ;
        }

        VOID UnLock( CHAR Type )
        {
            sm_unlock( m_SMUHead.flag, Type ) ;
        }
    
        VOID SetPoolID( UINT poolID )
        {
            m_SMUHead.PoolId = poolID ;
        }    

        UINT GetPoolID()
        {
            return m_SMUHead.PoolId ;
        }
    
        BOOL SetUseStatus( INT Use, CHAR Type )
        {
            Lock( Type ) ;
            m_SMUHead.UseStatus = Use ;
            UnLock( Type ) ;
            return TRUE ;
        }
    
        INT GetUseStatus( CHAR Type )
        {
            INT iRet ;
            Lock( Type ) ;
            iRet = m_SMUHead.UseStatus ;
            UnLock( Type ) ;
            return iRet ;
        }
    
        UINT GetTime2Save( CHAR Type )
        {
            UINT uTime ;
            Lock( Type ) ;
            uTime = m_SMUHead.SaveTime ;
            UnLock( Type ) ;
            return uTime ;
        }

        VOID SetTime2Save( UINT uTime, CHAR Type )
        {
            Lock( Type ) ;
            m_SMUHead.SaveTime = uTime ;
            UnLock( Type ) ;
        }

        VOID Init()
        {
            m_PlayerShop.CleanUp() ;
            m_PlayerShopDb.CleanUp() ;
        }
    } ;
};
#endif;
