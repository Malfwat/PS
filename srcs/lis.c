/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <admoufle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:57:53 by malfwa            #+#    #+#             */
/*   Updated: 2025/05/14 20:25:45 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps_struct.h"

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
