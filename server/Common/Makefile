# @desc makefile for Common
# @author viticm<viticm.ti@gmail.com>
# @date 2013-06-25 20:00:09
include ../premake.mk

CFLAGS  = -I$(BASEDIR)/Common/DataBase -I$(BASEDIR)/Common/Packets -I$(BASEDIR)/Common/DBSystem -I$(BASEDIR)/Common/DBSystem/DataBase -I$(BASEDIR)/Common/Combat -I$(BASEDIR)/Common/Net -I$(BASEDIR)/Common $(SERVER_BASE_INCLUDES)
LDFLAGS =
DIRS =  DataBase Packets DBSystem Combat Net
OBJS =  SkillDataMgr.o \
		GameStruct.o \
		BuffImpactMgr.o \
		Rand.o \
		FileDataMgr.o \
		GameUtil.o \
		Assertx.o \
		PacketFactoryManager.o \
		ScriptCommandStruct.o \
		Chain.o \
		GameStruct_Pet.o \
		ShareMemAPI.o \
		GameStruct_MinorPasswd.o \
		GameStruct_Finger.o \
		CampDataMgr.o \
		DirectlyImpactMgr.o \
		GameStruct_Script.o \
		DB_Struct.o \
		GameDefine_Result.o \
		GameStruct_Relation.o

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
