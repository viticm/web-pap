UNIX_ODBC_INCLUDES = /usr/local/unixODBC/include
UNIX_ODBC_LIBS     = /usr/local/unixODBC/lib
MYSQL_INCLUDES     = /usr/local/mysql/include
MYSQL_CLIENT_LIBS  = /usr/local/mysql/lib

RM = rm
DIRS = Billing Login ShareMemory World Server
DEBUG_DIRS = Billing Login ShareMemory World Server

all:debug

debug:premake.mk
	for dir in $(DEBUG_DIRS); do \
		$(MAKE) debug -C $$dir; \
	done

clean:
	for dir in $(DIRS); do \
		$(MAKE) clean -C $$dir; \
	done
	touch ./premake.mk
	$(RM) -f ./premake.mk

premake.mk:premake
	echo > premake.mk
	echo BASEDIR = `pwd` >> premake.mk
	echo UNIX_ODBC_INCLUDES = -I$(UNIX_ODBC_INCLUDES) >> premake.mk 
	echo UNIX_ODBC_LIBS     = -I$(UNIX_ODBC_LIBS) >> premake.mk
	echo MYSQL_INCLUDES     = -I$(MYSQL_INCLUDES) >> premake.mk
	echo MYSQL_CLIENT_LIBS  = -L$(MYSQL_CLIENT_LIBS) >> premake.mk
	cat ./premake >> premake.mk


