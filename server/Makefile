premake.mk:premake
	echo > premake.mk
	echo BASEDIR=`pwd` >> premake.mk
	cat ./premake >> premake.mk
	sed -i 's;<TAB>;\t;g' premake.mk
all:premake.mk
clean:
	touch ./premake.mk
	$(RM) -f ./premake.mk
