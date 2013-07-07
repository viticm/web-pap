# @desc makefile for Server
# @author viticm<viticm.ti@gmail.com>
# @date 2013-07-07 10:10:29
include ../../premake.mk

CFLAGS  = -I$(BASEDIR)/Server/Obj -I$(BASEDIR)/Server/Main -I$(BASEDIR)/Server/Ability -I$(BASEDIR)/Server/Player -I$(BASEDIR)/Server/Scene -I$(BASEDIR)/Server/Scene/Scan -I$(BASEDIR)/Server/MenPai -I$(BASEDIR)/Server/Packets -I$(BASEDIR)/Server/Skills -I$(BASEDIR)/Server/Skills/SkillLogic -I$(BASEDIR)/Server/Skills/SkillLogic/Pet -I$(BASEDIR)/Server/Skills/SkillLogic/Common -I$(BASEDIR)/Server/Skills/SkillLogic/Human -I$(BASEDIR)/Server/Skills/SkillLogic/Item -I$(BASEDIR)/Server/Skills/ImpactLogic -I$(BASEDIR)/Server/Skills/SpecialObjLogic -I$(BASEDIR)/Server/ActionModule -I$(BASEDIR)/Server/Base -I$(BASEDIR)/Server/Other -I$(BASEDIR)/Server/Team -I$(BASEDIR)/Server/SMU -I$(BASEDIR)/Server/Mission -I$(BASEDIR)/Server/EventModule -I$(BASEDIR)/Server/DB -I$(BASEDIR)/Server/Item -I$(BASEDIR)/Server/AI -I$(BASEDIR)/Server/Script -I$(BASEDIR)/Server $(LUA_INCLUDES)
LDFLAGS =
DIRS =  
OBJS =  StrTable.o \
		IDTable.o \
		Thread.o \
		TimeManager.o \
		LogDefine.o \
		ObjPool.o \
		Log.o \
		Config.o \
		File.o \
		FoxLuaScript.o \
		Ini.o

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
