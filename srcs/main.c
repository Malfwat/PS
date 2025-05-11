#include "libftprintf.h"
#include "ps_struct.h"
#include "ps.h"

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

int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (false);
		i++;
	}
	return (true);
}

bool	fill_data(t_stack **arr, t_stack *stack, char **av, int i)
{
	if (!ft_isnumber(av[i + 1]))
		return (false);
	stack[i].value = ft_atoi(av[i + 1]);
	stack[i].next = stack + i + 1;
	stack[i].prev = stack + i - 1;
	stack[i].lis = false;
	arr[i] = stack + i;
	return (true);
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
		if (!fill_data(tmp, stack, av, i++))
			return (free(stack), free(tmp), NULL);
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
	int	go;
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

t_target	get_cost(t_stack *stack, t_stack *node)
{
	unsigned int	size;
	unsigned int	pos;
	t_target		target;

	size = stack_size(stack);
	pos = get_position(stack, node);
	target.node = node;
	if (pos < size - pos)
		target.direction = up;
	else
		target.direction = down;
	target.cost_down = size - pos;
	target.cost_up = pos;
	return (target);
}

int	main(int ac, char **av)
{
	t_stack	*stacks[2];
	void	*garbage;

	stacks[stack_a] = init_stack_a(ac, av);
	if (!stacks[stack_a])
		return (ft_putendl_fd("Something wrong with your input", 2), 1);
	garbage = *stacks;
	init_stack_b(stacks, ac - 1);

	t_target	target = get_cost(stacks[stack_b], stacks[stack_b]->next->next);
	ft_printf("value: %i\tcost_up: %u\tcost_down: %u\tdirection: %s\n", target.node->value, target.cost_up, target.cost_down, (char *[]){"up", "down"}[target.direction]);
	free(garbage);
	return (0);
}
