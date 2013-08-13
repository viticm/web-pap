# @desc makefile for Billing
# @author viticm<viticm.ti@gmail.com>
# @date 2013-08-12 22:01:14
include ../premake.mk

CFLAGS = -I$(BASEDIR)/Billing/Main -I$(BASEDIR)/Billing/Packets -I$(BASEDIR)/Billing $(SERVER_BASE_INCLUDES) $(SERVER_BASE_INCLUDES)
debug:LDFLAGS =  $(SERVER_BASE_LDS)
release:LDFLAGS =  $(SERVER_BASE_LDS)

DIRS = Main Packets
DEBUG_DIRS = Main Packets

OBJS =  $(BASEDIR)/Common/Assertx.o \
		$(BASEDIR)/Common/Net/FileAPI.o \
		$(BASEDIR)/Common/Net/Packet.o \
		$(BASEDIR)/Common/Net/ServerSocket.o \
		$(BASEDIR)/Common/Net/SocketAPI.o \
		$(BASEDIR)/Common/Net/Socket.o \
		$(BASEDIR)/Common/Net/SocketInputStream.o \
		$(BASEDIR)/Common/Net/SocketOutputStream.o \
		$(BASEDIR)/Server/Base/Log.o \
		$(BASEDIR)/Server/Base/TimeManager.o \
		$(BASEDIR)/Server/Base/LogDefine.o \
		$(BASEDIR)/Server/Base/Config.o \
		$(BASEDIR)/Server/Base/Thread.o \
		$(BASEDIR)/Server/Base/Ini.o \
		$(BASEDIR)/Common/GameUtil.o \
		$(BASEDIR)/Common/PacketFactoryManager.o \
		$(BASEDIR)/Common/Packets/LBAskAuth.o \
		$(BASEDIR)/Common/Packets/BWConnect.o \
		$(BASEDIR)/Common/Packets/BLRetAuth.o \
		$(BASEDIR)/Common/Packets/SSConnect.o \
		$(BASEDIR)/Common/Packets/WBRetValidateUser.o \
		$(BASEDIR)/Common/Packets/SSScenePlayerCount.o \
		$(BASEDIR)/Common/Util/md5.o

debug:special $(OBJS)
	for dir in $(DEBUG_DIRS); do \
		$(MAKE) debug -C $$dir; \
	done
	$(CPP) -o ./Billing $(OBJS) Main/*.o Packets/*.o $(LDFLAGS) $(GLDFLAGS)

release:$(OBJS)
	for dir in $(DIRS); do \
		$(MAKE) release -C $$dir; \
	done
	$(CPP) -o ./Billing $(OBJS) Main/*.o Packets/*.o $(LDFLAGS) $(GLDFLAGS)

all:debug

special:
	$(RM) -f $(BASEDIR)/Common/PacketFactoryManager.o
	$(RM) -f $(BASEDIR)/Common/GameUtil.o
	$(RM) -f $(BASEDIR)/Server/Base/Log.o

clean:
	for dir in $(DIRS); do \
		$(MAKE) clean -C $$dir; \
	done
	$(RM) -f $(OBJS) Billing 
