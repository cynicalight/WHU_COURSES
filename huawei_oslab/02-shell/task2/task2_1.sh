#!/bin/bash
for filename in `ls`
do 
	if test -d $filename 
	then b=0
	else
	#请补充一下代码，使用awk命令打印指定内容
		a=$(ls -l $filename |    '{ print $5 }')
			#请补充一下代码,判断文件a大小是否等于0
			if 
			#请补充一下代码,使用rm命令删除文件
				then 
			fi
	fi
done