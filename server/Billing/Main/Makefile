# @desc makefile for Billing
# @author viticm<viticm.ti@gmail.com>
# @date 2013-08-14 11:20:18
include ../../premake.mk

CFLAGS  = -I$(BASEDIR)/Billing/Main -I$(BASEDIR)/Billing/Packets -I$(BASEDIR)/Billing $(SERVER_BASE_INCLUDES)
LDFLAGS =
DIRS =  
OBJS =  PlayerPool.o \
		DBManager.o \
		WebPlayer.o \
		ODBCInterface.o \
		PlayerManager.o \
		Billing.o \
		ServerPlayer.o \
		UserDBManager.o \
		ServerManager.o \
		Player.o

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
