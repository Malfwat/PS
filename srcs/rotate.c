/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <admoufle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:26:51 by malfwa            #+#    #+#             */
/*   Updated: 2025/05/14 20:26:53 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps_struct.h"
#include "libftprintf.h"

void	rotate(t_stack **one, t_stack **two, enum e_stack stack)
{
	static char	*move[3] = {"ra\n", "rb\n", "rr\n"};

	if (stack != stack_b && one && *one)
		*one = (*one)->next;
	if (stack != stack_a && two && *two)
		*two = (*two)->next;
	ft_putstr_fd(move[stack], 1);
}

void	rrotate(t_stack **one, t_stack **two, enum e_stack stack)
{
	static char	*move[3] = {"rra\n", "rrb\n", "rrr\n"};

	if (stack != stack_b && one && *one)
		*one = (*one)->prev;
	if (stack != stack_a && two && *two)
		*two = (*two)->prev;
	ft_putstr_fd(move[stack], 1);
}
