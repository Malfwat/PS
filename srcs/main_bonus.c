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

#include "ps.h"
#include "ps_struct.h"
#include "get_next_line.h"

void	error(void *garbage)
{
	ft_putendl_fd("Error", 2);
	free(garbage);
	exit(1);
}

void	make_move(t_stack *stacks[2], char *cmd, void *garbage)
{
	if (!ft_strcmp(cmd, "ra\n"))
		rotate(stacks, stacks + 1, stack_a);
	else if (!ft_strcmp(cmd, "rb\n"))
		rotate(stacks, stacks + 1, stack_b);
	else if (!ft_strcmp(cmd, "rr\n"))
		rotate(stacks, stacks + 1, both);
	else if (!ft_strcmp(cmd, "rra\n"))
		rrotate(stacks, stacks + 1, stack_a);
	else if (!ft_strcmp(cmd, "rrb\n"))
		rrotate(stacks, stacks + 1, stack_b);
	else if (!ft_strcmp(cmd, "rrr\n"))
		rrotate(stacks, stacks + 1, both);
	else if (!ft_strcmp(cmd, "sa\n"))
		s_stack(stacks, stacks + 1, stack_a);
	else if (!ft_strcmp(cmd, "sb\n"))
		s_stack(stacks, stacks + 1, stack_b);
	else if (!ft_strcmp(cmd, "ss\n"))
		s_stack(stacks, stacks + 1, both);
	else if (!ft_strcmp(cmd, "pa\n"))
		p_stack(stacks + 1, stacks, push_to_a);
	else if (!ft_strcmp(cmd, "pb\n"))
		p_stack(stacks, stacks + 1, push_to_b);
	else
		error(garbage);
}

int	main(int ac, char **av)
{
	t_stack	*stacks[2];
	void	*garbage;
	char	*cmd;

	if (ac == 1)
		return (1);
	stacks[stack_a] = init_stack_a(ac, av);
	if (!*stacks)
		return (1);
	garbage = *stacks;
	stacks[stack_b] = 0;
	cmd = get_next_line(0);
	while (cmd)
	{
		make_move(stacks, cmd, garbage);
		free(cmd);
		cmd = get_next_line(0);
	}
	if ((ac - 1 == 1 || is_sorted(stacks[stack_a])) && !stacks[stack_b])
		return (ft_printf("OK\n"), free(garbage), 0);
	return (ft_printf("KO\n"), free(garbage), 0);
}
