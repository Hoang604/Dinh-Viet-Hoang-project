#include <std_string.h>
bool is_white_space(char x) {
	return x == ' ' || x == '\n' || x == '\t' || x == '\r';
}
int count_word(char* str) {
	int count = 0;
	bool is_in_word = false;
	for (int i = 0; str[i] != '\0'; i++) {
		if (is_white_space(str[i])) {
			is_in_word = false;
		}
		else {
			if (is_in_word == false) {
				count++;
				is_in_word = true;
			}
		}
	}
	return count;
}
void standardized_word(char* str) {
	int n = strlen(str);
	if (str[0] >= 97 && str[0] <= 122) {
		str[0] -= 32;
	}
	for (int i = 1; i < n; i++) {
		if (str[i] <= 90 && str[i] >= 65) {
			str[i] += 32;
		}
	}
}
void remove_first_word(char* str) {
	bool is_word = false;
	int length = strlen(str);
	int j = 0;
	while (is_white_space(str[j]) && j < length) {
		j++;
	}
	while (!is_white_space(str[j]) && j < length) {
		str[j] = ' ';
		j++;
	}
}
void standardized(char* str) {
	int l = strlen(str);
	int count = count_word(str);
	char** std_str = (char**)malloc(count * sizeof(char*));
	for (int i = 0; i < count; i++) {
		std_str[i] = (char*)malloc(10 * sizeof(char));
	}
	for (int i = 0; i < count; i++) {
		sscanf(str, "%10s", std_str[i]);
		remove_first_word(str);
		standardized_word(std_str[i]);
	}
	int j = 0;
	for (int i = 0; i < count; i++) {
		int l = strlen(std_str[i]);
		if (j > 0)str[j] = ' ';
		for (int k = 0; k < l; k++) {
			str[j] = std_str[i][k];
			j++;
		}
		j++;
	}
	str[j - 1] = '\0';
}
void fix_string(char* str) {
	int length = strlen(str);
	standardized(str);
	if (length >= 2) {
		if (str[length - 1] == '\n' && str[length - 2] == '\r') {
			str[length - 2] = '\0';
		}
		else if (str[length - 1] == '\n' && str[length - 2] != '\r') {
			str[length - 1] = '\0';
		}
	}
}