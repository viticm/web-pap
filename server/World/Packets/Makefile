# @desc makefile for World
# @author viticm<viticm.ti@gmail.com>
# @date 2013-06-25 20:00:12
include ../../premake.mk

CFLAGS  = -I$(BASEDIR)/World/Main -I$(BASEDIR)/World/Packets -I$(BASEDIR)/World/WorldData -I$(BASEDIR)/World $(SERVER_BASE_INCLUDES) -I$(BASEDIR)/Server/SMU
LDFLAGS =
DIRS =  
OBJS =  GWAskChangeSceneHandler.o \
		LWAskDeleteCharHandler.o \
		GWCityAskInitInfoHandler.o \
		GWCommandHandler.o \
		LWAskCharLoginHandler.o \
		GWAskSceneDataHandler.o \
		GWMailHandler.o \
		GSAskDataHandler.o \
		GWEnterTeamFollowHandler.o \
		GWAskUserDataHandler.o \
		GWCityCloseHandler.o \
		GWTeamDismissHandler.o \
		GWTeamRetInviteHandler.o \
		GWAskMailHandler.o \
		GWTeamApplyHandler.o \
		GWTeamInviteHandler.o \
		GWLevelUpHandler.o \
		GWHeartBeatHandler.o \
		GWChannelDismissHandler.o \
		GWSystemMsgHandler.o \
		GWChatHandler.o \
		SGRetDataHandler.o \
		GWTeamAppointHandler.o \
		SSScenePlayerCountHandler.o \
		GWTeamMemberEnterSceneHandler.o \
		GWStopTeamFollowHandler.o \
		WLHandler.o \
		SSConnectHandler.o \
		GWFingerHandler.o \
		GWGuildHandler.o \
		GWChannelCreateHandler.o \
		GWTeamRetApplyHandler.o \
		GGSceneNotifyHandler.o \
		GWTeamKickHandler.o \
		GWUpdateTitleHandler.o \
		GWAskTeamInfoHandler.o \
		GWChannelKickHandler.o \
		GWCityCloseSuccessHandler.o \
		GWAskTeamMemberInfoHandler.o \
		GWTeamLeaderRetInviteHandler.o \
		GWCallOfHumanHandler.o \
		GWCityOptHandler.o \
		GWTeamLeaveHandler.o \
		GWCityApplyNewCityHandler.o \
		GWChannelInviteHandler.o \
		GWNotifyUserHandler.o \
		GWBatchMailHandler.o \
		GWChangeMenpaiHandler.o \
		GWRelationHandler.o \
		WGHandler.o

debug:$(OBJS)
	for dir in $(DIRS); do \
		$(MAKE) debug -C $$dir; \
	done

release:$(OBJS)
	for dir in $(DIRS); do \
		$(MAKE) release -C $$dir; \
	done

all:debug

clean:
	$(RM) -f *.o
