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



BOOL UserDBManager::IsHaveUser( CHAR* UserName )
{
    __ENTER_FUNCTION

        sprintf( m_strSql, "EXECUTE WorldWX_User_IsHave @UserName = '%s'", UserName ) ;
        strcpy( ( CHAR* )m_pDBManager->GetInterface( USER_DATABASE )->m_Query.m_SqlStr, m_strSql) ;
        m_pDBManager->GetInterface( USER_DATABASE )->Clear() ;
        if( m_pDBManager->GetInterface( USER_DATABASE )->Execute() )
        {
            m_pDBManager->GetInterface( USER_DATABASE )->Fetch() ;
            if( m_pDBManager->GetInterface(USER_DATABASE)->Col[0][0] != 0 )
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

BOOL UserDBManager::IsRealUser( const CHAR* UserName, const CHAR* PassWord )
{
    __ENTER_FUNCTION

        sprintf( m_strSql, "EXECUTE WorldWX_User_IsReal @UserName = '%s', @PassWord = '%s'", UserName, PassWord ) ;
        strcpy( ( CHAR* )m_pDBManager->GetInterface( USER_DATABASE )->m_Query.m_SqlStr, m_strSql ) ;
        m_pDBManager->GetInterface( USER_DATABASE )->Clear() ;
        if( m_pDBManager->GetInterface( USER_DATABASE )->Execute())
        {
            m_pDBManager->GetInterface( USER_DATABASE )->Fetch() ;
            if( m_pDBManager->GetInterface( USER_DATABASE )->Col[ 0 ][ 0 ] != 0 )
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

BOOL UserDBManager::WX_Shop_Add( INT ShopId, 
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
                                 CHAR* CreateTime)
{
    __ENTER_FUNCTION

        sprintf( m_strSql, " EXECUTE WX_Shop_Add "
        " @Id = %d, "
        " @UserId = %d, "
        " @Money  = %d, "
        " @Item_1  = %d, "
        " @ItemCount_1 = %d, "
        " @Item_2 = %d, "
        " @ItemCount_2 = %d, "
        " @Item_3 = %d, "
        " @ItemCount_3 = %d, "
        " @Item_4 = %d, "
        " @ItemCount_4 = %d, "
        " @Item_5 = %d, "
        " @ItemCount_5 = %d, "
        " @IsSucceed = %d, "
        " @CreateTime = '%s'",
        ShopId, 
        UserId, 
        Money, 
        Item_1,
        ItemCount_1,
        Item_2,
        ItemCount_2,
        Item_3,
        ItemCount_3,
        Item_4,
        ItemCount_4,
        Item_5,
        ItemCount_5,
        IsSucceed,
        CreateTime ) ;

        strcpy( ( CHAR* )m_pDBManager->GetInterface( USER_DATABASE )->m_Query.m_SqlStr, m_strSql ) ;
        m_pDBManager->GetInterface( USER_DATABASE )->Clear() ;
        if( m_pDBManager->GetInterface( USER_DATABASE )->Execute() )
        {
            INT aaa = m_pDBManager->GetInterface( USER_DATABASE )->mAffectCount ;

            if( aaa > 0 )
            {
                return TRUE ;
            }
        }
        else
        {
            return FALSE ;
        }

    __LEAVE_FUNCTION

        return FALSE ;
}

BOOL UserDBManager::WorldWX_Shop_IsHave( UINT ShopID )
{
    __ENTER_FUNCTION

        sprintf( m_strSql, "EXECUTE WorldWX_Shop_IsHave @Shop_Id = %d", ShopID );
        strcpy( ( CHAR* )m_pDBManager->GetInterface( USER_DATABASE )->m_Query.m_SqlStr, m_strSql ) ;
        m_pDBManager->GetInterface( USER_DATABASE )->Clear() ;
        if( m_pDBManager->GetInterface( USER_DATABASE )->Execute() )
        {
            m_pDBManager->GetInterface( USER_DATABASE )->Fetch() ;
            if( m_pDBManager->GetInterface(USER_DATABASE)->Col[ 0 ][ 0 ] != 0 )
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
