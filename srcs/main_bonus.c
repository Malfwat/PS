/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <admoufle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:53:50 by malfwa            #+#    #+#             */
/*   Updated: 2025/05/15 20:24:24 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "ps.h"
#include "ps_struct.h"
#include "get_next_line.h"

int	ft_strcmp(char *a, char *b)
{
	int	i;

	if (!a && !b)
		return (0);
	if (!a)
		return (*b);
	if (!b)
		return (*a);
	i = 0;
	while (a[i] && a[i] == b[i])
		i++;
	return (a[i] - b[i]);
}

void	error(t_stack *stacks[2])
{
	ft_printf("Probleme\n");
	(void)stacks;
}

void	make_move(t_stack *stacks[2], char *cmd)
{
	if (!ft_strcmp(cmd, "ra"))
		rotate(stacks, stacks + 1, stack_a);
	else if (!ft_strcmp(cmd, "rb"))
		rotate(stacks, stacks + 1, stack_b);
	else if (!ft_strcmp(cmd, "rr"))
		rotate(stacks, stacks + 1, both);
	else if (!ft_strcmp(cmd, "rra"))
		rrotate(stacks, stacks + 1, stack_a);
	else if (!ft_strcmp(cmd, "rrb"))
		rrotate(stacks, stacks + 1, stack_b);
	else if (!ft_strcmp(cmd, "rrr"))
		rrotate(stacks, stacks + 1, both);
	else if (!ft_strcmp(cmd, "sa"))
		s_stack(stacks, stacks + 1, stack_a);
	else if (!ft_strcmp(cmd, "sb"))
		s_stack(stacks, stacks + 1, stack_b);
	else if (!ft_strcmp(cmd, "ss"))
		s_stack(stacks, stacks + 1, both);
	else if (!ft_strcmp(cmd, "pa"))
		p_stack(stacks + 1, stacks, push_to_a);
	else if (!ft_strcmp(cmd, "pb"))
		p_stack(stacks, stacks + 1, push_to_b);
	else
		error(stacks);
}

#include <fcntl.h>

int	main(int ac, char **av)
{
	t_stack	*stacks[2];
	void	*garbage;
	char	*cmd;
	int		len;

	if (ac == 1)
		return (0);
	stacks[stack_a]	= init_stack_a(ac, av);
	if (!*stacks)
		return (1);
	garbage = *stacks;
	stacks[stack_b] = 0;
	cmd	= get_next_line(0);
	while (cmd)
	{
		len = ft_strlen(cmd);
		if (len && cmd[len - 1] == '\n')
			cmd[len - 1] = 0;
		make_move(stacks, cmd);
		free(cmd);
		cmd = get_next_line(0);
	}
	if (is_sorted(stacks[stack_a]) && !stacks[stack_b])
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	return (free(garbage), 0);
}
