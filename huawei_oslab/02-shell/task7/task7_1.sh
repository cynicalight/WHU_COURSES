#!/bin/bash
#请添加此处代码，使用ifconfig命令完成对IP的获取*/  
    | grep "inet addr:" | awk '{print $2}' |sed 's/addr://g'