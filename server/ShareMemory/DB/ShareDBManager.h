/**
 * PAP Server Engine ( https://github.com/viticm/web-pap )
 * $Id ShareDBManager.h
 * @link https://github.com/viticm/web-pap/tree/master/server for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-8-15 14:39:05
 * @uses the share database manager for sharememory model
 */
#include "stdafx.h"
#include "Config.h"
#include "ODBCInterface.h"
#include "TimeManager.h"
#include "Log.h"

#ifndef _SHARE_DB_MANAGER_H_
#define _SHARE_DB_MANAGER_H_

#include "DBManager.h"

class ShareDBManager :public DBManager
{

public:
    virtual  BOOL    Init() ;
    virtual  VOID    run() ;

};

#endif


