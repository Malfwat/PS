#include "libftprintf.h"
#include "ps.h"

bool	check_overflow(char *nb)
{
	if (ft_strlen(nb) < 10)
		return (true);
	if (*nb == '+')
		return (ft_strcmp("+2147483647", nb) >= 0);
	else if (*nb == '-')
		return (ft_strcmp("-2147483648", nb) >= 0);
	else
		return (ft_strcmp("2147483647", nb) >= 0);
}

bool	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (false);
		i++;
	}
	return (check_overflow(str));
}
