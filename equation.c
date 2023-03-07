#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <malloc.h>
#include <regex.h>


long double validation(char name){
  int valid = 0;
	long double result = 0;

	do {
  printf("%c = ", name);

//dynamic string
  char *str, c=0;
  int i = 0, j = 1;
  str = (char*)malloc(sizeof(char));
  while (c != '\n') {
    c = getc(stdin);
    str = (char*)realloc(str, j * sizeof(char));
    str[i] = c;
    i++;
    j++;
  }

  str[i-1] = '\0'; // \0 isted of \n to mark end of string

	//validate input with regex
	regex_t regex;
	int reti = regcomp(&regex, "^-?[0-9]+(.[0-9])?[0-9]*$", REG_EXTENDED);
		reti = regexec(&regex, str, 0, NULL, 0);
					if (reti) {
							printf("Error. Expected a valid real number, got %s instead\n", str);
							regfree(&regex);
							free(str);
							continue;
					}
	regfree(&regex);

	sscanf(str, "%Lf", &result);

	if (name == 'a' && result == 0) {
		printf("Error. This is a quadratic equation -> `a` cannot be equal to 0\n");
		free(str);
		continue;
	}

  free(str);
	valid = 1;
	} while(valid == 0);

  return result;
}

void main() {
  long double a = validation('a');
  long double b = validation('b');
  long double c = validation('c');
}