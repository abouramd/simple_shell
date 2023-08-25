#include "exec.h"

/**
 * ft_atoi - to convert from ascii to digit
 * @str: first parameter
 * Return: result in int
 */

int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	unsigned long	n;

	i = 0;
	sign = 1;
	n = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' ')))
		i++;
	if (str[i] && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + str[i] - 48;
		if (n > 9223372036854775807 && sign == 1)
			return (-1);
		else if (n > 9223372036854775807 && sign == -1)
			return (0);
		i++;
	}
	return (sign * n);
}

