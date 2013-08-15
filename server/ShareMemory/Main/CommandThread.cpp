#include "stdafx.h"
#include "CommandThread.h"
#include "SMULogicManager.h"
#include "Log.h"

CommandThread g_CommandThread ;

VOID CommandThread::run()
{ 
    __ENTER_FUNCTION

        while( IsActive() )
        {
            BOOL ret = FALSE ;
            ret = CmdParser::HandleInput() ;
            Assert( ret ) ;
        }

    __LEAVE_FUNCTION
}

#define SM_CMD_SIZE 255

BOOL     CmdParser::HandleInput()
{
    __ENTER_FUNCTION
    
        CHAR InBuffer[ SM_CMD_SIZE ] ;
        memset( InBuffer, 0, SM_CMD_SIZE ) ;
    
        INT CharCount = 0 ;
        INT CharIdentiy ;    
    
        while( TRUE )
        {
            CharIdentiy = getchar() ;

            if( '\n' == CharIdentiy )
            {
                break ;
            }
            if( SM_CMD_SIZE - 1 <= CharCount )
                break ;

            InBuffer[ CharCount ] = CharIdentiy ;
            CharCount++ ;
        }
    
    
        SM_COMMANDS_STATE cmdState = ParserCommandType( InBuffer ) ;
    
        switch( cmdState.cmdType ) 
        {
            case CMD_SAVE_ALL:
            {
                g_CommandThread.m_SMConfig.Commands = cmdState ;
                Log::SaveLog( "ShareMemory","Start SaveAll!%s", LF ) ;
            }
            break ;
            case CMD_CLEAR_ALL:
            {
                g_CommandThread.m_SMConfig.Commands = cmdState ;
                Log::SaveLog( "ShareMemory","Start ClearAll!%s", LF ) ;
            }
            break ;

            default:
            {
                Log::SaveLog( "ShareMemory","Unknow Commands!%s", LF ) ;
            
            }
        }
    
        return TRUE ;

    __LEAVE_FUNCTION

        return FALSE ;
}

SM_COMMANDS_STATE    CmdParser::ParserCommandType( CHAR* pBuff )
{
    __ENTER_FUNCTION
        
        CHAR szCmd[ SM_CMD_SIZE ] ;
        memset( szCmd, 0, SM_CMD_SIZE ) ;
        
        INT i ;
        for( i =0; SM_CMD_SIZE > i; i++ )
        {
            if( ' ' == pBuff[ i ] || 0 == pBuff[ i ] || '\t' == pBuff[ i ] )
                break ;
            szCmd[ i ] = pBuff[ i ] ;
        }

        SM_COMMANDS_STATE CMDState ;
        if( 0 == strcmp( szCmd, "saveall" ) )
        {
            CMDState.cmdType =  CMD_SAVE_ALL ;
        }
        else if( 0 == strcmp(szCmd,"clearall") )
        {
            CMDState.cmdType =  CMD_CLEAR_ALL ;
        }
        else
        {
            CMDState.cmdType = CMD_UNKNOW ;
        }
        
        return CMDState ;

    __LEAVE_FUNCTION
}
