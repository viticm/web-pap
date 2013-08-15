/**
 * PAP Server Engine ( https://github.com/viticm/web-pap )
 * $Id ShareDBManager.h
 * @link https://github.com/viticm/web-pap/tree/master/server for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-8-15 14:39:05
 * @uses the Command moudles for share memory
 */
#ifndef __COMMANDTHREAD_H__
#define __COMMANDTHREAD_H__

#include "Type.h"
#include "Thread.h"

//用来处理命令行数据
class CommandThread : public Thread
{
public :
    CommandThread(){ m_Active = TRUE ; } 
    ~CommandThread(){} ;

    //主循环
    virtual VOID    run() ;

    //停止线程执行
    virtual VOID    stop() { m_Active = FALSE ; } ;

    //判断当前线程是否激活
    BOOL            IsActive(){ return m_Active ; } ;

    GLOBAL_CONFIG    m_SMConfig ;    
private :
    BOOL            m_Active ;
    
} ;


extern CommandThread g_CommandThread;

class CmdParser
{
public:
    static  BOOL    HandleInput();

private:
    static SM_COMMANDS_STATE        ParserCommandType(CHAR* pBuff);
};

#endif
