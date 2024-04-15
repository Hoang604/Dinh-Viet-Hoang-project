#ifndef TYPE_H
#define TYPE_H
#include <stdio.h>
typedef struct student {
	char full_name[24];
	int id;
	float grades[9]; // 0.math, 1.literature, 2.english, 3.physic, 4.chemistry, 5.biology, 6.history, 7.geography, 8.computer science 
	float avg_grade;
} student;
typedef struct student_list {
	student* arr;
	int capacity; // capacity of the array
	int size; // number of student 
} student_list;
#endif