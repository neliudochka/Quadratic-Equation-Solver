#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <regex.h>
#include <math.h>

char *dyn_str_implement(char name)
{
	// dynamic string implementation
	printf("%c = ", name);
	char *str, c = 0;
	int i = 0, j = 1;
	str = (char *)malloc(sizeof(char));
	while (c != '\n')
	{
		c = fgetc(stdin);
		str = (char *)realloc(str, j * sizeof(char));
		str[i] = c;
		i++;
		j++;
	}
	str[i - 1] = '\0'; // \0 isted of \n to mark end of string
	return str;
}

int validation(char name, char *str)
{
	// validate input with regex
	regex_t regex;
	int reti = regcomp(&regex, "^-?[0-9]+(.[0-9])?[0-9]*$", REG_EXTENDED);
	reti = regexec(&regex, str, 0, NULL, 0);
	if (reti)
	{
		printf("Error. Expected a valid real number, got %s instead\n", str);
		regfree(&regex);
		return 0;
	}
	regfree(&regex);

	long double result = 0;
	sscanf(str, "%Lf", &result);
	if (name == 'a' && result == 0)
	{
		printf("Error. This is a quadratic equation -> `a` cannot be equal to 0\n");
		return 0;
	}

	return 1;
}

long double intaract_mode_implement(char name)
{
	int isValid = 0;
	long double result = 0;
	while (isValid == 0)
	{
		char *str = dyn_str_implement(name);
		isValid = validation(name, str);
		if (isValid)
			sscanf(str, "%Lf", &result);
		free(str);
	}
	return result;
}

char *stringcpy(const char *original)
{
	int size = strlen(original);
	char *copy = malloc(size + 1);

	int i;
	for (i = 0; original[i] != '\0'; i++)
	{
		copy[i] = original[i];
	}
	copy[i] = 0;
	return copy;
}

void solve_quadratic_equation(long double a, long double b, long double c)
{
	printf("Equation is: (%Lf) x^2 + (%Lf) x + (%Lf) = 0\n", a, b, c);

	long double D = b * b - 4 * a * c;
	if (D < 0)
		printf("D = %Lf, so there are 0 roots\n", D);
	else if (D == 0)
	{
		printf("D = %Lf, so there is 1 root\n", D);
		long double x1 = (-b + sqrtl(D)) / (2 * a);
		printf("x1 = x2 = %Lf\n", x1);
	}
	else
	{
		printf("D = %Lf, so there are 2 roots\n", D);
		long double x1 = (-b + sqrtl(D)) / (2 * a);
		long double x2 = (-b - sqrtl(D)) / (2 * a);
		printf("x1 = %Lf \nx2 = %Lf\n", x1, x2);
	}
}

int main(int argc, char **argv)
{
	long double a = 0, b = 0, c = 0;

	if (argc == 1)
	{ // ?????????????????????????? ??????????
		long double a = intaract_mode_implement('a');
		long double b = intaract_mode_implement('b');
		long double c = intaract_mode_implement('c');
	}

	else
	{ // ????????????????
		FILE *fp;
		char *filename;
		char ch;
		filename = argv[1];

		fp = fopen(filename, "r");
		if (!fp)
		{
			printf("file %s does not exist\n", filename);
		}
		else
		{
			// write content to the dyn_string
			char *full_text;
			full_text = (char *)malloc(sizeof(char));
			int i = 0, j = 1;
			while ((ch = fgetc(fp)) != EOF)
			{
				full_text = (char *)realloc(full_text, j * sizeof(char));
				full_text[i] = ch;
				i++;
				j++;
			}
			if (full_text[i - 1] == '\n')
				full_text[i - 1] = '\0';
			else
			{
				printf("invalid file format\n");
				return 0;
			}

			char *a_str;
			char *b_str;
			char *c_str;

			char delim[] = " ";
			char *ptr = strtok(full_text, delim);
			a_str = stringcpy(ptr);
			ptr = strtok(NULL, delim);

			b_str = stringcpy(ptr);
			ptr = strtok(NULL, delim);

			c_str = stringcpy(ptr);
			ptr = strtok(NULL, delim);

			free(full_text);

			if (!validation('a', a_str))
				return 0;
			if (!validation('b', b_str))
				return 0;
			if (!validation('c', c_str))
				return 0;

			sscanf(a_str, "%Lf", &a);
			sscanf(b_str, "%Lf", &b);
			sscanf(c_str, "%Lf", &c);
		}
	}

	solve_quadratic_equation(a, b, c);
	return 0;
}