#include <stdio.h>
#include "ps_struct.h"

void	stack_swap(t_stack **a, t_stack **b)
{
	t_stack	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	partitionning(t_stack **arr, int left, int right)
{
	int i;
	int	j;
	t_stack	*pivot;

	i = left - 1;
	j = left;
	pivot = arr[right];
	while (j < right)
	{
		if (pivot->value >= arr[j]->value)
		{
			i++;
			stack_swap(arr + i, arr + j);
		}
		j++;
	}
	stack_swap(arr + i + 1, arr + right);
	return (i + 1);
}

void	my_qsort(t_stack **arr, int left, int right)
{
	int	pi;

	if (left < right)
	{
		pi = partitionning(arr, left, right);

		my_qsort(arr, left, pi - 1);
		my_qsort(arr, pi + 1, right);
	}
}
