/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admoufle <admoufle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:52:12 by admoufle          #+#    #+#             */
/*   Updated: 2025/05/15 18:27:56 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif /*BUFFER_SIZE*/

# if (BUFFER_SIZE < 0)
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

# include "libftprintf.h"
# include <stdlib.h>

typedef struct s_read
{
	char			*ptr;
	struct s_read	*next;
}					t_read;

char	*ft_substring(char *str, int len);
void	free_lst(t_read *head);
void	free_all(char **stash);
char	*refresh(char **stash_ptr, char *stash);
char	*get_next_line(int fd);

#endif /*GET_NEXT_LINE_H*/
