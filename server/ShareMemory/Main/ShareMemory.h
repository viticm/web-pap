/**
 * PAP Server Engine ( https://github.com/viticm/web-pap )
 * $Id ShareMemory.h
 * @link https://github.com/viticm/web-pap/tree/master/server for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-8-15 14:39:05
 * @uses the main file for share memory
 */

#ifndef __SHAREMEMORY_H__
#define __SHAREMEMORY_H__

#include "Type.h"
#include "SMUManager.h"
#include "Config.h"

class ShareMemory
{
    struct SMUPool_T 
    {
        _SHAREMEM_DATA    m_Data ;
        VOID*             m_Pool ;

        SMUPool_T()
        {
            m_Pool    =    NULL ;
        }
    } ;


    struct SMUManager_T
    {
        VOID*                m_SMULogicManager ;
        SHAREMEM_TYPE        m_Type ;
        SMUManager_T()
        {
            m_Type                = ST_INVAILD ;
            m_SMULogicManager     =    0 ;
        }
    };
public :
    ShareMemory() ;
    ~ShareMemory() ;



    BOOL        Init() ;
    BOOL        Loop() ;
    BOOL        Exit() ;

    BOOL        DoWork() ;

    VOID        ConsoleCommand() ;


protected :
    BOOL                    NewStaticManager() ;
    BOOL                    InitStaticManager() ;
    BOOL                    DelStaticManager() ;
    BOOL                    CheckWorldIDZoneID() ; 

private:

    SMUPool_T                m_SMUPool[ MAX_SM_OBJ_NUM ] ;
    SMUManager_T             m_SMULogicManager[ MAX_SM_OBJ_NUM ] ;

    BOOL                     m_bExited ;

};

extern ShareMemory g_ShareMemory ;
extern INT           g_CmdArgv ;
extern INT           g_CmdInput ;


class ShmExceptionHandler
{
public:
    ShmExceptionHandler();
};

extern ShmExceptionHandler g_ShmExceptionHandler;

#endif
