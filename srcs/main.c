#include "libftprintf.h"
#include "ps_struct.h"

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

int	binary_search(t_stack *tab, int *tail, int length, int key)
{
	int	low;
	int	high;
	int	mid;

	low = 0;
	high = length - 1;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if ((int)tab[tail[mid]].index < key)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return (low);
}

void	initialize_tabs(int arr[2][MAX_LIS], int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		arr[previous][i] = -1;
		arr[tails][i] = 0;
		i++;
	}
}

void	lis(t_stack *tab, int size)
{
	int	arr[2][MAX_LIS];
	int	i;
	int	len;
	int	pos;
	int	lis_index;

	initialize_tabs(arr, MAX_LIS);
	len = 0;
	i = -1;
	while (++i < size)
	{
		pos = binary_search(tab, arr[tails], len, tab[i].index);
		arr[tails][pos] = i;
		if (pos > 0)
			arr[previous][i] = arr[tails][pos - 1];
		if (pos == len)
			len++;
	}
	lis_index = arr[tails][len - 1];
	while (len-- > 0)
	{
		tab[lis_index].lis = true;
		lis_index = arr[previous][lis_index];
	}
}

void	fill_data(t_stack **arr, t_stack *stack, char **av, int i)
{
	stack[i].value = ft_atoi(av[i + 1]);
	stack[i].next = stack + i + 1;
	stack[i].prev = stack + i - 1;
	stack[i].lis = false;
	arr[i] = stack + i;
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
		fill_data(tmp, stack, av, i++);
	stack[i - 1].next = stack;
	stack[0].prev = stack + i - 1;
	my_qsort(tmp, 0, ac - 2);
	i = -1;
	while (++i < ac - 1)
		tmp[i]->index = i;
	return (free(tmp), stack);
}

void	init_stack_b(t_stack *stacks[2], int size)
{
	void	*end;
	int		curr;

	lis(stacks[stack_a], size);
	stacks[stack_b] = NULL;
	end = stacks[stack_a];
	curr = 0;
	while (stacks[stack_a] != end || !curr++)
	{
		if (!stacks[stack_a]->lis)
			p_stack(stacks, stacks + 1, push_to_b);
		else
			rotate(stacks, stacks + stack_b, stack_a);
	}
}

int	main(int ac, char **av)
{
	t_stack	*stacks[2];
	void	*garbage;

	stacks[stack_a] = init_stack_a(ac, av);
	garbage = *stacks;
	init_stack_b(stacks, ac - 1);
	free(garbage);
	return (0);
}
