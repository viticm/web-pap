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
    BOOL AmendPassWord( CHAR* szUserName, CHAR* szNewPassWord ) ;
    BOOL DeleteUser( CHAR* UserName ) ;
    INT  GetUserSum( VOID ) ;
    BOOL IsHaveUser( CHAR* UserName ) ;
    BOOL IsRealUser( const CHAR* szUserName, const CHAR* szPassWord ) ;
    DBManager *m_pDBManager ;
    VOID MD5Encrypt( CHAR* szInEncryptStr, CHAR* szOutEncryptStr ) ;
    CHAR m_strSql[ MAX_SQL_LENGTH ] ;
};

extern UserDBManager* g_pUserDBManager ;
