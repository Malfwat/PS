/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <admoufle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:11:13 by malfwa            #+#    #+#             */
/*   Updated: 2025/05/14 20:24:50 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "ps.h"
#include "ps_struct.h"

int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (false);
		i++;
	}
	return (true);
}

bool	fill_data(t_stack **arr, t_stack *stack, char **av, int i)
{
	if (!ft_isnumber(av[i + 1]))
		return (false);
	stack[i].value = ft_atoi(av[i + 1]);
	stack[i].next = stack + i + 1;
	stack[i].prev = stack + i - 1;
	stack[i].lis = false;
	arr[i] = stack + i;
	return (true);
}

t_stack	*init_stack_a(int ac, char **av)
{
	t_stack	*stack;
	t_stack	**tmp;
	int		i;

	stack = malloc(sizeof(t_stack) * (ac - 1));
	if (!stack)
		return (NULL);
	tmp = malloc(sizeof(t_stack *) * (ac - 1));
	if (!tmp)
		return (free(stack), NULL);
	i = 0;
	while (i < ac - 1)
		if (!fill_data(tmp, stack, av, i++))
			return (free(stack), free(tmp), NULL);
	stack[i - 1].next = stack;
	stack[0].prev = stack + i - 1;
	my_qsort(tmp, 0, ac - 2);
	i = -1;
	while (++i < ac - 1)
		tmp[i]->index = i;
	lis(stack, ac - 1);
	return (free(tmp), stack);
}

void	put_first_elem(t_stack *stacks[2], int size)
{
	u_int8_t	dir;
	int			i;

	i = -1;
	if (!size)
		return ;
	dir = 0;
	while (!dir && ++i < size)
	{
		if (stacks[stack_a][i].lis == 0)
			dir = UP;
		else if (stacks[stack_a][size - i - 1].lis == 0)
			dir = DOWN;
	}
	while (i-- >= 0)
	{
		if (dir == UP)
			rotate(stacks, stacks + 1, stack_a);
		else if (dir == DOWN)
			rrotate(stacks, stacks + 1, stack_a);
	}
	p_stack(stacks, stacks + 1, push_to_b);
}

void	init_stack_b(t_stack *stacks[2], unsigned int size)
{
	put_first_elem(stacks, size);
	while (!is_all_lis(stacks[stack_a]))
	{
		if (!stacks[stack_a]->lis)
		{
			p_stack(stacks, stacks + 1, push_to_b);
			if (stacks[stack_b]->index < size / 2)
				rotate(stacks, stacks + 1, stack_b);
		}
		else
			rotate(stacks, stacks + 1, stack_a);
	}
}
