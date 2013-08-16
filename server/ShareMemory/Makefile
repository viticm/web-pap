# @desc makefile for ShareMemory
# @author viticm<viticm.ti@gmail.com>
# @date 2013-08-16 16:18:26
include ../premake.mk

CFLAGS = -I$(BASEDIR)/ShareMemory/Main -I$(BASEDIR)/ShareMemory/DB -I$(BASEDIR)/ShareMemory/ShareData -I$(BASEDIR)/ShareMemory $(SERVER_BASE_INCLUDES) $(SERVER_BASE_INCLUDES) -I$(BASEDIR)/Server/SMU $(MYSQL_INCLUDES) -I$(BASEDIR)/Server/Other
debug:LDFLAGS =  $(SERVER_BASE_LDS) $(MYSQL_CLIENT_LDS)
release:LDFLAGS =  $(SERVER_BASE_LDS) $(MYSQL_CLIENT_LDS)

DIRS = Main DB ShareData
DEBUG_DIRS = Main DB ShareData

OBJS =  $(BASEDIR)/Common/Assertx.o \
		$(BASEDIR)/Common/Net/FileAPI.o \
		$(BASEDIR)/Common/Net/Packet.o \
		$(BASEDIR)/Common/Net/ServerSocket.o \
		$(BASEDIR)/Common/Net/SocketAPI.o \
		$(BASEDIR)/Common/Net/Socket.o \
		$(BASEDIR)/Common/Net/SocketInputStream.o \
		$(BASEDIR)/Common/Net/SocketOutputStream.o \
		$(BASEDIR)/Common/GameUtil.o \
		$(BASEDIR)/Common/ShareMemAPI.o \
		$(BASEDIR)/Common/DBSystem/DataBase/DBAbilityList.o \
		$(BASEDIR)/Common/DBSystem/DataBase/DBCharFullData.o \
		$(BASEDIR)/Common/DBSystem/DataBase/DBCharList.o \
		$(BASEDIR)/Common/DBSystem/DataBase/DBCoolDownInfo.o \
		$(BASEDIR)/Common/DBSystem/DataBase/DBCreateCharOp.o \
		$(BASEDIR)/Common/DBSystem/DataBase/DBDeleteCharOp.o \
		$(BASEDIR)/Common/DBSystem/DataBase/DBEquipBaseList.o \
		$(BASEDIR)/Common/DBSystem/DataBase/DBGuildInfo.o \
		$(BASEDIR)/Common/DBSystem/DataBase/DBImpactList.o \
		$(BASEDIR)/Common/DBSystem/DataBase/DBInterface.o \
		$(BASEDIR)/Common/DBSystem/DataBase/DBItemList.o \
		$(BASEDIR)/Common/DBSystem/DataBase/DBItemSerial.o \
		$(BASEDIR)/Common/DBSystem/DataBase/DBMailInfo.o \
		$(BASEDIR)/Common/DBSystem/DataBase/DBManager.o \
		$(BASEDIR)/Common/DBSystem/DataBase/DBPetList.o \
		$(BASEDIR)/Common/DBSystem/DataBase/DBPrivateInfo.o \
		$(BASEDIR)/Common/DBSystem/DataBase/DBRelationList.o \
		$(BASEDIR)/Common/DBSystem/DataBase/DBSkillList.o \
		$(BASEDIR)/Common/DBSystem/DataBase/DBTaskList.o \
		$(BASEDIR)/Common/DBSystem/DataBase/DBTitleInfo.o \
		$(BASEDIR)/Common/DBSystem/DataBase/DBWebShopInfo.o \
		$(BASEDIR)/Common/DBSystem/DataBase/DBXinFaList.o \
		$(BASEDIR)/Common/DBSystem/DataBase/ODBCBase.o \
		$(BASEDIR)/Common/DBSystem/DataBase/ODBCInterface.o \
		$(BASEDIR)/Common/DBSystem/DataBase/SqlTemplate.o \
		$(BASEDIR)/Common/GameStruct.o \
		$(BASEDIR)/Common/DB_Struct.o \
		$(BASEDIR)/Server/Base/Config.o \
		$(BASEDIR)/Server/Base/Thread.o \
		$(BASEDIR)/Server/Base/Ini.o \
		$(BASEDIR)/Server/Base/Log.o \
		$(BASEDIR)/Server/Base/TimeManager.o \
		$(BASEDIR)/Server/Base/LogDefine.o \
		$(BASEDIR)/Server/SMU/ShareMemAO.o

debug:special $(OBJS)
	for dir in $(DEBUG_DIRS); do \
		$(MAKE) debug -C $$dir; \
	done
	$(CPP) -o ./ShareMemory $(OBJS) Main/*.o DB/*.o ShareData/*.o $(LDFLAGS) $(GLDFLAGS)

release:$(OBJS)
	for dir in $(DIRS); do \
		$(MAKE) release -C $$dir; \
	done
	$(CPP) -o ./ShareMemory $(OBJS) Main/*.o DB/*.o ShareData/*.o $(LDFLAGS) $(GLDFLAGS)

all:debug

special:
	$(RM) -f $(BASEDIR)/Common/PacketFactoryManager.o
	$(RM) -f $(BASEDIR)/Common/GameUtil.o
	$(RM) -f $(BASEDIR)/Server/Base/Log.o

clean:
	for dir in $(DIRS); do \
		$(MAKE) clean -C $$dir; \
	done
	$(RM) -f $(OBJS) ShareMemory 
