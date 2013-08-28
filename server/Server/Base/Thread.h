/**
 * PAP Server Engine ( https://github.com/viticm/web-pap )
 * $Id Thread.h
 * @link https://github.com/viticm/web-pap/tree/master/server for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-8-28 23:09:01
 * @uses the thread base module
 */

#ifndef __THREAD_H__
#define __THREAD_H__

#include "Type.h"




//当定义此宏时，所有线程将只执行一次后就推出。
//#define _EXEONECE 10
class Thread 
{

public :
    
    enum ThreadStatus 
    {
        READY ,      // 当前线程处于准备状态
        RUNNING ,    // 处于运行状态
        EXITING ,    // 线程正在退出
        EXIT         // 已经退出 
    };
    
public :

    // constructor
    Thread() ;

    // destructor
    virtual ~Thread() ;



public :

    VOID start() ;
    virtual VOID stop() ;

    VOID exit( VOID * retval = NULL ) ;
    virtual VOID run() ;


public :
    // get thread identifier
    TID getTID() { return m_TID; }
    
    // get/set thread's status
    ThreadStatus getStatus() { return m_Status; }
    VOID setStatus( ThreadStatus status ) { m_Status = status; }

private :

    // thread identifier variable
    TID m_TID;
    
    // thread status
    ThreadStatus m_Status;

#if defined( __WINDOWS__ )
    HANDLE m_hThread ;
#endif

};

extern UINT g_QuitThreadCount ;

#if defined( __LINUX__ )
VOID * MyThreadProcess ( VOID * derivedThread ) ;
#elif defined( __WINDOWS__ )
DWORD WINAPI MyThreadProcess(  VOID* derivedThread ) ;
#endif

#endif
