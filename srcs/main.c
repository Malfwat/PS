/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <admoufle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:06:42 by malfwa            #+#    #+#             */
/*   Updated: 2025/05/14 20:06:44 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "ps_struct.h"
#include "ps.h"

void	sort_three(t_stack **s)
{
	if ((*s)->index > (*s)->next->index && (*s)->index < (*s)->prev->index)
		s_stack(s, 0, stack_a);
	else if ((*s)->index < (*s)->next->index && (*s)->index > (*s)->prev->index)
		rrotate(s, 0, stack_a);
	else if ((*s)->index < (*s)->next->index && (*s)->next->index > (*s)->prev->index)
	{
		s_stack(s, 0, stack_a);
		rotate(s, 0, stack_a);
	}
	else if ((*s)->prev->index < (*s)->next->index)
	{
		s_stack(s, 0, stack_a);
		rrotate(s, 0, stack_a);
	}
	else
		rotate(s, 0, stack_a);
}

void	sort_five(t_stack *stacks[2])
{
	p_stack(stacks, stacks + 1, push_to_b);
	p_stack(stacks, stacks + 1, push_to_b);
	sort_three(stacks);
	resolve(stacks);
}

int	main(int ac, char **av)
{
	t_stack	*stacks[2];
	void	*garbage;

	if (ac < 2)
		return (ft_putendl_fd("Gimme some number", 2), 1);
	stacks[stack_a] = init_stack_a(ac, av);
	if (is_sorted(stacks[stack_a]))
		return (free(*stacks), 0);
	if (!stacks[stack_a])
		return (ft_putendl_fd("Something wrong with your input", 2), 1);
	garbage = *stacks;
	stacks[stack_b] = 0;
	if (ac - 1 == 3)
		sort_three(stacks);
	else if (ac - 1 == 5)
		sort_five(stacks);
	else
	{
		init_stack_b(stacks, ac - 1);
		resolve(stacks);
	}
	free(garbage);
	return (0);
}
