/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <admoufle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 19:54:17 by malfwa            #+#    #+#             */
/*   Updated: 2025/05/14 21:43:39 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"
#include "ps_struct.h"

t_pair	get_pair(t_stack *stacks[2], t_stack *node)
{
	void	*mate;
	t_pair	pair;

	mate = smallest_bigger(stacks[stack_a], node->index);
	pair.stack_b = get_cost(stacks[stack_b], node);
	pair.stack_a = get_cost(stacks[stack_a], mate);
	return (pair);
}

t_pair	get_best_pair(t_stack *stacks[2])
{
	t_stack			*it;
	void			*end;
	t_pair			best;
	t_pair			tmp;
	unsigned int	cost;

	cost = (unsigned int)-1;
	it = stacks[stack_b];
	end = it;
	while (it != end || cost == (unsigned int)-1)
	{
		tmp = get_pair(stacks, it);
		if (pair_cost(tmp, &tmp.dir) < cost)
		{
			best = tmp;
			cost = pair_cost(best, &best.dir);
		}
		it = it->next;
	}
	return (best);
}

void	join_pair(t_stack *s[2], t_pair p, u_int8_t dir, enum e_push p_to)
{
	void	(*mv)(t_stack **, t_stack **, enum e_stack);

	mv = NULL;
	if (dir == UP)
		mv = rotate;
	else if (dir == DOWN)
		mv = rrotate;
	if (mv)
		while (s[stack_a] != p.stack_a.node && s[stack_b] != p.stack_b.node)
			mv(s, s + 1, both);
	put_to_top(s, p);
	return (p_stack(s + 1, s, p_to));
}
