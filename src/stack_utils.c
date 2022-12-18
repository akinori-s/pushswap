/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 16:06:04 by asasada           #+#    #+#             */
/*   Updated: 2022/12/18 12:30:36 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_elem	*new_elem(long num)
{
	t_elem	*tmp;

	tmp = malloc(sizeof(t_elem));
	if (tmp == NULL)
		return (NULL);
	*tmp = (t_elem){0};
	tmp->num = num;
	return (tmp);
}

t_elem	*elem_at_index(t_elem **stack, size_t index)
{
	size_t	i;
	t_elem	*tmp;

	if (stack == NULL)
		return (0);
	if (*stack == NULL)
		return (0);
	i = 0;
	tmp = *stack;
	while (i < index - 1)
	{
		tmp = tmp->next;
		i++;
	}
	return (tmp);
}

size_t	index_of_stack(t_elem *stack, long num)
{
	size_t	i;
	t_elem	*tmp;

	if (stack == NULL)
		return (0);
	i = 0;
	tmp = stack;
	while (tmp->num != num && tmp->next != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

size_t	stacklen(t_elem *stack)
{
	size_t	i;
	t_elem	*tmp;

	if (stack == NULL)
		return (0);
	i = 1;
	tmp = stack;
	while (tmp->is_end != true && tmp->next != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

// =============================================================================

long	stackmaxnum(t_elem *stack)
{
	t_elem	*elem;
	long	max;

	elem = stack;
	max = LONG_MIN;
	while (true)
	{
		if (elem->num > max)
			max = elem->num;
		if (elem->is_end == true)
			break ;
		elem = elem->next;
	}
	return (max);
}

long	stackminnum(t_elem *stack)
{
	t_elem	*elem;
	long	min;

	elem = stack;
	min = LONG_MAX;
	while (true)
	{
		if (elem->num < min)
			min = elem->num;
		if (elem->is_end == true)
			break ;
		elem = elem->next;
	}
	return (min);
}