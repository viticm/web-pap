# @desc makefile for Billing
# @author viticm<viticm.ti@gmail.com>
# @date 2013-06-25 20:00:12
include ../premake.mk

CFLAGS = -I$(BASEDIR)/Billing/Main -I$(BASEDIR)/Billing/Packets $(SERVER_BASE_INCLUDES)
debug:LDFLAGS =  $(SERVER_BASE_LDS)
release:LDFLAGS =  $(SERVER_BASE_LDS)

DIRS = Main Packets
DEBUG_DIRS = Main Packets

OBJS =  

debug:$(OBJS)
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

clean:
	for dir in $(DIRS); do \
		$(MAKE) clean -C $$dir; \
	done
	$(RM) -f *.o Billing