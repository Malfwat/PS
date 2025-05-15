/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <admoufle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:05:55 by malfwa            #+#    #+#             */
/*   Updated: 2025/05/14 20:28:28 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "ps_struct.h"
#include "ps.h"

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

unsigned int	stack_size(t_stack *head)
{
	unsigned int	len;
	void			*end;

	len = 0;
	if (!head)
		return (0);
	end = head;
	while (head != end || !len)
	{
		head = head->next;
		len++;
	}
	return (len);
}

unsigned int	get_position(t_stack *head, t_stack *node)
{
	unsigned int	pos;

	pos = 0;
	while (head != node)
	{
		pos++;
		head = head->next;
	}
	return (pos);
}

t_stack	*smallest_bigger(t_stack *stack, unsigned int index)
{
	int		go;
	t_stack	*node;
	void	*end;

	go = 1;
	end = stack;
	node = NULL;
	while (stack != end || go--)
	{
		if (stack->index > index && (!node || stack->index < node->index))
			node = stack;
		stack = stack->next;
	}
	if (node)
		return (node);
	go = 1;
	while (stack != end || go--)
	{
		if (!node || node->index > stack->index)
			node = stack;
		stack = stack->next;
	}
	return (node);
}

bool	is_sorted(t_stack *stack)
{
	unsigned int	tmp;
	void			*end;

	end = stack;
	tmp = 0;
	while (stack != end || !tmp)
	{
		if (stack->index < tmp)
			return (false);
		tmp = stack->index;
		stack = stack->next;
	}
	return (true);
}
