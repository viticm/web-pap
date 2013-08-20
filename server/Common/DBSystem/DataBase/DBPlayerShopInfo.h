#ifndef _DB_GUILDINFO_H_
#define _DB_GUILDINFO_H_

#include "Type.h"
#include "ODBCBase.h"

class DBPlayerShopInfo:public ODBCBase
{
    
public:
    DBPlayerShopInfo(ODBCInterface* pInterface);
    virtual BOOL    Load();
    virtual BOOL    Save(VOID* pSource);
    virtual BOOL    Delete();
    virtual BOOL    ParseResult(VOID* pResult);

public:
    
};


#endif