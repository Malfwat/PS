#ifndef PS_STRUCT_H
# define PS_STRUCT_H

# include <stdbool.h>

# define MAX_LIS 2048
# define UP 1
# define DOWN 2
# define SEPARATE 3

enum e_stack
{
	stack_a,
	stack_b,
	both
};

enum e_push
{
	push_to_a,
	push_to_b
};

enum e_tab
{
	previous,
	tails
};

enum e_forward
{
	up,
	down
};

typedef struct s_stack
{
	int				value;
	unsigned int	index;
	bool			lis;
	struct s_stack	*next;
	struct s_stack	*prev;
}	t_stack;

typedef struct s_target
{
	t_stack			*node;
	unsigned int	cost_up;
	unsigned int	cost_down;
	enum e_forward	direction;
}t_target;

typedef t_target t_pair[2];

#endif // PS_STRUCT_H
