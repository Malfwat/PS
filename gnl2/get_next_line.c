/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <malfwa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:50:21 by admoufle          #+#    #+#             */
/*   Updated: 2025/05/02 08:48:46 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>

bool	add_back(t_read **head, char *str)
{
	t_read	*new;
	t_read	*last;
	int		i;

	new = malloc(sizeof(t_read));
	if (!new)
		return (false);
	new->next = NULL;
	new->ptr = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!new->ptr)
		return (free(new), false);
	i = -1;
	while (str[++i])
		new->ptr[i] = str[i];
	new->ptr[i] = 0;
	if (!*head)
		*head = new;
	else
	{
		last = *head;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	return (true);
}

t_read	*create_line(t_read *lst, char *new, int *j_ptr)
{
	int	i;
	int	j;

	i = 0;
	while (lst)
	{
		j = 0;
		while (lst->ptr[j] && lst->ptr[j] != '\n')
			new[i++] = lst->ptr[j++];
		if (lst->ptr[j] == '\n' && ++j)
		{
			new[i++] = '\n';
			new[i] = 0;
			break ;
		}
		else
			new[i] = 0;
		lst = lst->next;
	}
	*j_ptr = j;
	return (lst);
}

char	*t_read_join(t_read *lst, char **stash_tab, int size, int fd)
{
	int		j;
	int		i;
	char	*new;
	t_read	*ptr;

	new = malloc(sizeof(char) * (BUFFER_SIZE * size + 1));
	if (!new)
		return (free_all(stash_tab), NULL);
	ptr = lst;
	lst = create_line(lst, new, &j);
	if (!lst)
	{
		free(stash_tab[fd]);
		stash_tab[fd] = 0;
	}
	else
	{
		i = 0;
		while (lst->ptr[j])
			stash_tab[fd][i++] = lst->ptr[j++];
		stash_tab[fd][i] = 0;
	}
	free_lst(ptr);
	return (new);
}

char	*get_line(char **stash, int fd)
{
	int		nb_r;
	t_read	*head;
	int		lst_size;

	head = NULL;
	lst_size = 0;
	if (ft_strchr(stash[fd], '\n'))
		return (refresh(&stash[fd], stash[fd]));
	else if (stash[fd] && stash[fd][0] && ++lst_size)
		add_back(&head, stash[fd]);
	nb_r = read(fd, stash[fd], BUFFER_SIZE);
	if (nb_r < 0)	
		return (free(stash[fd]), free_lst(head), NULL);
	// printf("Je suis %i\n", fd);
	while (nb_r)
	{
		stash[fd][nb_r] = 0;
		add_back(&head, stash[fd]);
		lst_size++;
		if (ft_strchr(stash[fd], '\n'))
			break ;
		nb_r = read(fd, stash[fd], BUFFER_SIZE);
	}
	if (!lst_size)
		return (free(stash[fd]), NULL);
	return (t_read_join(head, stash, lst_size, fd));
}

char	*get_next_line(int fd)
{
	static char	*stash[4096];
	char		*line;

	if (fd < 0 || BUFFER_SIZE > INT_MAX - 1 || fd >= 4096)
		return (free_all(stash), NULL);
	if (!stash[fd])
	{
		stash[fd] = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!stash[fd])
			return (free_all(stash), NULL);
		stash[fd][0] = '\0';
	}
	line = get_line(stash, fd);
	if (!line)
		stash[fd] = 0;
	return (line);
}
