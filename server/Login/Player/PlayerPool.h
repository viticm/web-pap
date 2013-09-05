/**
 * PAP Server Engine ( https://github.com/viticm/web-pap )
 * $Id PlayerPool.h
 * @link https://github.com/viticm/web-pap/tree/master/server for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-9-5 14:36:23
 * @uses the player pool module
 */
#ifndef __PLAYERPOOL_H__
#define __PLAYERPOOL_H__

#include "Type.h"
#include "LoginPlayer.h"

// 分配玩家数据的数据池

class PlayerPool
{   
public :
    PlayerPool() ;
    ~PlayerPool() ;

    //初始化数据池
    BOOL                Init( UINT MaxPlayerCount = MAX_POOL_SIZE ) ;
    
    //取得ShareMem的初始化
    //BOOL                PostInit();


    //根据玩家的PlayerID取得数据指针
    LoginPlayer*        GetPlayer( PlayerID_t PlayerID )
    {
        if ( INVALID_ID == PlayerID || PlayerID >= ( PlayerID_t )m_MaxPlayerCount || 0 > PlayerID )
            return NULL ;
        return &( m_pPlayer[ PlayerID ] ) ;
    } ;

    //从空闲数据池里分配一个玩家数据
    LoginPlayer*        NewPlayer() ;
    LoginPlayer*        NewPlayer( PlayerID_t PlayerID ) ;
    //将一个玩家数据清空回收
    VOID                DelPlayer( PlayerID_t PlayerID ) ;
private :
    LoginPlayer*        m_pPlayer ;
    UINT                m_Position ;
    MyLock              m_Lock ;
    UINT                m_PlayerCount ;
    UINT                m_MaxPlayerCount ;
    VOID                SetPosition( UINT pos ) ;
};

extern PlayerPool* g_pPlayerPool ;

#endif
