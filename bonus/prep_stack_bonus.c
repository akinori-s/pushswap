/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_stack_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 21:46:58 by asasada           #+#    #+#             */
/*   Updated: 2022/12/18 21:48:54 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

void	apply_arr_to_stack(long *arr, t_elem *stack)
{
	size_t	i;
	t_elem	*tmp;

	i = 0;
	tmp = stack;
	while (true)
	{
		tmp->num = arr[i];
		if (tmp->is_end)
			break ;
		tmp = tmp->next;
		i++;
	}
}

void	sort_long_arr(long *arr, size_t arr_size)
{
	size_t	i;
	size_t	j;
	long	tmp;

	i = 0;
	while (i < arr_size)
	{
		j = 0;
		while (j < arr_size - i - 1)
		{
			if (arr[j] > arr[j + 1])
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	sort_tmp_stack(t_elem *stack)
{
	size_t	i;
	size_t	len;
	long	*arr;
	t_elem	*tmp;

	len = stacklen(stack);
	arr = malloc(sizeof(long) * len);
	if (arr == NULL)
		return (-1);
	tmp = stack;
	i = 0;
	while (true)
	{
		arr[i] = tmp->num;
		if (tmp->is_end)
			break ;
		tmp = tmp->next;
		i++;
	}
	sort_long_arr(arr, len);
	apply_arr_to_stack(arr, stack);
	free(arr);
	return (0);
}

int	check_duplicates(t_elem	*sorted)
{
	t_elem	*tmp;

	if (sorted == NULL)
		return (-1);
	tmp = sorted;
	while (tmp->is_end != true)
	{
		if (tmp->num == tmp->next->num)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}
