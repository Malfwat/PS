/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <admoufle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:20:35 by malfwa            #+#    #+#             */
/*   Updated: 2025/05/14 20:22:03 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PS_H
# define PS_H

# include "ps_struct.h"
# include <stdbool.h>

void			s_stack(t_stack **from, t_stack **to, enum e_stack stack);
void			p_stack(t_stack **from, t_stack **to, enum e_push direction);
void			rrotate(t_stack **one, t_stack **two, enum e_stack stack);
void			rotate(t_stack **one, t_stack **two, enum e_stack stack);
unsigned int	stack_size(t_stack *head);

unsigned int	get_position(t_stack *head, t_stack *node);
void			put_to_top(t_stack *stacks[2], t_pair pair);
int				ft_strcmp(char *a, char *b);

bool			ft_isnumber(char *str);
bool			is_sorted(t_stack *stack);
void			join_pair(t_stack *stacks[2], t_pair pair, u_int8_t dir,\
		enum e_push push_to);
t_stack			*smallest_bigger(t_stack *stack, unsigned int index);
t_pair			get_best_pair(t_stack *stacks[2]);
unsigned int	pair_cost(t_pair pair, u_int8_t *final_direction);
bool			is_all_lis(t_stack *head);
t_target		get_cost(t_stack *stack, t_stack *node);
void			resolve(t_stack *stacks[2]);
void			lis(t_stack *tab, int size);
void			my_qsort(t_stack **arr, int left, int right);
void			init_stack_b(t_stack *stacks[2], unsigned int size);
t_stack			*init_stack_a(int ac, char **av);
#endif //PS_H
