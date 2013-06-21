#!/bin/bash
cBaseDir=`pwd` # default use cur dir, you can define it
Arr_BinDir="Billing Server Login World ShareMemory"
Arr_ModelName="Billing Server Login World ShareMemory Common"
Arr_NotMakeFile="`pwd`"
Arr_Dir=`find ${cBaseDir} -type d`
cInludeFile=premake.mk

#@desc get include premake file by path
#@param string cPath
#@return string
function getIncludeFile()
{
    local cPath=${1}
    local iDepth=`echo ${cPath} | sed "s;${cBaseDir};;g" | awk -F '/' '{print NF}'`
    local cInludePath=""
    for (( i=1;i<iDepth;i++ ))
    do
        cInludePath+="../"
    done
    echo ${cInludePath}${cInludeFile}
}

#@desc check string is in array
#@param array Arr_Check
#@param mixd mCheck
#@return 0 or 1
function inArray()
{
    local mCheck=${1}
    local Arr_Check=${2}
    for check in ${Arr_Check}
    do
        if [[ ${mCheck} = ${check} ]] ; then
            return 0
        fi
    done
    return 1
}

#@desc get son dir array by path
#@param string cPath
#@param int iMaxdepth
#@return void
function getSonDirs()
{
    local cPath=${1}
    local iMaxdepth=${2}
    local Arr_FoundDir=""
    local Arr_SonDir=""
    if [[ "" != ${iMaxdepth} ]] ; then
        Arr_FoundDir=`find ${cPath} -maxdepth ${iMaxdepth} -type d`
    else
        Arr_FoundDir=`find ${cPath} -type d`
    fi
    
    for dir in ${Arr_FoundDir}
    do
        if [[ ${dir} != ${cPath} ]] ; then
            Arr_SonDir+="`echo ${dir} | sed "s;${cPath}/;;g"` "
        fi
    done
    echo ${Arr_SonDir}
}

#@desc get bin model name by dir
#@param string path
#@param array Arr_BinDir
#@return void
function getModelName()
{
    local cPath=${1}
    local Arr_ModelName=${2}
    for modelName in ${Arr_ModelName}
    do
        if [[ "" != `echo ${cPath} | sed -n "/${modelName}/="` ]] ; then
            echo ${modelName}
            return
        fi
    done
}

#@desc replace special words
#@param string cFileName
#@return void
function replaceSpecialWords()
{
#<TAB> \t | <S4> "    " | <DD> $$
    local cFileName=${1}
    sed -i 's;<TAB>;\t;g'  ${cFileName}
    sed -i 's;<S4>;    ;g' ${cFileName}
    sed -i 's;<DD>;$$;g'   ${cFileName}
    sed -i 's;<SLASH>;\\;g'  ${cFileName}
}

#@desc get will includes objs dirs
#@param string cPath
#@return void
function getSonDirObjs()
{
    local cPath=${1}
    local Arr_SonDir=`getSonDirs ${cPath}`
    local Arr_SonDirObjs=""
    for dir in ${Arr_SonDir}
    do
        Arr_SonDirObjs+="${dir}/*.o "
    done
    echo ${Arr_SonDirObjs}
}

#@desc get objs files in dir
#@param string cPath
#@return void
function getObjs()
{
    local cPath=${1}
    local Arr_FindFile=`find ${cPath} -maxdepth 1 -type f -name "*.cpp" -o -name "*.c"`
    local Arr_Objs=""
    for file in ${Arr_FindFile}
    do
        local cObjName=`basename ${file} | sed 's;\.cpp;\.o;g' | sed 's;\.c;\.o;g'`
        if [[ "" == ${Arr_Objs} ]] ; then
            Arr_Objs+=${cObjName}
        else
            Arr_Objs+=" <SLASH>\n<TAB><TAB>"${cObjName}
        fi
    done
    echo ${Arr_Objs}
}

#@desc main function
#@param void
#@return int
function main()
{
    for dir in ${Arr_Dir}
    do
        cInlude=`getIncludeFile ${dir} "${Arr_NotMakeFile}"`
        cCurDir=`basename ${dir}`
        cModleName=`getModelName ${dir} "${Arr_ModelName}"`
        Arr_Objs=`getObjs ${dir}`
        Arr_SonDir=`getSonDirs ${dir} 1`
        if inArray ${dir} "${Arr_NotMakeFile}"
        then :
            echo ${dir} not in make
        else
# get new file Makefile 
            if inArray ${cCurDir} "${Arr_BinDir}"
            then :
# need build bin file
                echo ${cModleName}
                Arr_SonDirObjs=`getSonDirObjs ${dir}`
                if [[ "Server" == ${cModleName} ]] ; then
                    cLdFlags="\$(COMMON_LD)"
                else
                    cLdFlags="\$(COMMON_LD) \$(SERVER_BASE_LDS)"
                fi
                cat > ${dir}/Makefile <<EOF
# @desc makefile for ${cModleName}
# @author viticm<viticm.ti@gmail.com>
# @date `date +"%Y-%m-%d %H:%M:%S"`
include ${cInlude}

CFLAGS =
debug:LDFLAGS = ${cLdFlags}
release:LDFLAGS = ${cLdFlags}

DIRS = ${Arr_SonDir}
DEBUG_DIRS = ${Arr_SonDir}

OBJS =  `echo -e "${Arr_Objs}"`

debug:\$(OBJS)
<TAB>for dir in \$(DEBUG_DIRS); do <SLASH>
<TAB><TAB>\$(MAKE) debug -C <DD>dir; <SLASH>
<TAB>done
<TAB>\$(CPP) -o ./${cModleName} \$(OBJS) ${Arr_SonDirObjs} \$(LDFLAGS) \$(GLDFLAGS)

release:\$(OBJS)
<TAB>for dir in \$(DIRS); do <SLASH>
<TAB><TAB>\$(MAKE) release -C <DD>dir; <SLASH>
<TAB>done
<TAB>\$(CPP) -o ./${cModleName} \$(OBJS) ${Arr_SonDirObjs} \$(LDFLAGS) \$(GLDFLAGS)

all:debug

clean:
<TAB>for dir in \$(DIRS); do <SLASH>
<TAB><TAB>\$(MAKE) clean -C <DD>dir; <SLASH>
<TAB>done
<TAB>\$(RM) -f *.o ${cModleName}
EOF
            else
# not need build bin file
                cat > ${dir}/Makefile <<EOF
# @desc makefile for ${cModleName}
# @author viticm<viticm.ti@gmail.com>
# @date `date +"%Y-%m-%d %H:%M:%S"`
include ${cInlude}

CFLAGS =
LDFLAGS =
DIRS = ${Arr_SonDir}

OBJS =  `echo -e "${Arr_Objs}"`

debug:\$(OBJS)
<TAB>for dir in \$(DIRS); do <SLASH>
<TAB><TAB>\$(MAKE) debug -C <DD>dir; <SLASH>
<TAB>done

release:\$(OBJS)
<TAB>for dir in \$(DIRS); do <SLASH>
<TAB><TAB>\$(MAKE) release -C <DD>dir; <SLASH>
<TAB>done

all:debug

clean:
<TAB>\$(RM) -f *.o
EOF
            fi
            replaceSpecialWords ${dir}/Makefile
        fi
    done
}
main #do main function
