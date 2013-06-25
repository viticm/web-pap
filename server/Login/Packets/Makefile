# @desc makefile for Login
# @author viticm<viticm.ti@gmail.com>
# @date 2013-06-25 20:00:13
include ../../premake.mk

CFLAGS  = -I$(BASEDIR)/Login/Main -I$(BASEDIR)/Login/DB -I$(BASEDIR)/Login/Packets -I$(BASEDIR)/Login/Process -I$(BASEDIR)/Login/Player -I$(BASEDIR)/Login $(SERVER_BASE_INCLUDES)
LDFLAGS =
DIRS =  
OBJS =  CLAskCreateCharHander.o \
		CLAskDeleteCharHandler.o \
		LWAskDeleteCharHandler.o \
		LWAskCharLoginHandler.o \
		WLRetCharLoginHandler.o \
		CLAskCharListHandler.o \
		LCRetCharLoginHandler.o \
		LCStatusHandler.o \
		BLRetAuthHandler.o \
		SSScenePlayerCountHandler.o \
		LCRetDeleteCharHandler.o \
		SSConnectHandler.o \
		LCRetConnectHandler.o \
		CLConnectHandler.o \
		LCRetCharListHandler.o \
		LCRetCreateCharHandler.o \
		CLAskCharLoginHandler.o \
		WLRetDeleteCharHandler.o \
		LBAskAuthHandler.o \
		CLAskLoginHandler.o \
		LCRetLoginHandler.o

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
