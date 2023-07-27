#include "shell.h"

/**
  * perr_str - a function that checks the errors in a string
  * @s1: the first string to be checked
  * @s2: the second string to be checked
  * Return: 0
  */
int perr_str(char *s1, char *s2)
{
	int count = 0;

	while (*s1)
		count += perr_ch(*s1++);
	while (*s2)
		count += perr_ch(*s2++);
	return (count);
}

/**
  * perr_ch - a function that checks for an error in a character in a string
  * @c: the character to be checked
  * Return: 0
  */
int perr_ch(char c)
{
	static char buff[BUFF_SIZE];
	static int i;

	if (c == -1 || i == (BUFF_SIZE - 1))
	{
		write(STDERR_FILENO, &buff, i);
		i = 0;
	}
	if (c != -1)
		buff[i++] = c;
	return (1);
}

/**
  * p_str - a function that checks the errors in a string
  * @s1: the first string to be checked
  * @s2: the second string to be checked
  * Return: 0
  */
int p_str(char *s1, char *s2)
{
	int count = 0;

	while (*s1)
		count += p_ch(*s1++);
	while (*s2)
		count += p_ch(*s2++);
	return (count);
}

/**
  * p_ch - a function that checks for an error in a character in a string
  * @c: the character to be checked
  * Return: 0
  */
int p_ch(char c)
{
	 static char buff[BUFF_SIZE];
	 static int i;

	if (c == -1 || i == (BUFF_SIZE - 1))
	{
		write(STDOUT_FILENO, &buff, i);
		i = 0;
	}
	if (c != -1)
		buff[i++] = c;
	return (1);
}
