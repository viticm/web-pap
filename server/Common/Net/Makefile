# @desc makefile for Common
# @author viticm<viticm.ti@gmail.com>
# @date 2013-06-25 20:00:12
include ../../premake.mk

CFLAGS  = -I$(BASEDIR)/Common/DataBase -I$(BASEDIR)/Common/Packets -I$(BASEDIR)/Common/DBSystem -I$(BASEDIR)/Common/DBSystem/DataBase -I$(BASEDIR)/Common/Combat -I$(BASEDIR)/Common/Net -I$(BASEDIR)/Common $(SERVER_BASE_INCLUDES)
LDFLAGS =
DIRS =  
OBJS =  SocketOutputStream.o \
		ServerSocket.o \
		Packet.o \
		SocketInputStream.o \
		SocketAPI.o \
		FileAPI.o \
		Socket.o

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
