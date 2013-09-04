#include "stdafx.h"

#include "LoginPlayer.h"
#include "PacketFactoryManager.h"
#include "PlayerPool.h"
#include "TimeManager.h"
#include "Log.h"
#include "Config.h"
#include "TurnPlayerQueue.h"
#include "LCStatus.h"


LoginPlayer::LoginPlayer()
{
    __ENTER_FUNCTION

        m_Status                = PS_LOGIN_EMPTY ;
        m_KickTime              = 0 ;
        m_LastSendTime          = 0 ;
        m_ConnectTime           = 0 ;
        m_KickTime              = 0 ;
        m_CurrentTime           = 0 ;
        m_LeftTimeToQuit        = 0 ;
        m_AccountGuid           = 0 ;    
        m_Version               = 0 ;
        m_LastSendProcessTurn   = 0 ;
        m_QueuePos              = 0 ;
        m_LastDBOpTime          = 0 ;

        m_CharNumber            = -1 ;
        memset( m_GUIDList, -1, sizeof( GUID_t ) * DB_CHAR_NUMBER ) ;
        m_uKey                  = -1 ;
        m_bDBOprating           = FALSE ;
        m_ReadyKickCount        = 0 ;
        m_WrongPWCount          = 0 ;
        m_SceneID               = 0 ;
        m_WorldPos.CleanUp() ;
        m_Camp                  = -1 ;

    __LEAVE_FUNCTION
}

LoginPlayer::~LoginPlayer()
{
    __ENTER_FUNCTION
    __LEAVE_FUNCTION
}

VOID LoginPlayer::CleanUp()
{
    __ENTER_FUNCTION

        m_Status                = PS_LOGIN_EMPTY ;
        m_KickTime              = 0 ;
        m_LastSendTime          = 0 ;
        m_ConnectTime           = 0 ;
        m_CurrentTime           = 0 ;
        m_LeftTimeToQuit        = 0 ;
        m_AccountGuid           = 0 ;
        m_Version               = 0 ;
        m_LastSendProcessTurn   = 0 ;
        m_QueuePos              = 0 ;
        m_LastDBOpTime          = 0 ;
        m_CharNumber            = -1 ;
        memset( m_GUIDList, -1, sizeof( GUID_t ) * DB_CHAR_NUMBER ) ;
        m_uKey                  = -1 ;
        m_bDBOprating           = FALSE ;
        m_ReadyKickCount        = 0 ;
        m_WrongPWCount          = 0 ;
        m_SceneID               = 0 ;
        m_WorldPos.CleanUp() ;
        m_Camp                  = -1 ;
        ResetKick() ;
        return Player::CleanUp() ;

    __LEAVE_FUNCTION
}

BOOL LoginPlayer::ProcessCommand( BOOL Option )
{
    __ENTER_FUNCTION

        return Player::ProcessCommand( Option ) ;

    __LEAVE_FUNCTION

        return FALSE ;
}

BOOL LoginPlayer::ProcessInput()
{
    __ENTER_FUNCTION

        return Player::ProcessInput() ;

    __LEAVE_FUNCTION

        return FALSE ;
}

BOOL LoginPlayer::ProcessOutput()
{
    __ENTER_FUNCTION

        return Player::ProcessOutput() ;

    __LEAVE_FUNCTION

        return FALSE ;
}

BOOL LoginPlayer::SendPacket( Packet* pPacket )
{
    __ENTER_FUNCTION

        return Player::SendPacket( pPacket ) ;

    __LEAVE_FUNCTION

        return FALSE ;
}

BOOL LoginPlayer::HeartBeat( UINT uTime )
{
    __ENTER_FUNCTION

        if ( IsDisconnect() )
        {
            m_LeftTimeToQuit -= ( uTime - m_CurrentTime ) ;
            if ( 0 > m_LeftTimeToQuit )
            {//真正执行退出处理
                return FALSE ;
            }
        }

        m_CurrentTime = uTime ;

        // 如果Player在一定时间内没有收到任何消息，则断开客户端连接
        // 在Player处理消息前会执行ResetKick函数修正m_KickTime信息
        if ( uTime > m_KickTime + MAX_KICK_TIME && PS_LOGIN_PROCESS_TURN != GetPlayerStatus() )
        {
            Log::SaveLog( LOGIN_LOGFILE, "ERROR: Player::HeartBeat Didn't recv message for too long time. Kicked!" ) ;
            return FALSE ;
        }
        
        if ( PS_LOGIN_PROCESS_TURN == GetPlayerStatus() )  // 排队状态的玩家，每格MAX_TRUN_MESSAGE_TIME
                                                           // 时间向客户端发送排队消息
        {
            if ( uTime > m_LastSendProcessTurn + MAX_TRUN_MESSAGE_TIME )
            {
                m_LastSendProcessTurn = uTime ;   
                LCStatus Msg ;
                Msg.SetClientStatus( CTS_TURN ) ;

                UINT Head = g_pProcessPlayerQueue->GetHead() ;
                if ( Head <= m_QueuePos )
                {
                    Msg.SetTurnNumber( ( m_QueuePos - Head ) + 1 ) ;
                }
                else
                {
                    Msg.SetTurnNumber( MAX_TURN_PLAYER - ( Head - m_QueuePos ) ) ;
                }
                
                SendPacket( &Msg ) ;
            }

        }

        return Player::HeartBeat( uTime ) ;

    __LEAVE_FUNCTION

        return FALSE ;
}

