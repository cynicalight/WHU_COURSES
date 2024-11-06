// student.h

#ifndef STUDENTS_H
#define STUDENTS_H

#define MAX_NUM 200
#define ITEM_FORMAT_PRINT "%12u%12s%3c%6d/%02d/%02d%32s%11u\n"
#define ITEM_FORMAT_SCAN "%u %s %c %d/%d/%d %s %u"
#define ITEM_FORMAT_SCAN2 "%s %c %d/%d/%d %s %u"

typedef struct _Date_T {
    int day;
    int month;
    int year;
} Date_T;

typedef struct _Student_T {
	unsigned int id;
	char name[16];
	char sex;
	char placeholder[3]; // for 4 bytes alignment
	Date_T birthday;
	char birthplace[64];
	unsigned int classID;
} Student_T;

int addRecord(Student_T stu[]); // append a record to stu[]
int delRecordByID(Student_T stu[], unsigned int id); // delete a record by ID
int updateRecordByID(Student_T stu[], unsigned int id); // update a record by ID
int queryRecordByName(Student_T stu[], char * name); // query record(s) by name
int list(Student_T stu[]); // list all records
int sortByID(Student_T stu[]);
int saveToFile(char * filename, Student_T stu[]);
int readFromFile(Student_T stu[], char * filename);
void quit(int error);



#endif // STUDENTS_H
