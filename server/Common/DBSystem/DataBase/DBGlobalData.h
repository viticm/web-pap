#pragma once

#include "Type.h"
#include "ODBCBase.h"

class DBGlobalData : public ODBCBase
{
    ID_t            m_iPoolID ;
public:
    DBGlobalData( ODBCInterface* pInterface ) ;
    virtual BOOL    Load() ;
    virtual BOOL    Save( VOID* pSource ) ;
    virtual BOOL    Delete() ;
    virtual BOOL    ParseResult( VOID* pResult ) ;

public:
    VOID            SetPoolID( ID_t iPoolID ) ;
    ID_t            GetPoolID() ;
} ;

