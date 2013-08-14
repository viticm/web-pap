#include "stdafx.h"
#include "LBAskAuth.h"
#include "BLRetAuth.h"
#include "ServerPlayer.h"
#include "UserDBManager.h"
#include "BWValidateUser.h"
#include "Log.h"

UINT LBAskAuthHandler::Execute( LBAskAuth* pPacket, Player* pPlayer )
{
    __ENTER_FUNCTION
        
        Assert( pPlayer ) ;
        Assert( pPacket ) ;

        BLRetAuth Msg ;
        Msg.SetAccount( pPacket->GetAccount() ) ;
        Msg.SetPlayerID( pPacket->GetPlayerID() ) ;
        if ( g_pUserDBManager->IsRealUser( pPacket->GetAccount(), pPacket->GetPassWord() ) )
        {
            Msg.SetResult( LOGINR_SUCCESS ) ;
        }
        else
        {
            Msg.SetResult( LOGINR_AUTH_FAIL ) ;
        }
        
        Msg.SetAge( 20 ) ;
        ( ( ServerPlayer* )pPlayer )->SendPacket( &Msg ) ;
        return PACKET_EXE_CONTINUE;

    __LEAVE_FUNCTION

        return PACKET_EXE_ERROR;
}
