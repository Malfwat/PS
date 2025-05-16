/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nb_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <admoufle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:36:05 by malfwa            #+#    #+#             */
/*   Updated: 2025/05/16 13:36:10 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
