#!/bin/bash
while :
do
	echo "Please input file's name"
	read a
	if test -e $a
	then
		echo "the file is existing Please input a new file"
	else
		#请添加此处代码，使用mkdir命令创建目录
		
		
		echo "you are sussesful!"
		break
	fi
done
