// student.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

int addRecord(Student_T stu[])
{
	if (stu == NULL){
		printf("Invalid argument!\n");
        return -1;
	}
	
	int index = 0;
	
	for (int i=0; i<MAX_NUM; i++) {
		if (stu[i].id == 0) {
			index = i;
			break;
		}
	}
	
	printf("Line %d: Please input a record by the format shown below:\n\n", index);
	printf("#ID\tName\tSex\tBirthday\tBirthplace\tClassID\n\n");
	printf("For example:\n\n");
	printf("110001 Dinu F 1992/12/25 Gaya 20161230\n\n");
	
	scanf(ITEM_FORMAT_SCAN,
	     &stu[index].id,
		 stu[index].name,
		 &stu[index].sex,
		 &stu[index].birthday.year,
		 &stu[index].birthday.month,
		 &stu[index].birthday.day,
		 stu[index].birthplace,
		 &stu[index].classID
		 );
		 
	if (stu[index].id == 0) {
		printf("The ID cannot be zero!\n");
		return -1;
	}
		 
	printf(ITEM_FORMAT_PRINT,
	      stu[index].id,
		  stu[index].name,
		  stu[index].sex,
		  stu[index].birthday.year,
		  stu[index].birthday.month,
		  stu[index].birthday.day,
		  stu[index].birthplace,
		  stu[index].classID
		  );
		  
	printf("This record has been added to line %d\n", index);
	return 0;
}

int delRecordByID(Student_T stu[], unsigned int id)
{
	if (stu == NULL || id == 0){
		printf("Invalid argument!\n");
        return -1;
	}
	
	int done = 0;
	for (int i=0; i<MAX_NUM; i++) {
		if (stu[i].id == id) {
			//请增加代码，使用memset函数删除学生记录

			printf("sizeof stu[%d] is %lu\n", i, sizeof(stu[i]));
			done = 1;
			break;
		}
	}
	
	if (!done) {
		printf("Cannot find the record by #ID: %u\n", id);
	}
	
	return 0;
}

int updateRecordByID(Student_T stu[], unsigned int id)
{
	if (stu == NULL || id == 0){
		printf("Invalid argument!\n");
        return -1;
	}
	
	int index = 0;
	int done = 0;
	for (int i=0; i<MAX_NUM; i++) {
		if (stu[i].id == id) {
			index = i;
			printf("Line %d:\n", index);
			printf("#ID\tName\tSex\tBirthday\tBirthplace\tClassID\n\n");
			printf(ITEM_FORMAT_PRINT,
				  stu[index].id,
				  stu[index].name,
				  stu[index].sex,
				  stu[index].birthday.year,
				  stu[index].birthday.month,
				  stu[index].birthday.day,
				  stu[index].birthplace,
				  stu[index].classID
				  );
			printf("Please input new values(except ID):\n");
			
			scanf(ITEM_FORMAT_SCAN2,
				 stu[index].name,
				 &stu[index].sex,
				 &stu[index].birthday.year,
				 &stu[index].birthday.month,
				 &stu[index].birthday.day,
				 stu[index].birthplace,
				 &stu[index].classID
				 );
				 
			printf(ITEM_FORMAT_PRINT,
				  stu[index].id,
				  stu[index].name,
				  stu[index].sex,
				  stu[index].birthday.year,
				  stu[index].birthday.month,
				  stu[index].birthday.day,
				  stu[index].birthplace,
				  stu[index].classID
				  );
				  
			printf("Line %d has been updated\n", index);
			done = 1;
			break;
		}
	}
	
	if (!done) {
		printf("Cannot find the record by #%u\n", id);
		return -1;
	}
	
	return 0;
}

int queryRecordByName(Student_T stu[], char * name)
{
	if (stu == NULL || name == NULL){
		printf("Invalid argument!\n");
        return -1;
	}
	
	int index = 0;
	int done = 0;
	for (int i=0; i<MAX_NUM; i++) {
		//请增加代码，使用strcmp函数对name字段实现字符串匹配
		if (strcmp(...) == 0) {
			index = i;
			printf(ITEM_FORMAT_PRINT,
				  stu[index].id,
				  stu[index].name,
				  stu[index].sex,
				  stu[index].birthday.year,
				  stu[index].birthday.month,
				  stu[index].birthday.day,
				  stu[index].birthplace,
				  stu[index].classID
				  );
			done = 1;
		}
	}
	
	if (!done) {
		printf("Cannot find the record by name: %s\n", name);
	}
	
	return 0;
}

int list(Student_T stu[])
{
	int n = 0;
	
	if (stu == NULL){
		printf("Invalid argument!\n");
        return -1;
	}
	
	for (int i = 0; i < MAX_NUM; i++) {
		if (stu[i].id != 0) {
			printf(ITEM_FORMAT_PRINT,
				  stu[i].id,
				  stu[i].name,
				  stu[i].sex,
				  stu[i].birthday.year,
				  stu[i].birthday.month,
				  stu[i].birthday.day,
				  stu[i].birthplace,
				  stu[i].classID
				  );
			++n;
		}
	}
	
	if (n == 0) {
		printf("The list is empty!\n");
	}
	
	return 0;
}

int sortByID(Student_T stu[])
{
	if (stu == NULL){
		printf("Invalid argument!\n");
        return -1;
	}
	
	for (int i = 0; i < MAX_NUM - 1; i++) {
		for (int j = i + 1; j < MAX_NUM; j++) {
			if (stu[j].id == 0) {
				; // do nothing
			}
			else if (stu[i].id > stu[j].id) {
				//请增加代码，根据学生id进行排序中的swap步骤
				
			}
		}
	}
	
	return 0;
}

int saveToFile(char * filename, Student_T stu[])
{
	if (filename == NULL || stu == NULL){
		printf("Invalid argument!\n");
        return -1;
	}
	
	//请增加代码，使用fopen函数打开文件
	FILE *fp = fopen(....);

    if (fp == NULL) {
        printf("Failure to create %s!\n", filename);
        return -2;
    }
	
	for (int i=0; i<MAX_NUM; i++) {
		if (stu[i].id != 0) {
			//请增加代码，使用fwrite函数进行写文件操作
			
		}
	}
    
        fclose(fp);

        printf("The record(s) have/has saved to %s!\n", filename);
	return 0;
}

int readFromFile(Student_T stu[], char * filename)
{
	if (stu == NULL || filename == NULL) {
		printf("Invalid argument!\n");
        return -1;
	}
	
	FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Failure to open %s!\n", filename);
        return -2;
    }
	
	for(int i = 0; !feof(fp); i++) {
        fread(&stu[i], sizeof(Student_T), 1, fp);
    }
	
	fclose(fp);
	return 0;
}

void quit(int error)
{
	return exit(error);
}
