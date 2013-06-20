
BASEDIR=/home/dc/develop/pap/server

COMMON_INCLUDES           = -I$(BASEDIR)/Common \
                            -I$(BASEDIR)/Common/Combat \
                            -I$(BASEDIR)/Common/DataBase \
                            -I$(BASEDIR)/Common/DBSystem \
                            -I$(BASEDIR)/Common/Net \
                            -I$(BASEDIR)/Common/Packets

SERVER_BASE_INCLUDES      = -I$(BASEDIR)/Server/Base

BILLING_INCLUDES          = -I$(BASEDIR)/Billing \
                            -I$(BASEDIR)/Billing/Main \
                            -I$(BASEDIR)/Billing/Packets

LOGIN_INCLUDES            = -I$(BASEDIR)/Login \
                            -I$(BASEDIR)/Login/DB \
                            -I$(BASEDIR)/Login/Main \
                            -I$(BASEDIR)/Login/Packets \
                            -I$(BASEDIR)/Login/Player \
                            -I$(BASEDIR)/Login/Process

SERVER_INCLUDES           = -I$(BASEDIR)/Server \
                            -I$(BASEDIR)/Server/Ability \
                            -I$(BASEDIR)/Server/ActionModule \
                            -I$(BASEDIR)/Server/AI \
                            -I$(BASEDIR)/Server/Base \
                            -I$(BASEDIR)/Server/DB \
                            -I$(BASEDIR)/Server/EventModule \
                            -I$(BASEDIR)/Server/Item \
                            -I$(BASEDIR)/Server/Main \
                            -I$(BASEDIR)/Server/MenPai \
                            -I$(BASEDIR)/Server/Mission \
                            -I$(BASEDIR)/Server/Obj \
                            -I$(BASEDIR)/Server/Other \
                            -I$(BASEDIR)/Server/Packets \
                            -I$(BASEDIR)/Server/Player \
                            -I$(BASEDIR)/Server/Scene \
                            -I$(BASEDIR)/Server/Script \
                            -I$(BASEDIR)/Server/Skills \
                            -I$(BASEDIR)/Server/SMU \
                            -I$(BASEDIR)/Server/Team

SHARE_MEMORY_INCLUDES     = -I$(BASEDIR)/ShareMemory \
                            -I$(BASEDIR)/ShareMemory/DB \
                            -I$(BASEDIR)/ShareMemory/Main \
                            -I$(BASEDIR)/ShareMemory/ShareData


WORLD_INCLUDES            = -I$(BASEDIR)/World \
                            -I$(BASEDIR)/World/Main \
                            -I$(BASEDIR)/World/Packets \
                            -I$(BASEDIR)/World/WorldData


ARFLAGS = -sr
AR      = ar
CC      = gcc
CXX     = g++
CPP     = g++

