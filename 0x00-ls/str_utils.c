#include "customls.h"
/**
 * _strcmp - compares strings
 * @p1: string to compare
 * @p2: string to compare
 * Return: Always 0 on success
 */
int _strcmp(char *p1, char *p2)
{
	const unsigned char *s1 = (const unsigned char *) p1;
	const unsigned char *s2 = (const unsigned char *) p2;
	unsigned char c1, c2;

	do {
		c1 = (unsigned char) *s1++;
		c2 = (unsigned char) *s2++;
	if (c1 == '\0')
		return (c1 - c2);
	} while (c1 == c2);
	return (c1 - c2);
}

/**
 * _strfcmp - compares first char
 * @p1: string to compare
 * @p2: string to compare
 * Return: Always 0 on success
 */
int _strfcmp(char *p1, char *p2)
{
	const unsigned char *s1 = (const unsigned char *) p1;
	const unsigned char *s2 = (const unsigned char *) p2;
	unsigned char c1, c2;

	c1 = (unsigned char) *s1++;
	c2 = (unsigned char) *s2++;
	return (c1 - c2);
}

/**
  *_strncpy - merge  two strings
  *
  *@dest: second string
  *@src: first string
  *@n: limit number
  *Return: a pointer, to dest
  */
char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; i < n && src[i] != 0; i++)
		*(dest + i) = *(src + i);
	for (; i < n; i++)
		*(dest + i) = 0;
	return (dest);
}

/**
 *_strlen - returns data len
 *@s: input string
 *
 *Return:an int number
 *
 */
int _strlen(char *s)
{
	int counter = 0;

	while (*(s + counter) != 0)
	{
	counter++;
	}
	return (counter);
}

/**
  *_strcat - concatenates two strings
  *
  *@dest: second string
  *@src: first string
  *Return: a pointer, to dest
  */
char *_strcat(char *dest, char *src)
{
	int i, counter = 0;

	while (*(dest + counter) != 0)
	{
		counter++;
	}
	for (i = counter;  src[i - counter] != 0; i++)
	{
		*(dest + i) = *(src + i - counter);
	}
	return (dest);
}
