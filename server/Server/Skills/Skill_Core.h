/**
 * PAP Server Engine ( https://github.com/viticm/web-pap )
 * $Id Billing.cpp
 * @link https://github.com/viticm/web-pap/tree/master/server for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-8-29 15:43:15
 * @uses the skill core module
 */
#ifndef SKILL_CORE_H
#define SKILL_CORE_H

#include "Type.h"
#include "Obj_Character.h"
#include "DataRecords.h"
#include "SkillInfo.h"
#include "Combat_Core.h"

namespace Combat_Module
{
    
    namespace Skill_Module
    {
        using namespace Combat_Module ;
        
        class SkillCore_T
        {
            friend class Combat_Module::CombatCore_T ;
            friend class Obj_Character ;
            public:
                SkillCore_T(){} ;
                ~SkillCore_T(){} ;
                BOOL InstanceSkill( SkillInfo_T& rSkillInfoOut, Obj_Character& rMe, SkillID_t nSkill, BYTE nLevel ) const ;
                BOOL ProcessSkillRequest( Obj_Character& rMe, 
                                          SkillID_t nSkillID, 
                                          BYTE nLevel, 
                                          ObjID_t nTargetID, 
                                          WORLD_POS const& rTargetPos, 
                                          FLOAT fTargetDir, 
                                          GUID_t guidTarget ) const ;
            protected:
                BOOL ActiveSkillNow( Obj_Character& rMe ) const ;
                VOID OnException( Obj_Character& rMe ) const ;
            private:
        };
        BOOL Skill_IsSkillInCollection( SkillInfo_T const& rSkillInfo, INT nCollection ) ;
        INT Skill_GetSkillInfoDescriptorValueByIndex( SkillInfo_T const& rSkillInfo, INT nIndex ) ;
        ConDepTerm_T const* Skill_GetConDepTermByIndex( SkillInfo_T const& rSkillInfo, INT nIndex ) ;
        
    } ;
} ;
extern Combat_Module::Skill_Module::SkillCore_T g_SkillCore ;
#endif //SKILL_CORE_H
