/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admoufle <admoufle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 07:46:24 by malfwa            #+#    #+#             */
/*   Updated: 2025/04/27 14:46:29 by admoufle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_all(char **stash)
{
	int	i;

	i = 0;
	while (i < 4096)
	{
		free(stash[i]);
		stash[i] = 0;
		i++;
	}
}

void	free_lst(t_read *head)
{
	t_read	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->ptr);
		free(tmp);
	}
}

char	*ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (str + i);
		i++;
	}
	return (NULL);
}

char	*ft_substring(char *str, int len)
{
	int		i;
	char	*new;

	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (++i < len)
		new[i] = str[i];
	new[i] = 0;
	return (new);
}

char	*refresh(char **stash_ptr, char *stash)
{
	char	*tmp;
	int		i;
	char	*line;

	tmp = ft_strchr(stash, '\n') + 1;
	line = ft_substring(stash, tmp - stash);
	i = 0;
	while (tmp[i])
	{
		stash[i] = tmp[i];
		i++;
	}
	stash[i] = 0;
	if (!i)
	{
		free(stash_ptr[i]);
		*stash_ptr = 0;
	}
	return (line);
}
