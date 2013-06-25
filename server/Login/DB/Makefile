# @desc makefile for Login
# @author viticm<viticm.ti@gmail.com>
# @date 2013-06-25 20:00:13
include ../../premake.mk

CFLAGS  = -I$(BASEDIR)/Login/Main -I$(BASEDIR)/Login/DB -I$(BASEDIR)/Login/Packets -I$(BASEDIR)/Login/Process -I$(BASEDIR)/Login/Player -I$(BASEDIR)/Login $(SERVER_BASE_INCLUDES)
LDFLAGS =
DIRS =  
OBJS =  DBThread.o \
		LoginDBManager.o \
		DBThreadManager.o \
		CharConfig.o \
		DBLogicManager.o

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
