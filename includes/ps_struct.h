#ifndef PS_STRUCT_H

#include <stdbool.h>

typedef struct s_stack
{
	int				value;
	unsigned int	value_sorted;
	bool			lis;
	struct s_stack	*next;
	struct s_stack	*prev;
}	t_stack;

enum e_stack
{
	stack_a,
	stack_b
};

void	my_qsort(t_stack **arr, int left, int right);

#endif // PS_STRUCT_H
