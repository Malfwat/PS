/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <admoufle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:26:51 by malfwa            #+#    #+#             */
/*   Updated: 2025/05/15 18:51:27 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps_struct.h"
#include "libftprintf.h"

void	rotate(t_stack **one, t_stack **two, enum e_stack stack)
{
	if (stack != stack_b && one && *one)
		*one = (*one)->next;
	if (stack != stack_a && two && *two)
		*two = (*two)->next;
}

void	rrotate(t_stack **one, t_stack **two, enum e_stack stack)
{
	(void)stack;
	if (stack != stack_b && one && *one)
		*one = (*one)->prev;
	if (stack != stack_a && two && *two)
		*two = (*two)->prev;
}
