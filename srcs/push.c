#include "ps_struct.h"
#include "libftprintf.h"

t_stack	*pop(t_stack **head)
{
	t_stack	*tmp;
	t_stack	*prev;
	t_stack	*next;

	if (!head || !*head)
		return (NULL);
	prev = (*head)->prev;
	next = (*head)->next;
	tmp = *head;
	if (tmp->next == tmp)
		*head = NULL;
	else
	{
		(*head) = next;
		next->prev = prev;
		prev->next = next;
	}
	return (tmp);
}

void	push(t_stack **head, t_stack *node)
{
	if (!*head)
	{
		*head = node;
		node->next = node;
		node->prev = node;
		return ;
	}
	node->next = *head;
	node->prev = (*head)->prev;
	(*head)->prev = node;
	node->prev->next = node;
	*head = node;
}

void	p_stack(t_stack **from, t_stack **to, enum e_push direction)
{
	static char *move[2] = {"pa\n", "pb\n"};

	if (!*from)
		return ;
	push(to, pop(from));
	ft_putstr_fd(move[direction], 1);
}
