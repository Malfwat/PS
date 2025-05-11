#ifndef PS_STRUCT_H
# define PS_STRUCT_H

# include <stdbool.h>

# define MAX_LIS 4096

typedef struct s_stack
{
	int				value;
	unsigned int	index;
	bool			lis;
	struct s_stack	*next;
	struct s_stack	*prev;
}	t_stack;

enum e_stack
{
	stack_a,
	stack_b
};

enum e_tab
{
	previous,
	tails
};

void	my_qsort(t_stack **arr, int left, int right);

#endif // PS_STRUCT_H
