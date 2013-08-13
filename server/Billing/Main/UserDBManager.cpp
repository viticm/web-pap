#include "stdafx.h"
#include "UserDBManager.h"
#include "md5.h"

UserDBManager* g_pUserDBManager = NULL ;

UserDBManager::UserDBManager( VOID )
{
    __ENTER_FUNCTION
    __LEAVE_FUNCTION
}

BOOL UserDBManager::Init()
{
    __ENTER_FUNCTION

        m_pDBManager = new DBManager ;
        if( m_pDBManager->Init() )
        {    
            sprintf( m_strSql, "USE userdb" );
            strcpy( ( CHAR* )m_pDBManager->GetInterface( USER_DATABASE )->m_Query.m_SqlStr, m_strSql ) ;
            m_pDBManager->GetInterface( USER_DATABASE )->Clear() ;
            if( m_pDBManager->GetInterface( USER_DATABASE )->Execute() )
            {
                return TRUE;
            }
        }
        else
        {
            return FALSE;
        }

    __LEAVE_FUNCTION
        return FALSE;
}

UserDBManager::~UserDBManager( VOID )
{
    __ENTER_FUNCTION

        delete m_pDBManager;

    __LEAVE_FUNCTION
}

BOOL UserDBManager::AddUser( CHAR* szUserName, 
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
                             CHAR* szPassWord2 ) 
{
    __ENTER_FUNCTION

        CHAR szEncryptPassWord[ 36 ]    = { 0 } ;
        CHAR szEncryptPassWord2[ 36 ]   = { 0 } ;
        MD5Encrypt( szPassWord, szEncryptPassWord );
        MD5Encrypt( szPassWord2, szEncryptPassWord2 );

        sprintf( m_strSql, "call adduser( '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', %d, '%s', '%s', '%s' )",
            szUserName, szEncryptPassWord, szPrompt, szAnswer, szTrueName, szIdNumber, szEmail, szMobileNumber, szProvince, szCity, szPhoneNumber,
            szAddress, szPostalCode, iGender, szBirthday, szQQ, szEncryptPassWord2 ) ;
        strcpy( ( CHAR* )m_pDBManager->GetInterface( USER_DATABASE )->m_Query.m_SqlStr, m_strSql ) ;
        m_pDBManager->GetInterface( USER_DATABASE )->Clear();

        if( m_pDBManager->GetInterface( USER_DATABASE )->Execute() )
        {
            if( m_pDBManager->GetInterface( USER_DATABASE )->mAffectCount > 0 )
                return TRUE ;
        }
        else
        {
            return FALSE ;
        }

    __LEAVE_FUNCTION

        return FALSE ;
}


BOOL UserDBManager::AmendPassWord( CHAR* szUserName, CHAR* szNewPassWord )
{
    __ENTER_FUNCTION

        CHAR szEncryptNewPassWord[ 36 ]    = { 0 } ;
        MD5Encrypt( szNewPassWord, szEncryptNewPassWord ) ; 
        sprintf( m_strSql, "call changePasswd( '%s', '%s' )", szUserName, szEncryptNewPassWord ) ;
        strcpy( ( CHAR* )m_pDBManager->GetInterface( USER_DATABASE )->m_Query.m_SqlStr, m_strSql ) ;
        m_pDBManager->GetInterface( USER_DATABASE )->Clear() ;
        if( m_pDBManager->GetInterface( USER_DATABASE )->Execute() )
        {
            // PROCEDURE UPDATE MAYBE RETURN ZERO
            if( m_pDBManager->GetInterface( USER_DATABASE )->mAffectCount >= 0 )
                return TRUE ;
        }
        else
        {
            return FALSE ;
        }

    __LEAVE_FUNCTION

        return FALSE ;
}


