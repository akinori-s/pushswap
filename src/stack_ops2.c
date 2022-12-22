/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_ops2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 20:16:09 by asasada           #+#    #+#             */
/*   Updated: 2022/12/22 20:16:30 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	elem_add_back(t_elem *new, t_elem **stack)
{
	t_elem	*first;
	t_elem	*last;

	if (new == NULL || stack == NULL)
		return ;
	if (*stack == NULL)
	{
		*stack = new;
		new->next = new;
		new->prev = new;
		new->is_end = true;
		return ;
	}
	first = *stack;
	last = first->prev;
	new->prev = last;
	new->next = first;
	first->prev = new;
	last->next = new;
	last->is_end = false;
	new->is_end = true;
}

void	elem_add_front(t_elem *new, t_elem **stack)
{
	t_elem	*first;
	t_elem	*last;

	if (new == NULL || stack == NULL)
		return ;
	if (*stack == NULL)
	{
		*stack = new;
		new->next = new;
		new->prev = new;
		new->is_end = true;
		return ;
	}
	first = *stack;
	last = first->prev;
	new->prev = last;
	new->next = first;
	first->prev = new;
	last->next = new;
	*stack = new;
}
