#include "ps_struct.h"
#include "libftprintf.h"

void	swap(t_stack *a, t_stack *b, t_stack **head)
{
	t_stack	*prev;
	t_stack	*next;

	if (a == *head)
		*head = b;
	next = b->next;
	prev = a->prev;
	a->prev->next = b;
	b->next = a;
	b->prev = prev;
	a->next = next;
	a->prev = b;
}

void	s_stack(t_stack **one, t_stack **two, enum e_stack stack)
{
	t_stack		*next;
	static char	*move[3] = {"sa\n", "sb\n", "ss\n"};

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
	ft_putstr_fd(move[stack], 1);
}
