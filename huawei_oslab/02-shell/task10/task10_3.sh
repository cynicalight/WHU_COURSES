#!/bin/bash
word=$1
#请添加代码，利用grep指令检测给定的单词是否为词典中的单词。

if [ $? -eq 0 ] ;then
	echo $word is a dictionary word;
else
	echo $word is not a dictionary word;
fi
