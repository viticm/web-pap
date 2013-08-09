#include "stdafx.h"
#include "UserDBManager.h"

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

BOOL UserDBManager::AddUser( INT UserId, 
                             CHAR* UserName, 
                             CHAR* PassWord, 
                             INT Authority, 
                             INT Type, 
                             CHAR *Sign, 
                             INT CardType, 
                             CHAR *CardId, 
                             INT PhoneType, 
                             CHAR *Phone )
{
    __ENTER_FUNCTION

        sprintf( m_strSql, "EXECUTE WorldWX_User_Add @UserId = %d, @UserName = '%s', @PassWord = '%s', @Authority = %d, @Type = %d, @Sign = %s, @CardType = %d, @CardId = %s, @PhoneType = %d, @Phone = %s",
            UserId, UserName, PassWord, Authority, Type, Sign, CardType, CardId, PhoneType, Phone) ;
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


BOOL UserDBManager::AmendPassWord( CHAR* UserName, CHAR* PassWord, CHAR* NewPassWord )
{
    __ENTER_FUNCTION

        sprintf( m_strSql, "EXECUTE WorldWX_User_AmendPassWord @UserName = '%s', @PassWord = '%s', @NewPassWord = '%s'", 
        UserName, PassWord, NewPassWord );
        strcpy( ( CHAR* )m_pDBManager->GetInterface( USER_DATABASE )->m_Query.m_SqlStr, m_strSql);

        m_pDBManager->GetInterface( USER_DATABASE )->Clear();
        if( m_pDBManager->GetInterface( USER_DATABASE )->Execute() )
        {
            if( m_pDBManager->GetInterface( USER_DATABASE )->mAffectCount > 0 )
                return TRUE;
        }
        else
        {
            return FALSE;
        }

    __LEAVE_FUNCTION

        return FALSE;
}


BOOL UserDBManager::DeleteUser( CHAR* UserName )
{
    __ENTER_FUNCTION

        sprintf( m_strSql, "EXECUTE WorldWX_User_Delete @UserName = '%s' ", UserName) ;
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
