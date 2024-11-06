#!/usr/bin/env bash
echo > out.log
while true 
do
				./random.sh >> out.log
				if [[ $? -ne 0 ]]; then
								cat out.log
								echo "fail after $count times"
								break
				fi
				((count++))

done
