# @desc makefile for Common
# @author viticm<viticm.ti@gmail.com>
# @date 2013-06-25 20:00:11
include ../../../premake.mk

CFLAGS  = -I$(BASEDIR)/Common/DataBase -I$(BASEDIR)/Common/Packets -I$(BASEDIR)/Common/DBSystem -I$(BASEDIR)/Common/DBSystem/DataBase -I$(BASEDIR)/Common/Combat -I$(BASEDIR)/Common/Net -I$(BASEDIR)/Common $(SERVER_BASE_INCLUDES)
LDFLAGS =
DIRS =  
OBJS =  DBManager.o \
		DBItemSerial.o \
		DBTaskList.o \
		DBItemList.o \
		ODBCInterface.o \
		DBEquipBaseList.o \
		DBSkillList.o \
		DBRelationList.o \
		DBInterface.o \
		DBCharFullData.o \
		DBXinFaList.o \
		ODBCBase.o \
		DBWebShopInfo.o \
		DBCharList.o \
		DBCoolDownInfo.o \
		DBTitleInfo.o \
		DBImpactList.o \
		DBPetList.o \
		DBGuildInfo.o \
		SqlTemplate.o \
		DBMailInfo.o \
		DBDeleteCharOp.o \
		DBCreateCharOp.o \
		DBPrivateInfo.o \
		DBAbilityList.o

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
