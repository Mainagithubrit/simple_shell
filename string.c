#include "shell.h"

/**
 * _strcpy - copies the string pointed to by src
 * @dest: destination
 * @src: source
 * Return: string
 */
char *_strcpy(char *dest, char *src)
{
	int len = 0;

	while (*(src + len) != '\0')
	{
		*(dest + len) = *(src + len);
		len++;
	}

	*(dest + len) = '\0';
	return (dest);
}

/**
 * _strcat - concertanate two strings
 * @dest: string 1
 * @src: string 2
 *
 * Return: value of string 1 which is a pointer to the result
 */

char *_strcat(char *dest, char *src)
{
	int i, j;

	i = 0;
	j = 0;

	while (dest[j] != '\0')
	{
		j++;
	}
	while (src[i] != '\0')
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = src[i];
	return (dest);
}

/**
 * _strdup - Makes a copy of the string given as parameter
 * @str: string paramenter
 *
 * Return: Pointer to newly allocated string
 */

char *_strdup(const char *str)
{
	char *c;
	int i, count = 0;

	if (str == NULL)
		return (NULL);

	for (i = 0; str[i] != '\0'; i++)
		count++;
	c = malloc(count + 1);
	if (c == NULL)
		return (NULL);
	for (i = 0; i <= count; i++)
	{
		c[i] = str[i];
	}
	return (c);
}

/**
 * _strcmp - Comapare two sting
 *
 * @s1: string 1
 * @s2: string 2
 *
 * Return: the difference in string
 */

int _strcmp(char *s1, char *s2)
{
	int i = 0, j = 0;

	for (; s1[i] != '\0' && s2[i] != '\0'; i++)
	{
		j = s1[i] - s2[i];
		if (j != 0)
			break;
	}
	return (j);
}

/**
 * _strncmp - compares n number of two strings
 * @str1: string 1
 * @str2: string 2
 * @n: Number
 * Return: 0 if string are same
 */

int _strncmp(const char *str1, const char *str2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		if (str1[i] == '\0')
			return (0);
	}
	return (0);
}

