# @desc makefile for World
# @author viticm<viticm.ti@gmail.com>
# @date 2013-06-25 20:00:12
include ../premake.mk

CFLAGS = -I$(BASEDIR)/World/Main -I$(BASEDIR)/World/Packets -I$(BASEDIR)/World/WorldData $(SERVER_BASE_INCLUDES)
debug:LDFLAGS =  $(SERVER_BASE_LDS)
release:LDFLAGS =  $(SERVER_BASE_LDS)

DIRS = Main Packets WorldData
DEBUG_DIRS = Main Packets WorldData

OBJS =  

debug:$(OBJS)
	for dir in $(DEBUG_DIRS); do \
		$(MAKE) debug -C $$dir; \
	done
	$(CPP) -o ./World $(OBJS) Main/*.o Packets/*.o WorldData/*.o $(LDFLAGS) $(GLDFLAGS)

release:$(OBJS)
	for dir in $(DIRS); do \
		$(MAKE) release -C $$dir; \
	done
	$(CPP) -o ./World $(OBJS) Main/*.o Packets/*.o WorldData/*.o $(LDFLAGS) $(GLDFLAGS)

all:debug

clean:
	for dir in $(DIRS); do \
		$(MAKE) clean -C $$dir; \
	done
	$(RM) -f *.o World
