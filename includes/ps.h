#ifndef PS_H
# define PS_H

# include "ps_struct.h"

void	s_stack(t_stack **from, t_stack **to, enum e_stack stack);
void	p_stack(t_stack **from, t_stack **to, enum e_push direction);
void	rrotate(t_stack **one, t_stack **two, enum e_stack stack);
void	rotate(t_stack **one, t_stack **two, enum e_stack stack);
unsigned int	stack_size(t_stack *head);

void	my_qsort(t_stack **arr, int left, int right);
#endif //PS_H
