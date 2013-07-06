--脚本号
x892003_g_scriptId = 892003

--**********************************
-- 
--**********************************
function x892003_StudyProperty(sceneId, selfId, lwIndex)		
	local itemIndex = LuaFnGetItemTableIndexByIndex( sceneId, selfId, 30 )
	local lw = LuaFnGetItemTableIndexByIndex( sceneId, selfId, lwIndex )
	if itemIndex~=20310181 and itemIndex~=20310182 and itemIndex~=20310183 then
		x892003_NotifyTip( sceneId, selfId, "材料不符" )
		return
	end
	if LuaFnGetAvailableItemCount(sceneId, selfId, itemIndex)<10 then
		x892003_NotifyTip( sceneId, selfId, "材料不足" )
		return
	end
	if lw~= 10157001 then
		x892003_NotifyTip( sceneId, selfId, "此装备无法学习技能" )
		return
	end
	local longwen1 = GetMissionData( sceneId, selfId, MY_LONGWEN1 )
	local longwen2 = GetMissionData( sceneId, selfId, MY_LONGWEN2 )
	local longwen3 = GetMissionData( sceneId, selfId, MY_LONGWEN3 )
	if itemIndex==20310181 and longwen1>0 then
		x892003_NotifyTip( sceneId, selfId, "您已学习过此技能，此处无法提升等级。" )
		return
	elseif itemIndex==20310182 and longwen2>0 then
		x892003_NotifyTip( sceneId, selfId, "您已学习过此技能，此处无法提升等级。" )
		return
	elseif itemIndex==20310183 and longwen3>0 then
		x892003_NotifyTip( sceneId, selfId, "您已学习过此技能，此处无法提升等级。" )
		return
	end
	local reply = CostMoney(sceneId,selfId,10000)
	if reply == -1 then
		x892003_NotifyTip( sceneId, selfId, "金钱不足" )
		return
	end
	if itemIndex==20310181 then
		LuaFnDelAvailableItem(sceneId,selfId,itemIndex,10)
		SetMissionData( sceneId, selfId, MY_LONGWEN1, 1 )
	elseif itemIndex==20310182 then
		LuaFnDelAvailableItem(sceneId,selfId,itemIndex,10)
		SetMissionData( sceneId, selfId, MY_LONGWEN2, 1 )
	elseif itemIndex==20310183 then
		LuaFnDelAvailableItem(sceneId,selfId,itemIndex,10)
		SetMissionData( sceneId, selfId, MY_LONGWEN3, 1 )
	end
	LuaFnSendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, 152, 0)
	x892003_NotifyTip( sceneId, selfId, "恭喜，技能学习成功" )
end

function x892003_UpdateProperty(sceneId, selfId, lwIndex)
	x892003_NotifyTip( sceneId, selfId, "123" )
end
--**********************************
--醒目提示
--**********************************
function x892003_NotifyTip( sceneId, selfId, Msg )
	BeginEvent( sceneId )
		AddText( sceneId, Msg )
	EndEvent( sceneId )
	DispatchMissionTips( sceneId, selfId )
end

--**********************************
--对话窗口信息提示
--**********************************
function x892003_MsgBox( sceneId, selfId, msg )
	BeginEvent( sceneId )
		AddText( sceneId, msg )
	EndEvent( sceneId )
	DispatchEventList( sceneId, selfId, -1 )
end
