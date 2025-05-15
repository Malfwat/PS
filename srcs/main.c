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
	t_stack	*n;
	t_stack	*p;

	n = (*s)->next;
	p = (*s)->prev;
	if ((*s)->index > n->index && (*s)->index < p->index)
		s_stack(s, 0, stack_a);
	else if ((*s)->index < n->index && (*s)->index > p->index)
		rrotate(s, 0, stack_a);
	else if ((*s)->index < n->index && n->index > p->index)
	{
		s_stack(s, 0, stack_a);
		rotate(s, 0, stack_a);
	}
	else if (p->index < n->index)
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

void	sorting(t_stack *stacks[2], int size)
{
	if (size == 3)
		sort_three(stacks);
	else if (size == 5)
		sort_five(stacks);
	else
	{
		init_stack_b(stacks, size);
		resolve(stacks);
	}
}

int	main(int ac, char **av)
{
	t_stack	*stacks[2];
	void	*garbage;

	if (ac < 2)
		return (0);
	if (ac == 2)
	{
		if (!ft_isnumber(av[1]))
			ft_putendl_fd("Error", 2);
		return (0);
	}
	stacks[stack_a] = init_stack_a(ac, av);
	if (!*stacks || is_sorted(stacks[stack_a]))
		return (free(*stacks), 0);
	garbage = *stacks;
	stacks[stack_b] = 0;
	sorting(stacks, ac - 1);
	return (free(garbage), 0);
}
