#include "pars.h"

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
	if (!(str = my_malloc(size + 1)))
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

