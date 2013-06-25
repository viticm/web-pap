# @desc makefile for Server
# @author viticm<viticm.ti@gmail.com>
# @date 2013-06-25 20:00:05
include ../../premake.mk

CFLAGS  = -I$(BASEDIR)/Server/EventModule -I$(BASEDIR)/Server/Item -I$(BASEDIR)/Server/Script -I$(BASEDIR)/Server/Main -I$(BASEDIR)/Server/Obj -I$(BASEDIR)/Server/Team -I$(BASEDIR)/Server/DB -I$(BASEDIR)/Server/MenPai -I$(BASEDIR)/Server/Packets -I$(BASEDIR)/Server/AI -I$(BASEDIR)/Server/Player -I$(BASEDIR)/Server/ActionModule -I$(BASEDIR)/Server/Skills -I$(BASEDIR)/Server/Skills/SpecialObjLogic -I$(BASEDIR)/Server/Skills/SkillLogic -I$(BASEDIR)/Server/Skills/SkillLogic/Item -I$(BASEDIR)/Server/Skills/SkillLogic/Common -I$(BASEDIR)/Server/Skills/SkillLogic/Human -I$(BASEDIR)/Server/Skills/SkillLogic/Pet -I$(BASEDIR)/Server/Skills/ImpactLogic -I$(BASEDIR)/Server/Mission -I$(BASEDIR)/Server/Ability -I$(BASEDIR)/Server/Other -I$(BASEDIR)/Server/Scene -I$(BASEDIR)/Server/Scene/Scan -I$(BASEDIR)/Server/SMU -I$(BASEDIR)/Server/Base -I$(BASEDIR)/Server
LDFLAGS =
DIRS =  
OBJS =  SpecialPool.o \
		Obj_Monster_Attributes.o \
		Obj_Human.o \
		MonsterPool.o \
		Obj_Pet_Attributes.o \
		Obj_Pet_Calc.o \
		ItemBoxManager.o \
		PetPool.o \
		Obj_Character_Attributes.o \
		Obj_Human_Calc.o \
		ItemBoxPool.o \
		Obj_Character_MenPai.o \
		Obj_Special.o \
		Obj_Character_Event.o \
		Obj_Character_Impact.o \
		Obj_Character_Skill.o \
		PetManager.o \
		HumanManager.o \
		CharacterManager.o \
		PetPlacard.o \
		ObjManager.o \
		ObjSingleManager.o \
		Obj_Character.o \
		PlatformManager.o \
		Obj_Human_AttrRefesh.o \
		Obj_Character_DirtyFlag.o \
		Obj_Monster.o \
		Obj_Human_Skill.o \
		Obj_Pet_AttrRefesh.o \
		Obj_Platform.o \
		Obj_Character_Logic.o \
		Obj_Monster_AttrRefesh.o \
		PlatformPool.o \
		Obj_Pet_Skill.o \
		Obj_Dynamic.o \
		SpecialManager.o \
		Obj_Monster_Calc.o \
		Obj_Static.o \
		Obj_Human_Attributes.o \
		Obj.o \
		Obj_Pet.o \
		MonsterManager.o \
		Obj_Monster_Skill.o \
		Obj_ItemBox.o

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
