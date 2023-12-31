#include "pars.h"

/**
 * itoa - convert a number to string.
 * @num: the number.
 * Return: the number in string.
 */

char *itoa(long num)
{
	unsigned long nbr;
	int size = 0;
	char *str;

	nbr = num * ((num >= 0) - (num < 0));
	while (nbr)
	{
		nbr /= 10;
		size++;
	}
	if (num <= 0)
		size++;
	nbr = num * ((num >= 0) - (num < 0));
	str = my_malloc(size + 1);
	if (!str)
		return (NULL);
	str[size] = 0;
	while (size--)
	{
		str[size] = nbr % 10 + 48;
		nbr /= 10;
	}
	if (num < 0)
		str[0] = '-';
	return (str);
}