BOOL LoginPlayer::FreeOwn()
{
    __ENTER_FUNCTION

        CleanUp() ;

        g_pPlayerPool->DelPlayer( PlayerID() ) ;

        return TRUE ;

    __LEAVE_FUNCTION

        return FALSE ;
}

VOID LoginPlayer::Init()
{
    __ENTER_FUNCTION

        SetDisconnect( FALSE ) ;
        ResetKick() ;//开始踢出计时

    __LEAVE_FUNCTION
}

VOID LoginPlayer::Disconnect()
{
    __ENTER_FUNCTION

        _MY_TRY
        {
            m_LeftTimeToQuit = g_Config.m_ConfigInfo.m_DisconnectTime ;
            SetDisconnect( TRUE ) ;
        }
        _MY_CATCH
        {
        }

        Player::Disconnect() ;

    __LEAVE_FUNCTION
}

VOID LoginPlayer::ResetKick()
{
    __ENTER_FUNCTION

        m_KickTime = g_pTimeManager->CurrentSavedTime() ;

        Player::ResetKick() ;

    __LEAVE_FUNCTION
}

const CHAR* LoginPlayer::GetAccount()
{
    return szAccount ;
}

VOID  LoginPlayer::SetAccount( const CHAR* pAccount )
{
    __ENTER_FUNCTION
    
        strncpy( szAccount, pAccount, MAX_ACCOUNT ) ;
        szAccount[ MAX_ACCOUNT ] = '\0' ;

    __LEAVE_FUNCTION
}

UINT LoginPlayer::GetVersion()
{
    return m_Version ;
}

VOID LoginPlayer::SetVersion( UINT uVersion )
{
    __ENTER_FUNCTION

        m_Version = uVersion ;

    __LEAVE_FUNCTION
}

UINT LoginPlayer::GetQueuePos()
{
        return m_QueuePos ;
}

VOID LoginPlayer::SetQueuePos( UINT QueuePos )
{
    __ENTER_FUNCTION

        m_QueuePos = QueuePos ;

    __LEAVE_FUNCTION
}

VOID LoginPlayer::SetCharNumber( INT CharNumber )
{
    __ENTER_FUNCTION

        m_CharNumber = CharNumber ;

    __LEAVE_FUNCTION
}

INT LoginPlayer::GetCharNumber()
{
    return m_CharNumber ;
}

VOID LoginPlayer::SetCharGUID( GUID_t guid, UINT uIndex )
{
    __ENTER_FUNCTION

        Assert( DB_CHAR_NUMBER > uIndex ) ;
        m_GUIDList[ uIndex ] = guid ;

    __LEAVE_FUNCTION
}

BOOL LoginPlayer::IsGUIDOwner( GUID_t guid )
{
    __ENTER_FUNCTION

        for ( INT i = 0; ( i < m_CharNumber ) && ( DB_CHAR_NUMBER > i ); i++ )
        {
            if ( ( m_GUIDList[i] == guid ) && ( INVALID_ID != guid ) )
            {
                return TRUE ;
            }
        }
        return FALSE ;

    __LEAVE_FUNCTION

        return FALSE ;
}

VOID LoginPlayer::SetUserKey( UINT key )
{
    __ENTER_FUNCTION

        m_uKey = key ;

    __LEAVE_FUNCTION
}

UINT LoginPlayer::GetUserKey()
{
    return m_uKey ;
}

VOID LoginPlayer::SetDBOperating( BOOL bOp )
{
    __ENTER_FUNCTION

        m_bDBOprating = bOp ;

    __LEAVE_FUNCTION
}

BOOL LoginPlayer::GetDBOperating()
{
    return m_bDBOprating ;
}

VOID LoginPlayer::SetReadyKickCount( INT KickCount )
{
    __ENTER_FUNCTION

        m_ReadyKickCount = KickCount ;

    __LEAVE_FUNCTION
}

INT LoginPlayer::GetReadyKickCount()
{
    return m_ReadyKickCount ;
}

UINT LoginPlayer::GetLastSendTurnTime()
{
    return m_LastSendProcessTurn ;
}

VOID LoginPlayer::SetLastSendTurnTime(UINT uTime)
{
    __ENTER_FUNCTION

        m_LastSendProcessTurn = uTime ;

    __LEAVE_FUNCTION
}

VOID LoginPlayer::SetWrongPWCount(INT Count)
{
    __ENTER_FUNCTION

        m_WrongPWCount = Count ;

    __LEAVE_FUNCTION
}

INT LoginPlayer::GetWrongPWCount()
{
    return m_WrongPWCount ;
}

SceneID_t LoginPlayer::GetChooseSceneID() const
{
    return m_SceneID ;
}

VOID LoginPlayer::SetChooseSceneID( SceneID_t sid )
{
    __ENTER_FUNCTION

        m_SceneID = sid ;

    __LEAVE_FUNCTION
}

WORLD_POS LoginPlayer::GetWorldPos() const
{
    return m_WorldPos ;
}

VOID LoginPlayer::SetWorldPos( WORLD_POS& pos )
{
    __ENTER_FUNCTION

        m_WorldPos = pos ;

    __LEAVE_FUNCTION
}

CampID_t LoginPlayer::GetPlayerCamp()
{
    return m_Camp ;
}

VOID LoginPlayer::SetPlayerCamp( CampID_t id )
{
    __ENTER_FUNCTION

        m_Camp = id ;

    __LEAVE_FUNCTION
}

BYTE LoginPlayer::GetPlayerAge()
{
    return m_Age ;
}

VOID LoginPlayer::SetPlayerAge( BYTE age )
{
    __ENTER_FUNCTION
    
        m_Age = age ;

    __LEAVE_FUNCTION
}
