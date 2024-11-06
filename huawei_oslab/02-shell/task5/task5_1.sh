#!/bin/bash
read file
#请添加此处代码，使用sort测试文件是否排序过，并根据输出结果进行判断

if [ $? -eq 0 ]; then 
	echo "Sorted" ;
else
	echo "Unsorted";
fi
