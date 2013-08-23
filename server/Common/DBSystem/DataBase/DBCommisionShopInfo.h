/**
 * PAP Server Engine ( https://github.com/viticm/web-pap )
 * $Id SMULogicManager.h
 * @link https://github.com/viticm/web-pap/tree/master/server for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-8-22 14:44:42
 * @uses the global data manager of database 
 */
#pragma once

#include "Type.h"
#include "ODBCBase.h"

class DBCommisionShopInfo : public ODBCBase
{
    ID_t            m_iWorldId ;
    ID_t            m_iServerId ;
public:
    DBCommisionShopInfo( ODBCInterface* pInterface ) ;
    virtual BOOL    Load() ;
    virtual BOOL    Save( VOID* pSource ) ;
    virtual BOOL    Delete() ;
    virtual BOOL    ParseResult( VOID* pResult ) ;

public:
    VOID            SetServerId( ID_t iPoolId ) ;
    ID_t            GetServerId() ;
    VOID            SetWorldId( ID_t iWorldId ) ;
    ID_t            GetWorldId() ;
} ;

