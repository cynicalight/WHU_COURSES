// main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

void showMenu()
{
	printf("\n\tStudents Info Management Sys. (Demo)\n\n");
	printf("\t1. Add a record\n");
	printf("\t2. Delete a record\n");
	printf("\t3. Update a record\n");
	printf("\t4. Query a record\n");
	printf("\t5. List all\n");
	printf("\t6. Sort for all records\n");
	printf("\t7. Save to file\n");
	printf("\t8. Read from file\n");
	printf("\t9. Show this menu\n");
	printf("\t0. Exit\n");
}

int main()
{
	Student_T stu[MAX_NUM];
	memset(stu, 0, sizeof(stu));
	
	// Test......
	printf("\n");
	printf("sizeof int: %lu\n", sizeof(int));
	printf("sizeof stu, stu[0]: %lu, %lu\n", sizeof(stu), sizeof(stu[0]));
	
	showMenu();
	
	unsigned int id = 0;
	char name[64] = {'\0'};
	
	for(;;) {
		printf("\nPlease select: ");
		
		int select = 0;
		scanf("%d", &select);
		switch(select) {
		case 1:
			if (addRecord(stu) != 0)
				printf("addRecord() error\n");
			break;
		case 2:
			printf("ID = ");
			scanf("%u", &id);
			if (delRecordByID(stu, id) != 0)
				printf("delRecordByID() error\n");
			break;
		case 3:
			printf("ID = ");
			scanf("%u", &id);
			if (updateRecordByID(stu, id) != 0)
				printf("updateRecordByID() error\n");
			break;
		case 4:
			printf("The name is: ");
			scanf("%s", name);
			if (queryRecordByName(stu, name) != 0)
				printf("queryRecordByName() error\n");
			break;
		case 5:
			if (list(stu) != 0)
				printf("sort() error\n");
			break;
		case 6:
			if (sortByID(stu) != 0)
				printf("sort() error\n");
			break;
		case 7:
			if (saveToFile("students.dat", stu) != 0)
				printf("saveToFile() error\n");
			break;
		case 8:
			if (readFromFile(stu, "students.dat") != 0)
				printf("readFromFile() error\n");
			break;
		case 9:
			showMenu();
			break;
		case 0:
			printf("Quit\n");
			quit(0);
			break;
		default:
			printf("Please input number 1~9 or 0 to quit.\n");
		}
	}

	return 0;
}
