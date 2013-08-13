/**
 * PAP Server Engine ( https://github.com/viticm/web-pap )
 * $Id UserDBManager.cpp
 * @link https://github.com/viticm/web-pap/tree/master/server for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-8-9 14:44:29
 * @uses the user db managers
 */
#pragma once
#include "DBManager.h"
#include "ODBCInterface.h"
 
class UserDBManager
{
public:
#define        MAX_SQL_LENGTH                4096
    UserDBManager( VOID ) ;
    virtual ~UserDBManager( VOID ) ;
    BOOL Init();
    BOOL AddUser( CHAR* szUserName, 
                  CHAR* szPassWord,
                  CHAR* szPrompt,
                  CHAR* szAnswer,
                  CHAR* szTrueName, 
                  CHAR* szIdNumber,
                  CHAR* szEmail,
                  CHAR* szMobileNumber,
                  CHAR* szProvince, 
                  CHAR* szCity, 
                  CHAR* szPhoneNumber, 
                  CHAR* szAddress, 
                  CHAR* szPostalCode, 
                  INT   iGender, 
                  CHAR* szBirthday,
                  CHAR* szQQ,
                  CHAR* szPassWord2 ) ;
    BOOL AmendPassWord( CHAR* UserName, CHAR* PassWord, CHAR* NewPassWord ) ;
    BOOL DeleteUser( CHAR* UserName ) ;
    INT  GetUserSum( VOID ) ;
    BOOL IsHaveUser( CHAR* UserName ) ;
    BOOL IsRealUser( const CHAR* UserName, const CHAR* PassWord ) ;
    BOOL WX_Shop_Add( INT ShopId, 
                      INT UserId, 
                      INT Money, 
                      INT Item_1,
                      INT ItemCount_1,
                      INT Item_2,
                      INT ItemCount_2,
                      INT Item_3,
                      INT ItemCount_3,
                      INT Item_4,
                      INT ItemCount_4,
                      INT Item_5,
                      INT ItemCount_5,
                      INT IsSucceed,
                      CHAR* CreateTime ) ;
    BOOL WorldWX_Shop_IsHave( UINT ShopID ) ;
    DBManager *m_pDBManager ;
    VOID MD5Encrypt( CHAR* szInEncryptStr, CHAR* szOutEncryptStr ) ;
    CHAR m_strSql[ MAX_SQL_LENGTH ] ;
};

extern UserDBManager* g_pUserDBManager ;
