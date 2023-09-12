#include "shell.h"
/**
 * _stringtok - separates strings with delimiters
 * @myline: array from getline
 * @mydelim: character to mark splite
 * Return: the token that created
*/
char *_stringtok(char *myline, char *mydelim)
{
	int n;
	static char *mystr;
	char *mystrcp;

	if (myline != NULL)
		mystr = myline;
	for (; *mystr != '\0'; mystr++)
	{
		for (n = 0; mydelim[n] != '\0'; n++)
		{
			if (*mystr == mydelim[n])
			break;
		}
		if (mydelim[n] == '\0')
			break;
	}
	mystrcp = mystr;
	if (*mystrcp == '\0')
		return (NULL);
	for (; *mystr != '\0'; mystr++)
	{
		for (n = 0; mydelim[n] != '\0'; n++)
		{
			if (*mystr == mydelim[n])
			{
				*mystr = '\0';
				mystr++;
				return (mystrcp);
			}
		}
	}
	return (mystrcp);
}