BOOL UserDBManager::DeleteUser( CHAR* szUserName )
{
    __ENTER_FUNCTION

        sprintf( m_strSql, "DELETE FROM `users` WHERE `name` = '%s' ", szUserName) ;
        strcpy( ( CHAR* )m_pDBManager->GetInterface( USER_DATABASE )->m_Query.m_SqlStr, m_strSql) ;
        m_pDBManager->GetInterface( USER_DATABASE )->Clear() ;
        if( m_pDBManager->GetInterface( USER_DATABASE )->Execute() )
        {
            if( m_pDBManager->GetInterface( USER_DATABASE )->mAffectCount > 0)
                return TRUE ;
        }
        else
        {
            return FALSE ;
        }

    __LEAVE_FUNCTION

        return FALSE ;
}

INT  UserDBManager::GetUserSum( VOID )
{
    __ENTER_FUNCTION

        sprintf( m_strSql, "EXECUTE WorldWX_User_GetSum" ) ;
        strcpy( ( CHAR* )m_pDBManager->GetInterface( USER_DATABASE )->m_Query.m_SqlStr, m_strSql ) ;
        m_pDBManager->GetInterface( USER_DATABASE )->Clear() ;
        if( m_pDBManager->GetInterface( USER_DATABASE )->Execute() )
        {
            m_pDBManager->GetInterface( USER_DATABASE )->Fetch() ;
            if( m_pDBManager->GetInterface( USER_DATABASE )->Col[0][0] != 0 )
            {
                return atoi( m_pDBManager->GetInterface( USER_DATABASE )->Col[0] ) ;
            }
        }
        else
        {
            return FALSE;
        }

    __LEAVE_FUNCTION

        return FALSE;
}

BOOL UserDBManager::IsHaveUser( CHAR* szUserName )
{
    __ENTER_FUNCTION

        sprintf( m_strSql, "call isHaveUser( '%s' )", szUserName ) ;
        strcpy( ( CHAR* )m_pDBManager->GetInterface( USER_DATABASE )->m_Query.m_SqlStr, m_strSql ) ;
        m_pDBManager->GetInterface( USER_DATABASE )->Clear() ;
        if( m_pDBManager->GetInterface( USER_DATABASE )->Execute() )
        {
            m_pDBManager->GetInterface( USER_DATABASE )->Fetch() ;
            if( 0 != m_pDBManager->GetInterface(USER_DATABASE)->Col[0][0] )
            {
                return atoi( m_pDBManager->GetInterface( USER_DATABASE )->Col[0] ) ;
            }
        }
        else
        {
            return FALSE ;
        }

    __LEAVE_FUNCTION

        return FALSE ;
}

BOOL UserDBManager::IsRealUser( const CHAR* szUserName, const CHAR* szPassWord )
{
    __ENTER_FUNCTION

        CHAR szEncryptPassWord[ 36 ] = { 0 } ;
        MD5Encrypt( ( CHAR* )szPassWord, szEncryptPassWord ) ;
        sprintf( m_strSql, "SELECT `ID` FROM `users` WHERE `name` = '%s' AND `passwd` = '%s' ", szUserName, szEncryptPassWord ) ;
        strcpy( ( CHAR* )m_pDBManager->GetInterface( USER_DATABASE )->m_Query.m_SqlStr, m_strSql ) ;
        m_pDBManager->GetInterface( USER_DATABASE )->Clear() ;

        if( m_pDBManager->GetInterface( USER_DATABASE )->Execute())
        {
            m_pDBManager->GetInterface( USER_DATABASE )->Fetch() ;
            if( 0 != m_pDBManager->GetInterface( USER_DATABASE )->Col[ 0 ][ 0 ] )
            {
                return atoi( m_pDBManager->GetInterface( USER_DATABASE )->Col[ 0 ] ) ;
            }
        }
        else
        {
            return FALSE ;
        }

    __LEAVE_FUNCTION

        return FALSE ;
}

VOID UserDBManager::MD5Encrypt( CHAR* szInEncryptStr, CHAR* szOutEncryptStr )
{
    const CHAR* szPreEncryptStr = "0x" ;
    MD5 MD5( szInEncryptStr ) ;
    sprintf( szOutEncryptStr, "%s%s", szPreEncryptStr, ( MD5.md5() ).c_str() ) ;
}
