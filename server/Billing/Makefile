# @desc  make billing server
# @author viticm<viticm.ti@gmail.com>
# @date  2013-6-20 19:39:42
include ../premake.mk

DIRS          = Main Packets
DEBUG_DIRS    = Main Packets

OBJS          = 

debug:LDFLAGS = -L$(JJDIR)/network -L$(JJDIR)/database -L$(JJDIR)/misc -L$(JJDIR)/luawrapper -L$(JJDIR)/lualib/src
release:LDFLAGS = -L$(JJDIR)/network -L$(JJDIR)/database -L$(JJDIR)/misc -L$(JJDIR)/luawrapper -L$(JJDIR)/lualib/src

debug:$(OBJS)
	for dir in $(DEBUG_DIRS); do \
		$(MAKE) debug -C $$dir; \
	done
	$(CPP) -o ./gameserver $(OBJS) handler/*.o aoi/*.o $(LDFLAGS) $(GLDFLAGS)


