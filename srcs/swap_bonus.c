/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <admoufle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:25:58 by malfwa            #+#    #+#             */
/*   Updated: 2025/05/15 18:51:40 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps_struct.h"
#include "ps.h"
#include "libftprintf.h"

void	swap(t_stack *a, t_stack *b, t_stack **head)
{
	t_stack	*prev;
	t_stack	*next;

	if (a == *head)
		*head = b;
	if (stack_size(*head) == 2)
		return ;
	next = b->next;
	prev = a->prev;
	a->prev->next = b;
	b->next = a;
	b->prev = prev;
	a->next = next;
	a->next->prev = a;
	a->prev = b;
}

void	s_stack(t_stack **one, t_stack **two, enum e_stack stack)
{
	t_stack		*next;

	(void)stack;
	if (stack != stack_b && one && *one)
	{
		next = (*one)->next;
		swap(*one, next, one);
	}
	if (stack != stack_a && two && *two)
	{
		next = (*two)->next;
		swap(*two, next, two);
	}
}
