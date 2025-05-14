/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <admoufle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:06:41 by malfwa            #+#    #+#             */
/*   Updated: 2025/05/14 20:28:49 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps_struct.h"
#include "ps.h"

unsigned int	biggest_cost(unsigned int a, unsigned int b)
{
	if (a > b)
		return (a);
	return (b);
}

unsigned int	min_cost(t_target target)
{
	if (target.direction == up)
		return (target.cost_up);
	return (target.cost_down);
}

unsigned int	pair_cost(t_pair pair, u_int8_t *final_direction)
{
	unsigned int	cost;
	unsigned int	tmp;

	cost = biggest_cost(pair.stack_a.cost_up, pair.stack_b.cost_up);
	*final_direction = UP;
	tmp = biggest_cost(pair.stack_a.cost_down, pair.stack_b.cost_down);
	if (cost > tmp)
	{
		cost = tmp;
		*final_direction = DOWN;
	}
	tmp = min_cost(pair.stack_a) + min_cost(pair.stack_b);
	if (cost > tmp)
	{
		cost = tmp;
		*final_direction = SEPARATE;
	}
	return (cost + 1);
}

t_target	get_cost(t_stack *stack, t_stack *node)
{
	unsigned int	size;
	unsigned int	pos;
	t_target		target;

	size = stack_size(stack);
	pos = get_position(stack, node);
	target.node = node;
	if (pos < size - pos)
		target.direction = up;
	else
		target.direction = down;
	target.cost_down = size - pos;
	target.cost_up = pos;
	return (target);
}
