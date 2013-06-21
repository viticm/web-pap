UNIX_ODBC_INCLUDES = /usr/local/unixODBC/include

premake.mk:premake
	echo > premake.mk
	echo BASEDIR = `pwd` >> premake.mk
	echo UNIX_ODBC_INCLUDES = -I$(UNIX_ODBC_INCLUDES) >> premake.mk 
	cat ./premake >> premake.mk
all:premake.mk
clean:
	touch ./premake.mk
	$(RM) -f ./premake.mk
