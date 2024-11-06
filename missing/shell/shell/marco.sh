pwd1=$(pwd)
marco(){
				echo $(pwd) > pwd_file.txt
}

polo(){
				cd $(cat ${pwd1}/pwd_file.txt)
}

