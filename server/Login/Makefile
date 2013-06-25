# @desc makefile for Login
# @author viticm<viticm.ti@gmail.com>
# @date 2013-06-25 20:00:13
include ../premake.mk

CFLAGS = -I$(BASEDIR)/Login/Main -I$(BASEDIR)/Login/DB -I$(BASEDIR)/Login/Packets -I$(BASEDIR)/Login/Process -I$(BASEDIR)/Login/Player $(SERVER_BASE_INCLUDES)
debug:LDFLAGS =  $(SERVER_BASE_LDS)
release:LDFLAGS =  $(SERVER_BASE_LDS)

DIRS = Main DB Packets Process Player
DEBUG_DIRS = Main DB Packets Process Player

OBJS =  

debug:$(OBJS)
	for dir in $(DEBUG_DIRS); do \
		$(MAKE) debug -C $$dir; \
	done
	$(CPP) -o ./Login $(OBJS) Main/*.o DB/*.o Packets/*.o Process/*.o Player/*.o $(LDFLAGS) $(GLDFLAGS)

release:$(OBJS)
	for dir in $(DIRS); do \
		$(MAKE) release -C $$dir; \
	done
	$(CPP) -o ./Login $(OBJS) Main/*.o DB/*.o Packets/*.o Process/*.o Player/*.o $(LDFLAGS) $(GLDFLAGS)

all:debug

clean:
	for dir in $(DIRS); do \
		$(MAKE) clean -C $$dir; \
	done
	$(RM) -f *.o Login
