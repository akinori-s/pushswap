/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 20:18:39 by asasada           #+#    #+#             */
/*   Updated: 2022/12/22 20:18:53 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
