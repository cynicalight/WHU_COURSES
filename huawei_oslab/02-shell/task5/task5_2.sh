#!/bin/bash
echo "Please enter a user:"
read a
#请添加此处代码，使用whoami指令测试用户是否在运行
b=
if test $a = $b
then echo "the user is running."
else echo "the user is not running."
fi
