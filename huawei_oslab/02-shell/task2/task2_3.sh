#!/bin/bash
echo "Current User is:"
#请补充一下代码，使用awk命令打印指定内容

echo $(ps |grep "$$"|     '{print $2}')