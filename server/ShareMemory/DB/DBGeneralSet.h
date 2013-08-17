/**
 * PAP Server Engine ( https://github.com/viticm/web-pap )
 * $Id ShareDBManager.h
 * @link https://github.com/viticm/web-pap/tree/master/server for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-8-16 19:46:32
 * @uses the char db general set moudle
 */
#pragma once
#include "ShareDBManager.h"

#define WORLD_ID    "WORLD_ID"
#define ZONE_ID     "ZONE_ID"
#define UNUSE_SPLIT "UNUSE_SPLIT"
#define ERROR_VALUE ( -999 )

class DBGeneralSet
{
public:
    DBGeneralSet() ;
    virtual ~DBGeneralSet() ;
    static INT GetValue( const CHAR* szKeyName ) ;
} ;

