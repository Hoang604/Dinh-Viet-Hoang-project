#ifndef FUNCTION_H
#define FUNCTION_H

#include "type.h"
void initialize_student_list(student_list* list, int initial_capacity);
void free_student_list(student_list* list);
void initialize_student(student*, int, const char*, float, float, float, float, float, float, float, float, float);
void display_infor_of_student(student);
// average grade for a student s
float avg_grade(student* s);
// average grade for all students in the student list
void avg_grade2(student_list* list);
void avg_grade_in_list(student_list* list);
// average grade for all students in the school database
void avg_grade_in_database();
// add a student to the student list
int add_student_to_student_list(student_list* list, student new_student);
// find student base on ID
void find(int id, student_list* list);
// modify student base on ID
int modify(int id, student_list*);
// delete student in the list base on ID
void deletion(int id, student_list* list);
void display_all_student_in_the_list(student_list* list);
void display_all_student_in_the_database();
// stop console
void pause();
// print number of student in list
void number_of_student(student_list* list);
// my safer scanf
int my_scanf(const char*, void*);
void display(student_list* list);
int read_from_mysql(student_list* list, int list_size);
int write_to_mysql(student_list* list);
void delete_from_mysql(int id);
int find_from_mysql(int id, student_list*);
int exit_();
void case_1(student_list* list);
void case_2_3(int decision, student_list* list);
void case_4_5(int decision, student_list* list);
void case_6_7(int decision, student_list* list);
void case_8_9(int decision, student_list* list);
void case_10(student_list* list);
void case_11(student_list* list);
void case_12_13(int decision, student_list* list);
#endif

