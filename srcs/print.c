#include "ps_struct.h"
#include "libftprintf.h"

void	print_stacks_side_by_side(t_stack *a, t_stack *b)
{
	t_stack	*start_a = a;
	t_stack	*start_b = b;
	int		end_a = !a;
	int		end_b = !b;

	ft_printf("   Stack A\t\tStack B\n");
	ft_printf("-------------------------------\n");

	while (!end_a || !end_b)
	{
		if (!end_a)
		{
			ft_printf("  val: %2d idx: %2u lis: %2d\t",
				a->value, a->index, a->lis);
			a = a->next;
			if (a == start_a)
				end_a = 1;
		}
		else
			ft_printf("  (empty)\t\t");

		if (!end_b)
		{
			ft_printf("val: %2d idx: %2u lis: %2d\n",
				b->value, b->index, b->lis);
			b = b->next;
			if (b == start_b)
				end_b = 1;
		}
		else
			ft_printf("(empty)\n");
	}
}

