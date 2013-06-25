# @desc makefile for Server
# @author viticm<viticm.ti@gmail.com>
# @date 2013-06-25 20:00:04
include ../premake.mk

CFLAGS = -I$(BASEDIR)/Server/EventModule -I$(BASEDIR)/Server/Item -I$(BASEDIR)/Server/Script -I$(BASEDIR)/Server/Main -I$(BASEDIR)/Server/Obj -I$(BASEDIR)/Server/Team -I$(BASEDIR)/Server/DB -I$(BASEDIR)/Server/MenPai -I$(BASEDIR)/Server/Packets -I$(BASEDIR)/Server/AI -I$(BASEDIR)/Server/Player -I$(BASEDIR)/Server/ActionModule -I$(BASEDIR)/Server/Skills -I$(BASEDIR)/Server/Skills/SpecialObjLogic -I$(BASEDIR)/Server/Skills/SkillLogic -I$(BASEDIR)/Server/Skills/SkillLogic/Item -I$(BASEDIR)/Server/Skills/SkillLogic/Common -I$(BASEDIR)/Server/Skills/SkillLogic/Human -I$(BASEDIR)/Server/Skills/SkillLogic/Pet -I$(BASEDIR)/Server/Skills/ImpactLogic -I$(BASEDIR)/Server/Mission -I$(BASEDIR)/Server/Ability -I$(BASEDIR)/Server/Other -I$(BASEDIR)/Server/Scene -I$(BASEDIR)/Server/Scene/Scan -I$(BASEDIR)/Server/SMU -I$(BASEDIR)/Server/Base
debug:LDFLAGS = 
release:LDFLAGS = 

DIRS = EventModule Item Script Main Obj Team DB MenPai Packets AI Player ActionModule Skills Mission Ability Other Scene SMU Base
DEBUG_DIRS = EventModule Item Script Main Obj Team DB MenPai Packets AI Player ActionModule Skills Mission Ability Other Scene SMU Base

OBJS =  

debug:$(OBJS)
	for dir in $(DEBUG_DIRS); do \
		$(MAKE) debug -C $$dir; \
	done
	$(CPP) -o ./Server $(OBJS) EventModule/*.o Item/*.o Script/*.o Main/*.o Obj/*.o Team/*.o DB/*.o MenPai/*.o Packets/*.o AI/*.o Player/*.o ActionModule/*.o Skills/*.o Skills/SpecialObjLogic/*.o Skills/SkillLogic/*.o Skills/SkillLogic/Item/*.o Skills/SkillLogic/Common/*.o Skills/SkillLogic/Human/*.o Skills/SkillLogic/Pet/*.o Skills/ImpactLogic/*.o Mission/*.o Ability/*.o Other/*.o Scene/*.o Scene/Scan/*.o SMU/*.o Base/*.o $(LDFLAGS) $(GLDFLAGS)

release:$(OBJS)
	for dir in $(DIRS); do \
		$(MAKE) release -C $$dir; \
	done
	$(CPP) -o ./Server $(OBJS) EventModule/*.o Item/*.o Script/*.o Main/*.o Obj/*.o Team/*.o DB/*.o MenPai/*.o Packets/*.o AI/*.o Player/*.o ActionModule/*.o Skills/*.o Skills/SpecialObjLogic/*.o Skills/SkillLogic/*.o Skills/SkillLogic/Item/*.o Skills/SkillLogic/Common/*.o Skills/SkillLogic/Human/*.o Skills/SkillLogic/Pet/*.o Skills/ImpactLogic/*.o Mission/*.o Ability/*.o Other/*.o Scene/*.o Scene/Scan/*.o SMU/*.o Base/*.o $(LDFLAGS) $(GLDFLAGS)

all:debug

clean:
	for dir in $(DIRS); do \
		$(MAKE) clean -C $$dir; \
	done
	$(RM) -f *.o Server
