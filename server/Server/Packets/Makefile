# @desc makefile for Server
# @author viticm<viticm.ti@gmail.com>
# @date 2013-07-10 19:09:17
include ../../premake.mk

CFLAGS  = -I$(BASEDIR)/Server/EventModule -I$(BASEDIR)/Server/Item -I$(BASEDIR)/Server/Script -I$(BASEDIR)/Server/Main -I$(BASEDIR)/Server/Obj -I$(BASEDIR)/Server/Team -I$(BASEDIR)/Server/DB -I$(BASEDIR)/Server/MenPai -I$(BASEDIR)/Server/Packets -I$(BASEDIR)/Server/AI -I$(BASEDIR)/Server/Player -I$(BASEDIR)/Server/ActionModule -I$(BASEDIR)/Server/Skills -I$(BASEDIR)/Server/Skills/SpecialObjLogic -I$(BASEDIR)/Server/Skills/SkillLogic -I$(BASEDIR)/Server/Skills/SkillLogic/Item -I$(BASEDIR)/Server/Skills/SkillLogic/Common -I$(BASEDIR)/Server/Skills/SkillLogic/Human -I$(BASEDIR)/Server/Skills/SkillLogic/Pet -I$(BASEDIR)/Server/Skills/ImpactLogic -I$(BASEDIR)/Server/Mission -I$(BASEDIR)/Server/Ability -I$(BASEDIR)/Server/Other -I$(BASEDIR)/Server/Scene -I$(BASEDIR)/Server/Scene/Scan -I$(BASEDIR)/Server/SMU -I$(BASEDIR)/Server/Base -I$(BASEDIR)/Server
LDFLAGS =
DIRS =  
OBJS =  CGTeamApplyHandler.o \
		GCCityErrorHandler.o \
		WGWorldTimeHandler.o \
		CGPlayerShopSaleOutHandler.o \
		CGShopRepairHandler.o \
		CGPlayerShopFavoriteHandler.o \
		CGAskItemInfoHandler.o \
		CGAskStudyXinfaHandler.o \
		CGBankSwapItemHandler.o \
		GWCityAskInitInfoHandler.o \
		CGTeamRetApplyHandler.o \
		CGAskDetailEquipListHandler.o \
		CGCharMoveHandler.o \
		WGRelationHandler.o \
		CGCharAskBaseAttribHandler.o \
		CGTeamKickHandler.o \
		WGNotifyMailHandler.o \
		CGCharDefaultEventHander.o \
		CGAskMissionListHandler.o \
		CGPlayerShopNameHandler.o \
		CGAskLeanAbilityHandler.o \
		CGPlayerShopTypeHandler.o \
		CGTeamRetInviteHandler.o \
		CGTeamLeaveHandler.o \
		CGCharUseSkillHandler.o \
		CGUseEquipSkillHandler.o \
		CGDoEventHandler.o \
		CGPackUpPacketHandler.o \
		CGEnvRequestHandler.o \
		CGChannelCreateHandler.o \
		CGAskTeamMemberInfoHandler.o \
		CGBankRemoveItemHandler.o \
		CGBankAddItemHandler.o \
		CGFingerHandler.o \
		CGMyEquipHandler.o \
		WGChannelErrorHandler.o \
		WGCityAttrHandler.o \
		CGConnectHandler.o \
		CGTeamDismissHandler.o \
		CGStopTeamFollowHandler.o \
		CGShopCloseHandler.o \
		GWCityCloseHandler.o \
		CGAskMyBagListHandler.o \
		CGGuildApplyHandler.o \
		CGBBSApplyHandler.o \
		CGCharJumpHandler.o \
		WGTeamAskApplyHandler.o \
		CGExchangeCancelHandler.o \
		GCCityNotifyHandler.o \
		WGTeamListHandler.o \
		CGAskTeamFollowHandler.o \
		CGAskChangeSceneHandler.o \
		CGAskDetailAbilityInfoHandler.o \
		CGExchangeSynchMoneyIIHandler.o \
		WGGuildReturnHandler.o \
		CGUnEquipHandler.o \
		CGAskDetaiXinFaListHandler.o \
		CGApplyPirvateInfoHandler.o \
		CGCharStopLogicHandler.o \
		CGEventRequestHander.o \
		CGMissionSubmitHander.o \
		CGChannelDismissHandler.o \
		CGCharAllTitlesHandler.o \
		CGGuildJoinHandler.o \
		CGAttackHandler.o \
		WGTeamErrorHandler.o \
		WGGuildErrorHandler.o \
		CGMissionAbandonHander.o \
		CGAskDetailSkillListHandler.o \
		CGPlayerShopSizeHandler.o \
		WGSystemMsgHandler.o \
		CGPlayerShopApplyHandler.o \
		WGRetSceneDataHandler.o \
		WGTeamResultHandler.o \
		CGBankMoneyHandler.o \
		CGMissionAcceptHander.o \
		CGIssuePetPlacardHandler.o \
		CGExchangeSynchLockHandler.o \
		CGItemSynchHandler.o \
		CGPlayerShopPartnerHandler.o \
		CGAskDetailAttribHandler.o \
		CGPlayerCallOfResultHandler.o \
		CGStallDefaultPageHandler.o \
		CGCommandHandler.o \
		CGDiscardEquipHandler.o \
		CGSkillHandler.o \
		WGGuildHandler.o \
		CGOpenItemBoxHander.o \
		CGShopBuyHandler.o \
		CGStallBuyHandler.o \
		CGPlayerShopEstablishHandler.o \
		CGReqResetAttrHandler.o \
		CGAskMissionDescHander.o \
		WGCallOfHumanHandler.o \
		SSScenePlayerCountHandler.o \
		CGCharPositionWarpHandler.o \
		CGChannelInviteHandler.o \
		WGFingerHandler.o \
		GWHandler.o \
		CGCharUpdateCurTitleHandler.o \
		CGStallShopNameHandler.o \
		CGPackage_SwipItemHandle.o \
		CGStallApplyHandler.o \
		CGPlayerShopMoneyHandler.o \
		CGCharSitHandler.o \
		CGPlayerShopAcquireShopListHandler.o \
		CGExchangeSynchItemIIHandler.o \
		SSConnectHandler.o \
		CGChannelKickHandler.o \
		WGTeamMemberInfoHandler.o \
		WGRetUserDataHandler.o \
		CGCharCancelSkillHandler.o \
		CGPickBoxItemHandler.o \
		CGReqManualAttrHandler.o \
		CGBuyHandler.o \
		CGShopSellHandler.o \
		CGChatHandler.o \
		CGStallOpenHandler.o \
		CGAskJoinMenpaiHandler.o \
		CGTeamAppointHandler.o \
		CGTeamInviteHandler.o \
		WGTeamLeaderAskInviteHandler.o \
		CGSystemMsgHandler.o \
		GGSceneNotifyHandler.o \
		CGPlayerShopBuyShopHandler.o \
		WGCityErrorHandler.o \
		CGAskSettingHandler.o \
		CGMissionRefuseHander.o \
		CGPlayerShopOpenStallHandler.o \
		CGExchangeOkIIIHandler.o \
		WGTeamAskInviteHandler.o \
		CGEnterSceneHandler.o \
		CGMinorPasswordHandler.o \
		CGRemoveGemHandler.o \
		CGBankAcquireListHandler.o \
		CGExchangeApplyIHandler.o \
		CGMoveHandler.o \
		GWCityCloseSuccessHandler.o \
		CGGemCompoundHandler.o \
		CGStallRemoveItemHandler.o \
		CGUseItemHandler.o \
		CGAskMailHandler.o \
		CGStallEstablishHandler.o \
		GCHandler.o \
		CGExecuteScriptHandler.o \
		CGBBSSychMessagesHandler.o \
		CGCityAskAttrHandler.o \
		CGCharAskEquipmentHandler.o \
		CGRelationHandler.o \
		CGMailHandler.o \
		CGLockTargetHandler.o \
		CGLeaveSceneHandler.o \
		CGReqLevelUpHandler.o \
		CGSplitItemHandler.o \
		CGCharIdleHandler.o \
		CGManipulatePetHandler.o \
		CGUseGemHandler.o \
		CGPlayerShopAcquireItemListHandler.o \
		WGCityApplyNewCityHandler.o \
		CGUseEquipHandler.o \
		CGAskTeamInfoHandler.o \
		CGPlayerShopBuyItemHandler.o \
		WGRetChangeSceneHandler.o \
		CGAskPrivateInfoHandler.o \
		CGReturnTeamFollowHandler.o \
		CGDiscardItemHandler.o \
		CGDispelBuffReqHandler.o \
		WGMailHandler.o \
		CGMissionContinueHander.o \
		CGStallItemPriceHandler.o \
		CGAskLockObjHandler.o \
		WGNotifyUserHandler.o \
		WGTeamFollowListHandler.o \
		WGChannelResultHandler.o \
		CGModifySettingHandler.o \
		GWCityOptHandler.o \
		CGBankCloseHandler.o \
		CGStallAddItemHandler.o \
		GWCityApplyNewCityHandler.o \
		CGPlayerShopDescHandler.o \
		CGTeamLeaderRetInviteHandler.o \
		CGUseAbilityHandler.o \
		CGGuildHandler.o \
		WGCityCloseSuccessHandler.o \
		WGChatHandler.o \
		CGStallCloseHandler.o \
		CGCharMoodStateHandler.o \
		CGTestHandler.o \
		CGPlayerShopAskForRecordHandler.o \
		WGCityCloseHandler.o \
		CGPlayerDieResultHandler.o \
		CGExchangeReplyIHandler.o \
		CGPlayerShopOnSaleHandler.o \
		GCCityAttrHandler.o \
		CGSetMoodToHeadHandler.o \
		CGMissionCheckHandler.o \
		CGHeartBeatHandler.o \
		CGSetPetAttribHandler.o \
		CGOtherEquipHandler.o \
		WGCityInitInfoHandler.o

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
