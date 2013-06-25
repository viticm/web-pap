# @desc makefile for ShareMemory
# @author viticm<viticm.ti@gmail.com>
# @date 2013-06-25 20:00:12
include ../../premake.mk

CFLAGS  = -I$(BASEDIR)/ShareMemory/Main -I$(BASEDIR)/ShareMemory/DB -I$(BASEDIR)/ShareMemory/ShareData -I$(BASEDIR)/ShareMemory $(SERVER_BASE_INCLUDES)
LDFLAGS =
DIRS =  
OBJS =  SMConfig.o \
		ShareMemory.o \
		CommandThread.o

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
