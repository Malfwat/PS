/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admoufle <admoufle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:44:23 by admoufle          #+#    #+#             */
/*   Updated: 2025/04/24 12:44:24 by admoufle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (*s2);
	if (!s2)
		return (*s1);
	i = 0;
	while (s1[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return (s1[i] - s2[i]);
}
