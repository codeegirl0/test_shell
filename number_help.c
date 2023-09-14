#include "shell.h"

/**
 * lng_to_str - make a number as a string.
 * @number: number to be convert.
 * @string: to save a number as a string.
 * @base: base for converting
 * Return: nothing.
 */
void lng_to_str(long number, char *string, int base)
{
	int idx = 0, isNeg = 0;
	long coct = number;
	char letters[] = {"0123456789abcdef"};

	if (coct == 0)
		string[idx++] = '0';

	if (string[0] == '-')
		isNeg = 1;

	while (coct)
	{
		if (coct < 0)
			string[idx++] = letters[-(coct % base)];
		else
			string[idx++] = letters[coct % base];
		coct /= base;
	}
	if (isNeg)
		string[idx++] = '-';

	string[idx] = '\0';
	string_rev(string);
}


/**
 * _tiao - make string as integer.
 * @s: a pointer to str.
 * Return: 0 or int.
 */
int _tiao(char *s)
{
	int sig = 1;
	unsigned int number = 0;
	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			sig *= -1;
		if (*s == '+')
			sig *= +1;
		s++;
	}

	while ('0' <= *s && *s <= '9' && *s != '\0')
	{
		number = (number * 10) + (*s - '0');
		s++;
	}
	return (number * sig);
}

/**
 * count_chars - to count character in string.
 * @string: a pointer to str .
 * @character: chars string to count
 * Return: 0 or int.
 */
int count_chars(char *string, char *character)
{
	int m = 0, count = 0;

	for (; string[m]; m++)
	{
		if (string[m] == character[0])
			count++;
	}
	return (count);
}
