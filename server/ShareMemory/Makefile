# @desc makefile for ShareMemory
# @author viticm<viticm.ti@gmail.com>
# @date 2013-06-25 20:00:12
include ../premake.mk

CFLAGS = -I$(BASEDIR)/ShareMemory/Main -I$(BASEDIR)/ShareMemory/DB -I$(BASEDIR)/ShareMemory/ShareData $(SERVER_BASE_INCLUDES)
debug:LDFLAGS =  $(SERVER_BASE_LDS)
release:LDFLAGS =  $(SERVER_BASE_LDS)

DIRS = Main DB ShareData
DEBUG_DIRS = Main DB ShareData

OBJS =  

debug:$(OBJS)
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

clean:
	for dir in $(DIRS); do \
		$(MAKE) clean -C $$dir; \
	done
	$(RM) -f *.o ShareMemory
