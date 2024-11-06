#!/bin/bash
echo "input a character"
read Keypress
case "$Keypress" in
	#[补充以下代码，利用正则表达式判断是否为小写]
	             echo "Lowercase letter";; 
	[[:upper:]]) echo "Uppercase letter";;

	#[补充以下代码，利用正则表达式判断是否为小写]
	    echo "Digit";;
	* ) echo "Punctuation,whitespace,or other";;
esac
exit 0
