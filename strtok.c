#include "shell.h"

/**
 * ifdelim - a function that checks the character after the string
 * @c: The character to be checked
 * @delim: The character after the string
 * Return: 0
 */

unsigned int ifdelim(char c, char *delim)
{
	while (*delim != '\0')
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}

/**
 * _strtok - a function that works te same as the strtok functon
 * @str: our string
 * @delim: te character after our string
 * Return: 0
 */

char *_strtok(char *str, char *delim)
{
	static char *next_token; /* Stores the next position to start tokenizing */
	char *token_start;

	if (!str)
	str = next_token;

	if (!str) /* if user input is not a string */
		return (NULL);
	while (1)
	{
	if (ifdelim(*str, delim))
	{
		str++;
	continue; /* continue to check the next string */
	}
	if (*str == '\0')
		return (NULL);
	break;
	}
	token_start = str;

	while (1)
	{
	if (*str == '\0')
	{
	next_token = str;
	return (token_start);
	}

	if (ifdelim(*str, delim))
	{
	*str = '\0';
	next_token = str + 1;
	return (token_start);
	}
	str++;
	}
}
