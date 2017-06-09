#!/bin/bash

filepath="./results/voice_result.mlf"
writefilepath="./results/result"

if [ ! -f "$filepath" ]; then
 echo "结果文件不存在!"
 exit 0
fi

if [ ! -f "$writefilepath" ]; then
 touch $writefilepath
 echo "创建文件成功!"
fi
 
#清空文件
: > $writefilepath

cat $filepath | while read -r line a b c d
do
 echo -n "$b" >> $writefilepath 
done

echo "finished"


exit 0
