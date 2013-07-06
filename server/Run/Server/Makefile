# @desc makefile for Server
# @author viticm<viticm.ti@gmail.com>
# @date 2013-07-06 13:55:02
include ../../premake.mk

CFLAGS = -I$(BASEDIR)/Server/Obj -I$(BASEDIR)/Server/Main -I$(BASEDIR)/Server/Ability -I$(BASEDIR)/Server/Player -I$(BASEDIR)/Server/Scene -I$(BASEDIR)/Server/Scene/Scan -I$(BASEDIR)/Server/MenPai -I$(BASEDIR)/Server/Packets -I$(BASEDIR)/Server/Skills -I$(BASEDIR)/Server/Skills/SkillLogic -I$(BASEDIR)/Server/Skills/SkillLogic/Pet -I$(BASEDIR)/Server/Skills/SkillLogic/Common -I$(BASEDIR)/Server/Skills/SkillLogic/Human -I$(BASEDIR)/Server/Skills/SkillLogic/Item -I$(BASEDIR)/Server/Skills/ImpactLogic -I$(BASEDIR)/Server/Skills/SpecialObjLogic -I$(BASEDIR)/Server/ActionModule -I$(BASEDIR)/Server/Base -I$(BASEDIR)/Server/Other -I$(BASEDIR)/Server/Team -I$(BASEDIR)/Server/SMU -I$(BASEDIR)/Server/Mission -I$(BASEDIR)/Server/EventModule -I$(BASEDIR)/Server/DB -I$(BASEDIR)/Server/Item -I$(BASEDIR)/Server/AI -I$(BASEDIR)/Server/Script -I$(BASEDIR)/Server
debug:LDFLAGS = 
release:LDFLAGS = 

DIRS = Log Config
DEBUG_DIRS = Log Config

OBJS =  

debug:$(OBJS)
	for dir in $(DEBUG_DIRS); do \
		$(MAKE) debug -C $$dir; \
	done
	$(CPP) -o ./Server $(OBJS) Log/*.o Config/*.o $(LDFLAGS) $(GLDFLAGS)

release:$(OBJS)
	for dir in $(DIRS); do \
		$(MAKE) release -C $$dir; \
	done
	$(CPP) -o ./Server $(OBJS) Log/*.o Config/*.o $(LDFLAGS) $(GLDFLAGS)

all:debug

clean:
	for dir in $(DIRS); do \
		$(MAKE) clean -C $$dir; \
	done
	$(RM) -f $(OBJS) Server 
