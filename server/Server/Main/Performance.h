/**
 * PAP Server Engine ( https://github.com/viticm/web-pap )
 * $Id Performance.h
 * @link https://github.com/viticm/web-pap/tree/master/server for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-8-27 11:06:59
 * @uses Saving and statistical systems and the efficiency of each module operation
 */

#ifndef __PERFORMANCE_H__
#define __PERFORMANCE_H__

#include "Type.h"

#define MAX_PERFOR_SIZE 1024

enum SCENE_PERFOR_TYPE
{
    SPT_TICK_LOGIC = 0 ,
    SPT_TICK_SELECT ,
    SPT_TICK_PROCESSEXCEPTIONS ,
    SPT_TICK_PROCESSINPUTS ,
    SPT_TICK_PROCESSOUTPUTS ,
    SPT_TICK_PROCESSCOMMANDS ,
    SPT_TICK_PROCESSCACHECOMMANDS ,
    SPT_TICK_HEARTBEAT ,

    SPT_HEARTBEAT_CLOSELOGIC ,
    SPT_HEARTBEAT_SCENETIMER ,
    SPT_HEARTBEAT_SCENEPLAYERMANAGER ,
    SPT_HEARTBEAT_HUMANMANAGER ,
    SPT_HEARTBEAT_MONSTERMANAGER ,
    SPT_HEARTBEAT_PETMANAGER ,
    SPT_HEARTBEAT_ITEMBOXMANAGER ,
    SPT_HEARTBEAT_SPECIALMANANGER ,
    SPT_HEARTBEAT_GROWPOINTGROUP ,
    SPT_HEARTBEAT_CHATPIPE ,
    SPT_HEARTBEAT_PLAYERSHOP, 
    SPT_HEARTBEAT_SCENETIMERS ,
    SPT_HEARTBEAT_RECYCLEPLAYERMANAGER ,


    SPT_NUMBER ,
};

struct SCENE_PERFOR
{
    UINT            m_aPerfor[ SPT_NUMBER ] ;    // 各个位置的响应值
    SceneID_t       m_SceneID ;                  // 监控的场景号

    SCENE_PERFOR()
    {
        m_SceneID = INVALID_ID ;
        for( INT i = 0; SPT_NUMBER > i; i++ )
        {
            m_aPerfor[ i ] = 0 ;
        }
    }
} ;


class PerformanceManager
{
public :
    PerformanceManager() ;
    ~PerformanceManager() ;

    VOID            CleanUp() ;

    BOOL            Init() ; // 初始化

    BOOL            HeartBeat( UINT uTime ) ; // 心跳逻辑处理

    INT             Scene2Index( SceneID_t sceneid ) ; // 场景号映射到性能数据块索引

    VOID            CompareScenePerformance( INT index ) ; // 处理一个场景的数据信息


public :
    INT                m_PerforCount ;
    SCENE_PERFOR       m_aPerforData[ MAX_PERFOR_SIZE ] ;
    INT                m_aHash[ MAX_SCENE ] ;

    CMyTimer        m_OperateTime ;

};

extern PerformanceManager* g_pPerformanceManager ;

class ShareMemoryNotifyer
{
public:
    ShareMemoryNotifyer(){} ;
    ~ShareMemoryNotifyer(){} ;
    
    BOOL        HeartBeat(UINT uTime) ;

};

extern ShareMemoryNotifyer g_ShareMemNotifyer ;

#endif
