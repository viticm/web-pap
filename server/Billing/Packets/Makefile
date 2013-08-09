# @desc makefile for Billing
# @author viticm<viticm.ti@gmail.com>
# @date 2013-08-08 16:15:53
include ../../premake.mk

CFLAGS  = -I$(BASEDIR)/Billing/Main -I$(BASEDIR)/Billing/Packets -I$(BASEDIR)/Billing $(SERVER_BASE_INCLUDES)
LDFLAGS =
DIRS =  
OBJS =  BLRetAuthHandler.o \
		SSScenePlayerCountHandler.o \
		BWConnectHandler.o \
		BWValidateUserHandler.o \
		SSConnectHandler.o \
		LBAskAuthHandler.o \
		WBRetValidateUserHandler.o

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
