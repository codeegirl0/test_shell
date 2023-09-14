#include "shell.h"

/**
 * string_len - to show a string mlength.
 * @string: pointer of a string.
 * Return: string length.
 */
int string_len(char *string)
{
	int leng = 0;

	if (string == NULL)
		return (0);

	while (string[leng++] != '\0')
	{
	}
	return (--leng);
}

/**
 * string_dup - to duplicate string
 * @string: str to copy
 * Return: pointer of array
 */
char *string_dup(char *string)
{
	char *result;
	int leng, m;

	if (string == NULL)
		return (NULL);

	leng = string_len(string) + 1;

	result = malloc(sizeof(char) * leng);

	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (m = 0; m < leng ; m++)
	{
		result[m] = string[m];
	}

	return (result);
}

/**
 * string_cmp - to compare 2 strs
 * @string1: Str 1 or shorter
 * @string2: str 2 or the longer
 * @number: characters to compare or 0 if infinite
 * Return: 1 if equals or 0 if different
 */
int string_cmp(char *string1, char *string2, int number)
{
	int iterat;

	if (string1 == NULL && string2 == NULL)
		return (1);

	if (string1 == NULL || string2 == NULL)
		return (0);

	if (number == 0) 
	{
		if (string_len(string1) != string_len(string2))
			return (0);
		for (iterat = 0; string1[iterat]; iterat++)
		{
			if (string1[iterat] != string2[iterat])
				return (0);
		}
		return (1);
	}
	else
	{
		for (iterat = 0; iterat < number ; iterat++)
		{
			if (string1[iterat] != string2[iterat])
			return (0);
		}
		return (1);
	}
}

/**
 * str_concati_nate - concatenating 2 str.
 * @string1: String to concatenat
 * @string2: String to concatenat
 * Return: array pointer
 */
char *string_concati_nate(char *string1, char *string2)
{
	char *result;
	int leng1 = 0, leng2 = 0;

	if (string1 == NULL)
		string1 = "";
	leng1 = string_len(string1);

	if (string2 == NULL)
		string2 = "";
	leng2 = string_len(string2);

	result = malloc(sizeof(char) * (leng1 + leng2 + 1));
	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	for (leng1 = 0; string1[leng1] != '\0'; leng1++)
		result[leng1] = string1[leng1];
	free(string1);

	for (leng2 = 0; string2[leng2] != '\0'; leng2++)
	{
		result[leng1] = string2[leng2];
		leng1++;
	}

	result[leng1] = '\0';
	return (result);
}


/**
 * string_rev - to reverse a string.
 * @string: the pointer of string.
 * Return: nothing.
 */
void string_rev(char *string)
{

	int m = 0, leng = string_len(string) - 1;
	char hold;

	while (m < leng)
	{
		hold = string[m];
		string[m++] = string[leng];
		string[leng--] = hold;
	}
}