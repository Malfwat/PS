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
	init_stack_b(stacks, ac - 1);
	resolve(stacks);
	free(garbage);
	return (0);
}
