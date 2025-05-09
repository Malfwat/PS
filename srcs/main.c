#include "libftprintf.h"
#include "ps_struct.h"

t_stack	initialize(int ac, char );

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

void	s_stack(t_stack **a, enum e_stack stack)
{
	t_stack	*next;

	next = (*a)->next;
	swap(*a, next, a);
	ft_putendl_fd((char *[]){"sa", "sb"}[stack], 1);
}

void	rotate(t_stack **head)
{
	*head = (*head)->next;
}

void	rrotate(t_stack **head)
{
	*head = (*head)->prev;
}

void	p_stack(t_stack **from, t_stack **to, enum e_stack stack)
{
	if ((*from)->next != *from)
	{
		(*from)->next->prev = (*from)->prev;
		(*from)->prev->next = (*from)->next;
		(*from) = (*from)->next;
	}

	if (*to && (*to)->prev)
		(*to)->prev->next = *from;
	if (*to && (*to)->next)
		(*to)->next->prev = *from;
	*to = *from;

	ft_putendl_fd((char *[]){"pa", "pb"}[stack], 1);
}

int	binary_search(t_stack *tab, int *tail, int length, int key)
{
	int	low;
	int high;
	int mid;

	low = 0;
	high = length - 1;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if ((int)tab[tail[mid]].value_sorted < key)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return (low);
}

void	lis(t_stack *tab, int size)
{
	int	prev[4096];
	int	tail[4096];
	int i;
	int len;
	int	pos;

	i = 0;
	while (i < 4096)
	{
		prev[i] = -1;
		tail[i] = 0;
		i++;
	}
	len = 0;
	i = 0;
	(void)prev;
	while (i < size)
	{
		pos = binary_search(tab, tail, len, tab[i].value_sorted);
		tail[pos] = i;
		if (pos > 0)
			prev[i] = tail[pos - 1];
		if (pos == len)
				len++;
		i++;
	}
	int k = tail[len - 1];
	i = len - 1;
	while (i >= 0)
	{
		ft_printf("%i\t", k);
		tab[k].lis = true;
		k = prev[k];
		i--;
	}
	ft_printf("\n");
}

int main(int ac, char **av)
{
	int i;
	t_stack	*stack;
	t_stack	**tmp;
	t_stack	*head;
	void	*garbage;

	i = 0;
	if (ac == 1)
		return (1);
	stack = malloc(sizeof(t_stack) * (ac - 1));
	if (!stack)
		return (false);
	tmp = malloc(sizeof(t_stack *) * (ac - 1));
	if (!tmp)
		return (free(stack), 1);
	head = stack;
	while (i < ac - 1)
	{
		stack[i].value = ft_atoi(av[i + 1]);
		stack[i].next = stack + i + 1;
		stack[i].prev = stack + i - 1;
		stack[i].lis = false;
		tmp[i] = stack + i;
		i++;
	}
	garbage = stack;
	stack[i - 1].next = stack;
	stack[0].prev = stack + i - 1;
	int curr = 0;
	int stack_size = ac -1;
	while (curr < stack_size)
	{
		ft_printf("%i\n", stack->value);
		stack = stack->next;
		curr++;
	}
	ft_printf("Paaaaauuuuuse1\n");
	my_qsort(tmp, 0, ac - 2);
	head = garbage;
	curr = 0;
	stack = garbage;
	while (curr < stack_size)
	{

		tmp[curr]->value_sorted = curr;
		curr++;
	}
	lis(head, ac - 1);
	free(tmp);
	t_stack *b = NULL;
	void	*end = stack;
	curr = 0;
	while (!curr++ || stack != end)
	{
		if (!stack->lis)
			p_stack(&stack, &b, stack_b);
		else
		{
			ft_printf("%i\n", stack->value);
			stack = stack->next;
		}
	}
	free(garbage);
	return (0);
}
