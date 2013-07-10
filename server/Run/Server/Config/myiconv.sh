#!/bin/bash
Arr_Files=`find ./ -type f | sed 's;\./;;g'`
Arr_NotConvetFile=`find ./ -type f -name "*.path" -o -name "*.cpf" -o -name "*.lib" -o -name "*.nav" -o -name "*.stall" -o -name "*.zip" -o -name "*.ObjRegion" | sed 's;\./;;g'`
cDstDir=./iconv/
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
        if [[ ${mCheck} == ${check} ]] ; then
            return 0
        fi
    done
    return 1
}


for file in ${Arr_Files}
do
    cBaseDir=`dirname ${file}`
    mkdir -p ${cDstDir}${cBaseDir}
    if inArray ${file} "${Arr_NotConvetFile}"
    then :
        echo cp ${file} ${cDstDir}${file}
        cp ${file} ${cDstDir}${file}
    else
        echo iconv -f GBK -t UTF-8 ${file} > ${cDstDir}${file}
        iconv -f GBK -t UTF-8 ${file} > ${cDstDir}${file}
    fi
done
