#!/bin/bash
cBaseDir=`pwd` # default use cur dir, you can define it
Arr_BinDir="Billing Server Login World ShareMemory"
Arr_ModelName="Billing Server Login World ShareMemory Common"
Arr_ModelIncludeNeedCompile=(
    "Common/Assertx.cpp Common/Net/*.cpp Server/Base/Log.cpp Server/Base/TimeManager.cpp Server/Base/LogDefine.cpp
    Server/Base/Config.cpp Server/Base/Thread.cpp Server/Base/Ini.cpp Common/GameUtil.cpp Common/PacketFactoryManager.cpp 
    Common/Packets/LBAskAuth.cpp Common/Packets/BWConnect.cpp Common/Packets/BLRetAuth.cpp
    " #Billing
    ""
    ""
    ""
    "Common/Assertx.cpp Common/Net/*.cpp Common/GameUtil.cpp Server/Base/Log.cpp Server/Base/TimeManager.cpp Server/Base/LogDefine.cpp
    Common/ShareMemAPI.cpp Common/DBSystem/DataBase/*
    Server/Base/Config.cpp Server/Base/Thread.cpp Server/Base/Ini.cpp Server/Base/Log.cpp Server/Base/TimeManager.cpp
    Server/Base/LogDefine.cpp Server/SMU/ShareMemAO.cpp
    " #ShareMemory
)
Arr_NotMakeFile="`pwd`"
Arr_Dir=`find ${cBaseDir} -type d`
cInludeFile=premake
iSystemBit=`getconf LONG_BIT`

#@desc get include premake file by path
#@param string cPath
#@return string
function getIncludeFile()
{
    local cPath=${1}
    local iDepth=`echo ${cPath} | sed "s;${cBaseDir};;g" | awk -F '/' '{print NF}'`
    local cInludePath=""
    for (( i=1;i<${iDepth};i++ ))
    do
        cInludePath+="../"
    done
    echo ${cInludePath}${cInludeFile}.mk
}

#@desc get first position form array by val
#@param array Arr_Haystack
#@param mixed mNeedle
#@return void
function arrayPos()
{
    local Arr_Haystack=${1}
    local mNeedle=${2}
    local iIndex=0
    for val in ${Arr_Haystack}
    do
        if [[ ${mNeedle} == ${val} ]] ; then
            break
        fi
        ((iIndex+=1))
    done
    echo ${iIndex}
}
#@desc get include need compile objs by modele index
#@param array Arr_IncludeFile
#@return void
function getIncludeNeedCompileObjs()
{
#    local iModelIndex=${1}
#    local Arr_ModelIncludeNeedCompile=${2}
    local Arr_Objs=""
    local Arr_IncludeFile=${1}  #${Arr_ModelIncludeNeedCompile[${iModelIndex}]}
    for file in ${Arr_IncludeFile}
    do
#        local cFileName=`echo ${file} | awk -F / '{print $NF}'`
#        local cDirName=`echo ${file} | sed "s;${cFileName};;g"`
#        local Arr_SourceFile=`find ${cBaseDir}/${cDirName} -maxdepth 1 -type f -name ${cFileName}`
#        for sourceFile in ${Arr_SourceFile}
#        do
        local cObjName=`echo ${file} | sed 's;\.cpp;\.o;g' | sed 's;\.c;\.o;g'`
        if [[ "" == ${Arr_Objs} ]] ; then
            Arr_Objs+="\$(BASEDIR)/${cObjName}"
        else
            Arr_Objs+=" <SLASH>\n<TAB><TAB>\$(BASEDIR)/${cObjName}"
        fi
#        done
    done
    echo ${Arr_Objs}
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
#<TAB> \t | <S4> "    " | <DD> $$ | <SLASH> \
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

#@desc get self includes from dir
#@param string cModelName
#@param string cCurDirBaseName
#@param string Arr_ModelSonDir
#@return void
function getIncludes()
{
    local cModelName=${1}
    local cCurDirBaseName=${2}
    local Arr_ModelSonDir=${3}
    local cIncludes=""
    for dir in ${Arr_ModelSonDir}
    do
        cIncludes+=" -I\$(BASEDIR)/${cModelName}/${dir}"
    done
    echo ${cIncludes}
}


#@desc main function
#@param void
#@return int
function main()
{
    sed -i "s;-D_FILE_OFFSET_BITS=64;-D_FILE_OFFSET_BITS=${iSystemBit};g" ${cBaseDir}/${cInludeFile}
    for dir in ${Arr_Dir}
    do
        cInlude=`getIncludeFile ${dir} "${Arr_NotMakeFile}"`
        cCurDir=`basename ${dir}`
        cModelName=`getModelName ${dir} "${Arr_ModelName}"`
        Arr_Objs=`getObjs ${dir}`
        Arr_SonDir=`getSonDirs ${dir} 1`
        Arr_ModelSonDir=`getSonDirs ${cBaseDir}/${cModelName}`
        cCFlags=""
        cLdFlags=""
        cCFlags=`getIncludes ${cModelName} ${cCurDir} "${Arr_ModelSonDir}"`
        cCFlags+=" -I\$(BASEDIR)/${cModelName}"
        if [[  "Server" != ${cModelName} ]] ; then
            cCFlags+=" \$(SERVER_BASE_INCLUDES)"
        fi

        if inArray ${dir} "${Arr_NotMakeFile}"
        then :
            echo ${dir} not in make
        else
# get new file Makefile 
            if inArray ${cCurDir} "${Arr_BinDir}"
            then :
# need build bin file
                echo ${cModelName}
                #bin dir not need objs
                Arr_Objs=""
                Arr_IncludeObjs=""
                iModelIndex=`arrayPos "${Arr_ModelName}" ${cModelName}`
                Arr_IncludeObjs=`getIncludeNeedCompileObjs "${Arr_ModelIncludeNeedCompile[${iModelIndex}]}"`
                Arr_Objs+=${Arr_IncludeObjs}
                Arr_SonDirObjs=`getSonDirObjs ${dir}`
                if [[  "Server" != ${cModelName} ]] ; then
                    cCFlags+=" \$(SERVER_BASE_INCLUDES)"
                fi
                if [[ "Server" != ${cModelName} ]] ; then
                    cLdFlags+=" \$(SERVER_BASE_LDS)"
                    cCFlags+=" \$(SERVER_BASE_INCLUDES)"
                fi
                
                if [[ "World" == ${cModelName} || "ShareMemory" == ${cModelName} ]] ; then
                    cCFlags+=" -I\$(BASEDIR)/Server/SMU"
                    cCFlags+=" \$(MYSQL_INCLUDES) "
                fi
                if [[ "ShareMemory" == ${cModelName} ]] ; then
                    cCFlags+=" -I\$(BASEDIR)/Server/Other"
                fi

                cat > ${dir}/Makefile <<EOF
# @desc makefile for ${cModelName}
# @author viticm<viticm.ti@gmail.com>
# @date `date +"%Y-%m-%d %H:%M:%S"`
include ${cInlude}

CFLAGS = ${cCFlags}
debug:LDFLAGS = ${cLdFlags}
release:LDFLAGS = ${cLdFlags}

DIRS = ${Arr_SonDir}
DEBUG_DIRS = ${Arr_SonDir}

OBJS =  `echo -e "${Arr_Objs}"`

debug:\$(OBJS)
<TAB>for dir in \$(DEBUG_DIRS); do <SLASH>
<TAB><TAB>\$(MAKE) debug -C <DD>dir; <SLASH>
<TAB>done
<TAB>\$(CPP) -o ./${cModelName} \$(OBJS) ${Arr_SonDirObjs} \$(LDFLAGS) \$(GLDFLAGS)

release:\$(OBJS)
<TAB>for dir in \$(DIRS); do <SLASH>
<TAB><TAB>\$(MAKE) release -C <DD>dir; <SLASH>
<TAB>done
<TAB>\$(CPP) -o ./${cModelName} \$(OBJS) ${Arr_SonDirObjs} \$(LDFLAGS) \$(GLDFLAGS)

all:debug

clean:
<TAB>for dir in \$(DIRS); do <SLASH>
<TAB><TAB>\$(MAKE) clean -C <DD>dir; <SLASH>
<TAB>done
<TAB>\$(RM) -f \$(OBJS) ${cModelName} 
EOF
            else
# not need build bin file
                if [[ "World" == ${cModelName} || "ShareMemory" == ${cModelName} ]] ; then
                    cCFlags+=" -I\$(BASEDIR)/Server/SMU"
                fi
                if [[ "ShareMemory" == ${cModelName} ]] ; then
                    cCFlags+=" -I\$(BASEDIR)/Server/Other"
                fi
                cat > ${dir}/Makefile <<EOF
# @desc makefile for ${cModelName}
# @author viticm<viticm.ti@gmail.com>
# @date `date +"%Y-%m-%d %H:%M:%S"`
include ${cInlude}

CFLAGS  = ${cCFlags}
LDFLAGS =
DIRS =  ${Arr_SonDir}
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
