#!/bin/sh

myPath="./receivedAudio/receivedAudioFile"
myFile="./receivedAudio/receivedAudioFile/voice.wav"
myResult="./results/voice_result.mlf"

#myFeature = "./receivedAudio/receivedAudioFeature/voice.mfc"

 
# 这里的-x 参数判断$myPath是否存在并且是否具有可执行权限
#if [ ! -x "$myPath"]; then
# mkdir "$myPath"
#fi
# 这里的-d 参数判断$myPath是否存在
if [ ! -d "$myPath" ]; then
 echo "文件存储目录不存在"
 exit 0
fi

# 这里的-f参数判断$myFile是否存在
if [ ! -f "$myFile" ]; then
 echo "文件不存在!"
 exit 0
 #touch "$myFile"
fi
# 其他参数还有-n,-n是判断一个变量是否是否有值
#if [ ! -n "$myVar" ]; then
# echo "$myVar is empty"
# exit 0
#fi 
# 两个变量判断是否相等
#if [ "$var1" = "$var2" ]; then
# echo '$var1 eq $var2'
#else
# echo '$var1 not eq $var2'
#fi

HCopy -T 1 -C config/config0 -S receivedAudio/voice.scp

HVite -H hmms/hmm12/macros -H hmms/hmm12/hmmdefs -S receivedAudio/feature.scp  -l '*' -i results/voice_result.mlf -w wdnet -p 0.0 -s 5.0 dict/dict1 lists/triphones1

if [ ! -f "$myResult" ]; then
 echo "结果文件不存在!"
 exit 0
fi

#打开文件
#gedit "$myResult"
./getString.sh

gcc main.c -o main.out
./main.out

echo "done！"

exit 0
