/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <admoufle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:02:23 by malfwa            #+#    #+#             */
/*   Updated: 2025/05/14 20:26:37 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps_struct.h"
#include "ps.h"

void	put_to_top(t_stack *stacks[2], t_pair pair)
{
	while (pair.stack_a.node != stacks[stack_a])
	{
		if (pair.stack_a.direction == up)
			rotate(stacks, stacks + 1, stack_a);
		else
			rrotate(stacks, stacks + 1, stack_a);
	}
	while (pair.stack_b.node != stacks[stack_b])
	{
		if (pair.stack_b.direction == up)
			rotate(stacks, stacks + 1, stack_b);
		else
			rrotate(stacks, stacks + 1, stack_b);
	}
}

void	resolve(t_stack *stacks[2])
{
	t_pair		pair;
	t_target	first;
	t_stack		*tmp;
	void		(*mv)(t_stack **, t_stack **, enum e_stack);

	while (stacks[stack_b])
	{
		pair = get_best_pair(stacks);
		join_pair(stacks, pair, pair.dir, push_to_a);
	}
	tmp = stacks[stack_a];
	while (tmp->index != 0)
		tmp = tmp->next;
	first = get_cost(stacks[stack_a], tmp);
	if (first.direction == up)
		mv = rotate;
	else
		mv = rrotate;
	while (stacks[stack_a]->index != 0)
		mv(stacks, stacks + 1, stack_a);
}
