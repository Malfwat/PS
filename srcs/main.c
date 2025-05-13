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
	lis(stack, ac - 1);
	return (free(tmp), stack);
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


t_stack	*biggest_smaller(t_stack *stack, unsigned int index)
{
	int	go;
	t_stack	*node;
	void	*end;

	go = 1;
	end = stack;
	node = NULL;
	while (stack != end || go--)
	{
		if (stack->index < index && (!node || stack->index > node->index))
			node = stack;
		stack = stack->next;
	}
	if (node)
		return (node);
	go = 1;
	while (stack != end || go--)
	{
		if (!node || node->index < stack->index)
			node = stack;
		stack = stack->next;
	}
	return (node);
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

bool  is_sorted(t_stack *stack)
{
	unsigned int	tmp;
	void			*end;

	end = stack;
	tmp = 0;
	while (stack != end || !tmp)
	{
		if (stack->index < tmp)
			return (false);
		tmp = stack->index;
		stack = stack->next;
	}
	return (true);
}

t_pair	get_pair(t_stack *stacks[2], t_stack *node, t_stack *(*find)(t_stack *, unsigned int), bool from)
{
	void	*mate;
	t_pair	pair;

	if (from == FROM_B)
	{
		mate = find(stacks[stack_a], node->index);
		pair.stack_b = get_cost(stacks[stack_b], node);
		pair.stack_a = get_cost(stacks[stack_a], mate);
		return (pair);
	}
	mate = find(stacks[stack_b], node->index);
	pair.stack_b = get_cost(stacks[stack_b], mate);
	pair.stack_a = get_cost(stacks[stack_a], node);
	return (pair);
}

unsigned int	biggest_cost(unsigned int a, unsigned int b)
{
	if (a > b)
		return (a);
	return (b);
}

unsigned int min_cost(t_target target)
{
	if (target.direction == up)
		return (target.cost_up);
	return (target.cost_down);
}

unsigned int pair_cost(t_pair pair, u_int8_t *final_direction)
{
	unsigned int	cost;
	unsigned int	tmp;

	cost = biggest_cost(pair.stack_a.cost_up, pair.stack_b.cost_up);
	*final_direction = UP;
	tmp = biggest_cost(pair.stack_a.cost_down, pair.stack_b.cost_down);
	if (cost > tmp)
	{
		cost = tmp;
		*final_direction = DOWN;
	}
	tmp = min_cost(pair.stack_a) + min_cost(pair.stack_b);
	if (cost > tmp)
	{
		cost = tmp;
		*final_direction = SEPARATE;
	}
	return (cost + 1);
}

void	find_best_pair(t_stack *stacks[2])
{
	(void)stacks;
}

void	print_stacks_side_by_side(t_stack *a, t_stack *b);

bool	is_all_lis(t_stack *head)
{
	int		go;
	void	*end;

	go = 1;
	end = head;
	while (head != end || go--)
	{
		if (!head->lis)
			return (false);
		head = head->next;
	}
	return (true);
}

void	put_first_elem(t_stack *stacks[2], int size)
{
	u_int8_t	dir;
	int			i;

	i = 0;
	if (!size)
		return ;
	while (i < size)
	{
		if (stacks[stack_a][i].lis == 0)
		{
			dir = UP;
			break ;
		}
		else if (stacks[stack_a][size - i - 1].lis == 0)
		{
			dir = DOWN;
			break ;
		}
		i++;
	}
	while (i-- >= 0)
	{
		if (dir == UP)
			rotate(stacks, stacks + 1, stack_a);
		else if (dir == DOWN)
			rrotate(stacks, stacks + 1, stack_a);
	}
	p_stack(stacks, stacks + 1, push_to_b);
}

bool	is_not_lis(t_stack *node)
{
	return (!node->lis);
}

bool	is_non_null(void *ptr)
{
	return (ptr != 0);
}


t_pair	get_best_pair(t_stack *stacks[2], \
					bool (*is_pushable)(t_stack *), \
					t_stack *(*find)(t_stack *, unsigned int), \
					bool from)
{
	t_stack			*it;
	void			*end;
	t_pair			best;
	t_pair			tmp;
	unsigned int	cost;

	cost = (unsigned int)-1;
	it = stacks[from];

	end = it;
	while (it != end || cost == (unsigned int)-1)
	{
		if (is_pushable(it))
		{
			tmp = get_pair(stacks, it, find, from);
			if (pair_cost(tmp, &tmp.dir) < cost)
			{
				best = tmp;
				cost = pair_cost(best, &best.dir);
			}
		}
		it = it->next;
	}
	return (best);
}

void	put_to_top(t_stack *stacks[2], t_pair pair)
{
	while (pair.stack_a.node != stacks[stack_a])
	{
		if (pair.stack_a.direction == up)
			rotate(stacks, stacks + 1, stack_a);
		else
			rrotate(stacks, stacks + 1, stack_a);
	}
	while (pair.stack_b.node != stacks[stack_b])
	{
		if (pair.stack_b.direction == up)
			rotate(stacks, stacks + 1, stack_b);
		else
			rrotate(stacks, stacks + 1, stack_b);
	}
}

void	join_pair(t_stack *stacks[2], t_pair pair, u_int8_t dir, enum e_push push_to)
{
	if (dir == UP)
	{
		while (stacks[stack_a] != pair.stack_a.node && stacks[stack_b] != pair.stack_b.node)
			rotate(stacks, stacks + 1, both);
	}
	else if (dir == DOWN)
	{
		while (stacks[stack_a] != pair.stack_a.node && stacks[stack_b] != pair.stack_b.node)
			rrotate(stacks, stacks + 1, both);
	}
	put_to_top(stacks, pair);
	if (push_to == push_to_a)
		p_stack(stacks + 1, stacks, push_to);
	else
	{
		if (stacks[stack_b]->next != stacks[stack_b])
		{
			rotate(stacks, stacks + 1, stack_b);
			p_stack(stacks, stacks + 1, push_to);
		}
		else
			p_stack(stacks, stacks + 1, push_to);
	}
}

void	init_stack_b(t_stack *stacks[2], int size)
{
	t_pair	pair;

	put_first_elem(stacks, size);
	while (!is_all_lis(stacks[stack_a]))
	{
		pair = get_best_pair(stacks, is_not_lis, smallest_bigger, FROM_A);
		join_pair(stacks, pair, pair.dir, push_to_b);
	}
}

void	resolve(t_stack *stacks[2])
{
	t_pair		pair;
	t_target	first;
	t_stack		*tmp;
	void (*mv)(t_stack **, t_stack **, enum e_stack);

	while (stacks[stack_b])
	{
		pair = get_best_pair(stacks, is_not_lis, smallest_bigger, FROM_B);
		join_pair(stacks, pair, pair.dir, push_to_a);
	}
	tmp = stacks[stack_a];
	while (tmp->index != 0)
		tmp = tmp->next;
	first = get_cost(stacks[stack_a], tmp);
	if (first.direction == up)
		mv = rotate;
	else 
		mv = rrotate;
	while (stacks[stack_a]->index != 0)
		mv(stacks, stacks + 1, stack_a);
}

int	main(int ac, char **av)
{
	t_stack	*stacks[2];
	void	*garbage;

	if (ac < 2)
		return (ft_putendl_fd("Gimme some number", 2), 1);
	stacks[stack_a] = init_stack_a(ac, av);
	if (is_sorted(stacks[stack_a]))
		return (ft_putendl_fd("Already sorted", 1), free(*stacks), 0);
	if (!stacks[stack_a])
		return (ft_putendl_fd("Something wrong with your input", 2), 1);
	garbage = *stacks;
	stacks[stack_b] = 0;
	init_stack_b(stacks, ac - 1);
	resolve(stacks);
	print_stacks_side_by_side(stacks[stack_a], stacks[stack_b]);
	free(garbage);
	return (0);
}
