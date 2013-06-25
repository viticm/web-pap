# @desc makefile for Server
# @author viticm<viticm.ti@gmail.com>
# @date 2013-06-25 20:00:08
include ../../../premake.mk

CFLAGS  = -I$(BASEDIR)/Server/EventModule -I$(BASEDIR)/Server/Item -I$(BASEDIR)/Server/Script -I$(BASEDIR)/Server/Main -I$(BASEDIR)/Server/Obj -I$(BASEDIR)/Server/Team -I$(BASEDIR)/Server/DB -I$(BASEDIR)/Server/MenPai -I$(BASEDIR)/Server/Packets -I$(BASEDIR)/Server/AI -I$(BASEDIR)/Server/Player -I$(BASEDIR)/Server/ActionModule -I$(BASEDIR)/Server/Skills -I$(BASEDIR)/Server/Skills/SpecialObjLogic -I$(BASEDIR)/Server/Skills/SkillLogic -I$(BASEDIR)/Server/Skills/SkillLogic/Item -I$(BASEDIR)/Server/Skills/SkillLogic/Common -I$(BASEDIR)/Server/Skills/SkillLogic/Human -I$(BASEDIR)/Server/Skills/SkillLogic/Pet -I$(BASEDIR)/Server/Skills/ImpactLogic -I$(BASEDIR)/Server/Mission -I$(BASEDIR)/Server/Ability -I$(BASEDIR)/Server/Other -I$(BASEDIR)/Server/Scene -I$(BASEDIR)/Server/Scene/Scan -I$(BASEDIR)/Server/SMU -I$(BASEDIR)/Server/Base -I$(BASEDIR)/Server
LDFLAGS =
DIRS =  
OBJS =  StdImpact048.o \
		StdImpact009.o \
		SOT_Unbreakable.o \
		StdImpact055.o \
		StdImpact046.o \
		StdImpact017.o \
		StdImpact012.o \
		SOT_Dali012.o \
		StdImpact052.o \
		ImpactLogic.o \
		StdImpact029.o \
		StdImpact025.o \
		StdImpact015.o \
		StdImpact018.o \
		StdImpact019.o \
		StdImpact026.o \
		StdImpact002.o \
		StdImpact044.o \
		StdImpact031.o \
		StdImpact050.o \
		SOT_TianShan017.o \
		StdImpact049.o \
		StdImpact003.o \
		StdImpact033.o \
		StdImpact021.o \
		StdImpact028.o \
		SOT_Dali007.o \
		StdImpact022.o \
		SOT_ProlongSpecificImpact.o \
		StdImpact030.o \
		StdImpact056.o \
		DS_WuDang010.o \
		StdImpact000.o \
		SOT_XingXiu017.o \
		StdImpact043.o \
		StdImpact007.o \
		StdImpact053.o \
		StdImpact020.o \
		StdImpact005.o \
		StdImpact013.o \
		StdImpact027.o \
		SOT_Emei016.o \
		DS_Emei014.o \
		StdImpact045.o \
		StdImpact036.o \
		StdImpact023.o \
		StdImpact035.o \
		StdImpact004.o \
		StdImpact057.o \
		StdImpact054.o \
		StdImpact041.o \
		StdImpact039.o \
		StdImpact006.o \
		StdImpact034.o \
		StdImpact011.o \
		StdImpact001.o \
		StdImpact042.o \
		StdImpact010.o \
		StdImpact016.o \
		StdImpact038.o \
		StdImpact024.o \
		StdImpact051.o \
		StdImpact047.o \
		StdImpact032.o \
		StdImpact037.o \
		StdImpact008.o \
		StdImpact040.o \
		StdImpact014.o

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
