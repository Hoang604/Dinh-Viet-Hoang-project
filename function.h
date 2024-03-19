#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <mysql/mysql.h>
#include "type.h"
#include "std_string.h"
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
void modify(int id, student_list*);
// delete student in the list base on ID
void deletion(int id, student_list* list);
void display_all_student_in_the_list(student_list);
void display_all_student_in_the_database();
// stop console
void pause();
// print number of student in list
void number_of_student(student_list* list);
// my safer scanf
int my_scanf(const char*, void*);
void display(student_list* list);
int read_from_mysql(student_list*, int);
int write_to_mysql(student_list*);
void delete_from_mysql(int);
int find_from_mysql(int, student_list*);
int exit();
void case_1(student_list* list);
void case_2_3(int decision, student_list* list);
void case_4_5(int decision, student_list* list);
void case_6_7(int decision, student_list* list);
void case_8_9(int decision, student_list* list);
void case_10(student_list* list);
void case_11(student_list* list);
void case_12_13(int decision, student_list* list);
int my_scanf(const char* format, void* output) {
	char buffer[100];
	if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
		printf("Error occured when read from the key board.\n");
		return 0;
	}
	if (sscanf(buffer, format, output) != 1) {
		printf("Error occured when converting data.\n");
		return 0;
	}
	return 1;
}
void initialize_student_list(student_list* list, int initial_capacity) {
	list->arr = (student*)malloc(initial_capacity * sizeof(student));
	list->capacity = initial_capacity;
	list->size = 0;
}
int add_student_to_student_list(student_list* list, student new_student) {
	if (list->size == list->capacity) {
		list->capacity *= 2;
		list->arr = (student*)realloc(list->arr, list->capacity * sizeof(student));
	}
	student_list temp_list;
	initialize_student_list(&temp_list, 1);
	if (find_from_mysql(new_student.id, &temp_list)) {
		printf("The student with id %d is already exist in the school database.\n", new_student.id);
		return 0;
	}
	int k = list->size;
	for (int i = 0; i < k; i++) {
		if (new_student.id == list->arr[i].id) {
			printf("The student with id %d is already exist in the student list.\n", new_student.id);
			return 0;
		}
	}
	list->arr[list->size] = new_student;
	list->size++;
	return 1;
}
void free_student_list(student_list* list) {
	free(list->arr);
	list->arr = NULL;
	free(list);
}
void initialize_student(student* s, int id, const char* name, float math, float lit, float eng, float phys, float ch, float bio, float his, float geo, float cs) {
	strcpy(s->full_name, name);
	s->id = id;
	s->grades[0] = math;
	s->grades[1] = lit;
	s->grades[2] = eng;
	s->grades[3] = phys;
	s->grades[4] = ch;
	s->grades[5] = bio;
	s->grades[6] = his;
	s->grades[7] = geo;
	s->grades[8] = cs;
	s->avg_grade = avg_grade(s);
}
void display_infor_of_student(student s) {
	printf("ID: %d\n", s.id);
	printf("Name: %s\n", s.full_name);
	char subjects[9][17] = { "Math", "Literature", "English", "Physics", "Chemistry", "Biology", "History", "Geography", "Computer Science" };
	printf("Subjects  ");
	for (int i = 0; i < 9; i++) {
		printf("%-12s", subjects[i]);
	}
	printf("  Average Grade");
	printf("\nGrades    ");
	for (int i = 0; i < 9; i++) {
		printf("%-12.2f", s.grades[i]);
	}
	printf("      %.2f", s.avg_grade);
	printf("\n");
}
float avg_grade(student* s) {
	float sum;
	int n = sizeof(s->grades) / sizeof(float);
	for (int i = 0; i < n; i++) {
		sum = sum + s->grades[i];
	}
	float grade = sum / n;
	return grade;
}
void avg_grade2(student_list* list) {
	student s;
	float k;
	int n = list->size;
	int m = sizeof(s.grades) / sizeof(float);
	for (int i = 0; i < m; i++) {
		k = 0;
		for (int j = 0; j < n; j++) {
			k += list->arr[j].grades[i];
		}
		s.grades[i] = k / n;
	}
	k = 0;
	for (int i = 0; i < n; i++) {
		k += list->arr[i].avg_grade;
	}
	s.avg_grade = k / n;
	puts(" ___________________________________________________________________________________________");
	puts("|  Math  |  Lit.  |  Eng.  | Physic |  Che.  |  Bio.  |  His.  |  Geo.  |Comp. Sci.|   Avg  |");
	puts("|________|________|________|________|________|________|________|________|__________|________|");
	for (int j = 0; j < m - 1; j++) {
		printf("|  %-5.2f ", s.grades[j]);
	}
	printf("|   %-5.2f  ", s.grades[m - 1]);
	printf("|  %.2f  |", s.avg_grade);
	printf("\n");
	puts("|________|________|________|________|________|________|________|________|__________|________|");
	pause();
}
void avg_grade_in_list(student_list* list) {
	if (list->size == 0) {
		puts("Students list is empty.");
		return;
	}
	puts("Average grade of all students in the list: ");
	avg_grade2(list);
}
void avg_grade_in_database() {
	student_list* list = (student_list*)malloc(sizeof(student_list));
	initialize_student_list(list, 10);
	read_from_mysql(list, 0);
	if (list->size == 0) {
		puts("Students list is empty.");
		return;
	}
	puts("Average grade of all students in the school database: ");
	avg_grade2(list);
}
void find(int id, student_list* list) {
	int n = list->size;
	for (int i = 0; i < n; i++) {
		if (list->arr[i].id = id) {
			display_infor_of_student(list->arr[i]);
			return;
		}
	}
	printf("There are no student with id %d in the student list.", id);
}
void modify(int id, student_list* list) {
	int n = list->size;
	for (int i = 0; i < n; i++) {
		if (list->arr[i].id == id) {
			char subjects[9][17] = { "Math", "Literature", "English", "Physics", "Chemistry", "Biology", "History", "Geography", "Computer Science" };
			int num;
			do {
				printf("\nStudent information:\n");
				display_infor_of_student(list->arr[i]);
				printf("\t\t----SELECT INFORMATION TO MODIFY----\n");
				printf("1. ID\n2. Full name\n");
				for (int j = 0; j < 9; j++) {
					printf("%d. %s grade\n", j + 3, subjects[j]);
				}
				printf("0.Exit\n");
				printf("Your selection is: ");
				while (!my_scanf("%d", &num)) {
					printf("Please enter an integer.\n");
				}
				if (num == 1) {
					printf("Enter new ID: ");
					while (!my_scanf("%d", &(list->arr[i].id))) {
						printf("Please enter an integer.\n");
					}
				}
				else if (num == 2) {
					printf("Enter new full name: ");
					fgets(list->arr[i].full_name, 24, stdin);
					fix_string(list->arr[i].full_name);
				}
				else if (num >= 3 && num <= 11) {
					printf("Enter new grade for %s: ", subjects[num - 3]);
					while (!my_scanf("%f", &(list->arr[i].grades[num - 3]))) {
						printf("Please enter an integer.\n");
					}
				}
				else if (num == 0) {
					printf("Exit successfully.");
					break;
				}
				else {
					printf("Invalid input. Enter again.");
					continue;
				}
			} while (num);
			list->arr[i].avg_grade = avg_grade(&(list->arr[i]));
			return;
		}
	}
	printf("There are no student with ID %d in the school.\n", id);
	pause();
}
void deletion(int id, student_list* list) {
	int n = list->size;
	for (int i = 0; i < n; i++) {
		if (list->arr[i].id == id) {
			if (i < n - 1) {
				list->arr[i] = list->arr[n - 1];
			}
			list->size--;
			printf("Remove student %d suceccfully.\n", id);
			return;
		}
	}
	printf("There are no student with id %d in the school.\n", id);
}
void case_1(student_list* list) {
	char full_name[24];
	int id;
	float grade[9];
	char subjects[9][17] = { "Math", "Literature", "English", "Physics", "Chemistry", "Biology", "History", "Geography", "Computer Science" };
	char verify; // for verify if the entered grade is valid?
	student s;
	do {
		printf("Enter ID: ");
		while (!my_scanf("%d", &id)) {
			printf("Please enter an integer.\n");
		}
		printf("Enter full name: ");
		fgets(full_name, 24, stdin);
		fix_string(full_name);
		int n = sizeof(grade) / sizeof(float);
		for (int i = 0; i < n; i++) {
			printf("Enter grade for %s: ", subjects[i]);
			while (!my_scanf("%f", &grade[i])) {
				printf("Please enter an integer.\n");
			}
			if (grade[i] > 10 || grade[i] < 0) {
				printf("Grade must be greater than or equal 0 and less than or equal to 10. Enter again.\n");
				i--;
			}
		}
		initialize_student(&s, id, full_name, grade[0], grade[1], grade[2], grade[3], grade[4], grade[5], grade[6], grade[7], grade[8]);
		printf("Student information:\n");
		display_infor_of_student(s);
		do {
			printf("\n\nVerify if the data is correct? (Y/N): ");
			my_scanf("%c", &verify);
			if (verify != 'y' && verify != 'Y' && verify != 'n' && verify != 'N')
				printf("\nInvalid command!");
		} while (verify != 'y' && verify != 'Y' && verify != 'n' && verify != 'N');

	} while (verify == 'N' || verify == 'n');
	initialize_student(&s, id, full_name, grade[0], grade[1], grade[2], grade[3], grade[4], grade[5], grade[6], grade[7], grade[8]);
	int x = add_student_to_student_list(list, s);
	if (x)
		printf("\nStudent with ID %d was added to the list.\n", s.id);
	pause();
}
int read_from_mysql(student_list* list, int size) {
	MYSQL* conn;
	MYSQL_RES* result;
	MYSQL_ROW row;

	conn = mysql_init(NULL);
	if (conn == NULL) {
		fprintf(stderr, "mysql_init() failed\n");
		return 0;
	}
	if (mysql_real_connect(conn, "localhost", "Hoang", "Hoangdeptry_05", "student", 0, NULL, 0) == NULL) {
		fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
		mysql_close(conn);
		return 0;
	}
	if (mysql_query(conn, "select student.id, fullname, math, literature, english, physic, chemistry, biology, history, geography, computer_science, avg_grade from student, grades where student.id = grades.id")) {
		fprintf(stderr, "mysql_query failed: %s\n", mysql_error(conn));
		mysql_close(conn);
		return 0;
	}
	result = mysql_use_result(conn);
	int num_fields = mysql_num_fields(result);
	if (result == NULL) {
		fprintf(stderr, "mysql_use_result() failed: %s\n", mysql_error(conn));
		mysql_close(conn);
		return 0;
	}
	student s;
	char a[30];
	while ((row = mysql_fetch_row(result)) != NULL) {
		int i = 0;
		while (i < num_fields) {
			strcpy(a, row[i]);
			if (i == 0) {
				sscanf(a, "%d", &s.id);
			}
			else if (i == 1) {
				strcpy(s.full_name, a);
			}
			else if (2 <= i && i <= 10) {
				sscanf(a, "%f", &s.grades[i - 2]);
			}
			else {
				sscanf(a, "%f", &s.avg_grade);
			}
			i++;
		}
		if (list->size == list->capacity) {
			list->capacity *= 2;
			list->arr = (student*)realloc(list->arr, list->capacity * sizeof(student));
		}
		int label = 1;
		for (int i = 0; i < size; i++) {
			if (s.id == list->arr[i].id) {
				label = 0;
				break;
			}
		}
		if (label == 1) {
			list->arr[list->size] = s;
			list->size++;
		}
	}
	mysql_close(conn);
	return 1;
}
int count() {
	MYSQL* conn;
	MYSQL_RES* result;
	MYSQL_ROW row;

	conn = mysql_init(NULL);
	if (conn == NULL) {
		fprintf(stderr, "mysql_init() failed\n");
		return 0;
	}
	if (mysql_real_connect(conn, "localhost", "Hoang", "Hoangdeptry_05", "student", 0, NULL, 0) == NULL) {
		fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
		mysql_close(conn);
		return 0;
	}
	if (mysql_query(conn, "SELECT COUNT(*) FROM student")) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		mysql_close(conn);
		return 0;
	}
	int number_of_record;
	MYSQL_RES* res;
	res = mysql_use_result(conn);
	row = mysql_fetch_row(res);
	number_of_record = atoi(row[0]);
	mysql_close(conn);
	return number_of_record;
}
int find_from_mysql(int id, student_list* list) {
	MYSQL* conn;
	MYSQL_RES* result;
	MYSQL_ROW row;

	conn = mysql_init(NULL);
	if (conn == NULL) {
		fprintf(stderr, "mysql_init() failed\n");
		return 0;
	}
	if (mysql_real_connect(conn, "localhost", "Hoang", "Hoangdeptry_05", "student", 0, NULL, 0) == NULL) {
		fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
		mysql_close(conn);
		return 0;
	}
	char* query = (char*)malloc(sizeof(char) * 300);
	strcpy(query, "select student.id, fullname, math, literature, english, physic, chemistry, biology, history, geography, computer_science, avg_grade from student, grades where student.id = grades.id and student.id = ");
	char str[10];
	sprintf(str, "%d", id);
	strcat(query, str);
	if (mysql_query(conn, query)) {
		fprintf(stderr, "mysql_query failed: %s\n", mysql_error(conn));
		mysql_close(conn);
		return 0;
	}
	result = mysql_use_result(conn);
	int num_fields = mysql_num_fields(result);
	student s;
	char a[30];
	if ((row = mysql_fetch_row(result)) != NULL) {
		int i = 0;
		while (i < num_fields) {
			strcpy(a, row[i]);
			if (i == 0) {
				sscanf(a, "%d", &s.id);
			}
			else if (i == 1) {
				strcpy(s.full_name, a);
			}
			else if (2 <= i && i <= 10) {
				sscanf(a, "%f", &s.grades[i - 2]);
			}
			else {
				sscanf(a, "%f", &s.avg_grade);
			}
			i++;
		}
		list->arr[0] = s;
		list->size++;
		return 1;
	}
	return 0;
}
int write_to_mysql(student_list* list) {
	if (list->size == 0) {
		printf("There are no student in the student list.\n");
		return 0;
	}
	MYSQL* conn;
	conn = mysql_init(NULL);
	if (conn == NULL) {
		fprintf(stderr, "mysql_init() failed\n");
		return 0;
	}
	if (mysql_real_connect(conn, "localhost", "Hoang", "Hoangdeptry_05", "student", 0, NULL, 0) == NULL) {
		fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
		mysql_close(conn);
		return 0;
	}
	char* query = (char*)malloc(sizeof(char) * 2000);
	int num = list->size;
	int num_fields = 2;
	strcpy(query, "insert ignore into student(id, fullname) value ");
	for (int i = 0; i < num; i++) {
		sprintf(query + strlen(query), "(%d, '%s')", list->arr[i].id, list->arr[i].full_name);
		if (i < num - 1) strcat(query, ", ");
	}
	if (mysql_query(conn, query)) {
		fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
		free(query);
		mysql_close(conn);
		return 0;
	}
	num_fields = 11;
	strcpy(query, "insert ignore into grades(id, math, literature, english, physic, chemistry, biology, history, geography, computer_science, avg_grade) value ");
	for (int i = 0; i < num; i++) {
		sprintf(query + strlen(query), "(%d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f)", list->arr[i].id, list->arr[i].grades[0], list->arr[i].grades[1], list->arr[i].grades[2], list->arr[i].grades[3], list->arr[i].grades[4], list->arr[i].grades[5], list->arr[i].grades[6], list->arr[i].grades[7], list->arr[i].grades[8], list->arr[i].avg_grade);
		if (i < num - 1) strcat(query, ", ");
	}
	if (mysql_query(conn, query)) {
		fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
		free(query);
		mysql_close(conn);
		return 0;
	}
	mysql_close(conn);
	free_student_list(list);
	list = (student_list*)malloc(sizeof(student_list));
	initialize_student_list(list, 10);
	return 1;
}
void delete_from_mysql(int id) {
	MYSQL* conn;
	conn = mysql_init(NULL);
	if (conn == NULL) {
		fprintf(stderr, "mysql_init() failed\n");
		return;
	}
	if (mysql_real_connect(conn, "localhost", "Hoang", "Hoangdeptry_05", "student", 0, NULL, 0) == NULL) {
		fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
		mysql_close(conn);
		return;
	}
	char query[100];
	char str[100];
	strcpy(query, "delete from student where id = ");
	sprintf(str, "%d;", id);
	strcat(query, str);
	mysql_query(conn, query);
	strcpy(query, "delete from grades where id = ");
	sprintf(str, "%d;", id);
	strcat(query, str);
	mysql_query(conn, query);
	mysql_close(conn);
}
void display(student_list* list) {
	int n = list->size;
	int k = sizeof(list->arr[0].grades) / sizeof(float);
	for (int i = 0; i < n; i++) {
		printf("|%-10d| %-23s", list->arr[i].id, list->arr[i].full_name);
		for (int j = 0; j < k - 1; j++) {
			printf("|  %-5.2f ", list->arr[i].grades[j]);
		}
		printf("|   %-5.2f  ", list->arr[i].grades[k - 1]);
		printf("|  %.2f  |", list->arr[i].avg_grade);
		printf("\n");
	}
}
void display_all_student_in_the_list(student_list list) {
	int n = list.size;
	puts(" _______________________________________________________________________________________________________________________________");
	puts("|         Identification            |                                         Grades                                            |");
	puts("|___________________________________|___________________________________________________________________________________________|");
	puts("|    ID    |       Full name        |  Math  |  Lit.  |  Eng.  | Physic |  Che.  |  Bio.  |  His.  |  Geo.  |Comp. Sci.|   Avg  |");
	puts("|__________|________________________|________|________|________|________|________|________|________|________|__________|________|");
	display(&list);
	puts("|__________|________________________|________|________|________|________|________|________|________|________|__________|________|");
}
void display_all_student_in_the_database() {
	student_list* list = (student_list*)malloc(sizeof(student_list));
	initialize_student_list(list, 100);
	read_from_mysql(list, 0);
	if (list->size == 0) {
		printf("Database empty!\n");
	}
	display_all_student_in_the_list(*list);
	free_student_list(list);
}
void number_of_student(student_list* list) {
	printf("Number of student in the student list: %d\n", list->size);
	pause();
}
void pause() {
	printf("Press Enter to continue ........");
	char x = getchar();
	if (x != '\n') {
		my_scanf("%c", &x);
	}
}
void case_2_3(int selection, student_list* list) {
	int id;
	printf("\nEnter the ID of the student whose information needs to be modified: ");
	while (!my_scanf("%d", &id)) {
		printf("Please enter an integer.\n");
	}

	if (selection == 2)
		modify(id, list);
	else {
		student_list* temp_list = (student_list*)malloc(sizeof(student_list));
		initialize_student_list(temp_list, 1);
		find_from_mysql(id, temp_list);
		modify(id, temp_list);
		delete_from_mysql(id);
		write_to_mysql(temp_list);
		free_student_list(temp_list);
	}
}
void case_4_5(int selection, student_list* list) {
	if (selection == 4) {
		if (list->size == 0) {
			printf("Students list is empty.\n\n");
			pause();
			return;
		}
		printf("\n\n                                                ========LIST OF STUDENT=========\n\n");
		display_all_student_in_the_list(*list);
	}
	else {
		printf("\n\n                                                ========LIST OF STUDENT=========\n\n");
		display_all_student_in_the_database();
	}
	printf("\n");
	pause();
}
void case_6_7(int selection, student_list* list) {
	int id;
	printf("\nEnter the ID of the student who you want to find: ");
	while (!my_scanf("%d", &id)) {
		printf("Please enter an integer.\n");
	}

	student s;
	int in = 0;
	if (selection == 6) {
		find(id, list);
	}
	else {
		student_list* temp_list = (student_list*)malloc(sizeof(student_list));
		initialize_student_list(temp_list, 1);
		if (find_from_mysql(id, temp_list)) {
			display_all_student_in_the_list(*temp_list);
		}
		else {
			printf("\nThere are no student with ID %d in the school database.\n", id);
		}
		free_student_list(temp_list);
	}
	pause();
}
void case_8_9(int selection, student_list* list) {
	int id;
	printf("\nEnter the ID of the student who you want to remove: ");
	while (!my_scanf("%d", &id)) {
		printf("Please enter an integer.\n");
	}
	if (selection == 8) {
		deletion(id, list);
	}
	else {
		delete_from_mysql(id);
	}
	pause();
}
void case_10(student_list* list) {
	if (write_to_mysql(list) == 1) {
		printf("Write data to database successfuly.\n");
	}
	else {
		printf("Failed to write data to the database. An error has occured\n");
	}
	pause();
}
void case_11(student_list* list) {
	if (read_from_mysql(list, list->size) == 1) {
		printf("Retrieve data from database successfuly.\n");
	}
	else {
		printf("Failed to retrieve data from the database. An error has occured");
	}
	pause();
}
void case_12_13(int selection, student_list* list) {
	if (selection == 13) {
		number_of_student(list);
	}
	else {
		printf("Number of student in the school database: %d\n", count());
		pause();
	}
}
int exit() {
	char decision;
	do {
		printf("Are you sure you want to exit the menu option? (Y/N)  ");
		my_scanf("%c", &decision);
		if (decision == 'y' || decision == 'Y' || decision == 'n' || decision == 'N') {
			break;
		}
		else {
			printf("Invalid choice. Please enter a valid option\n");
			continue;
		}
	} while (1);
	if (decision == 'y' || decision == 'Y') {
		return 1;
	}
	else {
		return -1;
	}
}
