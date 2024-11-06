#!/bin/bash
echo "No Password User are:"
#请添加此处代码，使用cat命令显示整个文件夹
echo $(     /etc/shadow|grep "!"|awk 'BEGIN {FS=":"} {print $1}')