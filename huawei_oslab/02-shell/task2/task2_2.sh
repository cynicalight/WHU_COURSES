#!/bin/bash
a=0
for name in *.*
do
    #请补充一下代码，使用awk命令打印指定内容
    b=$(ls -l "$name" |       '{print $5}')
    if [ "$b" -gt "$a" ]; then
        a=$b
        
        #请添加代码，完成对文件最大值的替换
        
    fi
done
echo "the max file is $namemax"