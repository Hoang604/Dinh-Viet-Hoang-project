#include <stdio.h>
#include "function.h"
int main() {
	printf("WELCOME TO THE STUDENT MANAGEMENT PROGRAM\n\n");
	printf("This program is designed to manage student information.\n\n");
	printf("Maximize the console for the best experience.\n\n");
	int choice;
	do {
		printf("Enter: 1. To initialize a list to store students\n       2. To exit the program\n       ---->");
		my_scanf("%d", &choice);
	} while (choice != 1 && choice != 2);
	if (choice == 2) {
		printf("Exit program successfully.");
		return 0;
	}
	student_list* list = (student_list*)malloc(sizeof(student_list));
	initialize_student_list(list, 10);
	int selection;
	do {
		printf("===========STUDENT MANAGEMENT PROGRAM===========\n\n");
		printf("1. Add a new student to the student list.\n");
		printf("2. Modify information of an existing student in the student list based on ID.\n");
		printf("3. Modify information of an existing student in the school database based on ID.\n");
		printf("4. Display information of all student in the student list.\n");
		printf("5. Display information of all student from the school database.\n");
		printf("6. Find a student from the student list based on ID.\n");
		printf("7. Find a student from the school database based on ID.\n");
		printf("8. Delete a student from the student list based on ID.\n");
		printf("9. Delete a student from the school database based on ID.\n");
		printf("10. Add all students from the student list to the school database.\n");
		printf("11. Retrieve all students from the school database and add them to the student list.\n");
		puts("12. Display number of student in the student list.");
		puts("13. Display number of student in the school database.");
		puts("14. Average grades of all students in the list.");
		puts("15. Average grades of all students in the school.");
		puts("0. Exit.");
		printf("\nEnter your selection: ");
		while (!my_scanf("%d", &selection)) {
			printf("Please enter an integer.\n");
		}
		if (selection == 1) {
			case_1(list);
		}
		else if (selection == 2 || selection == 3) {
			case_2_3(selection, list);
		}
		else if (selection == 4 || selection == 5) {
			case_4_5(selection, list);
		}
		else if (selection == 6 || selection == 7) {
			case_6_7(selection, list);
		}
		else if (selection == 8 || selection == 9) {
			case_8_9(selection, list);
		}
		else if (selection == 10) {
			case_10(list);
		}
		else if (selection == 11) {
			case_11(list);
		}
		else if (selection == 12 || selection == 13) {
			case_12_13(selection, list);
		}
		else if (selection == 14) {
			avg_grade_in_list(list);
		}
		else if (selection == 15) {
			avg_grade_in_database();
		}
		else if (selection == 0) {
			int e = exit();
			if (e == 1) {
				break;
			}
			selection = e;
			continue;
		}
		else {
			printf("Invalid choice. Please enter a valid option\n\n");
			pause();
		}
	} while (selection);
	printf("Exiting program successfully.\n");
	free_student_list(list);
	return 0;
}