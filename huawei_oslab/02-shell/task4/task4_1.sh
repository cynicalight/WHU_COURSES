#!/bin/bash
result=1
while [ $# -gt 0 ]
do
	result=`expr $result '*' $1`
	#请添加代码，使用shift指令完成向左移动参数
	
done
echo $result