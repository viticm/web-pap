#!/bin/bash
Arr_Files=`find ./ -type f | sed 's;\./;;g'`
cDstDir=./iconv/
for file in ${Arr_Files}
do
    cBaseDir=`dirname ${file}`
    mkdir -p ${cDstDir}${cBaseDir}
    cLibGrep=`echo ${file} | grep '.lib'`
    if [[ "" == ${cLibGrep} ]] ; then
        iconv -f GBK -t UTF-8 ${file} > ${cDstDir}${file}
    else
        cp ${file} ${cDstDir}${file}
    fi
done
