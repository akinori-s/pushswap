/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_ops_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 21:51:39 by asasada           #+#    #+#             */
/*   Updated: 2022/12/18 21:57:55 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

void	swap(t_elem **stack)
{
	t_elem	*elem;
	t_elem	*next;

	if (stack == NULL)
		return ;
	if (*stack == NULL)
		return ;
	elem = *stack;
	if (elem->is_end || elem->next == NULL)
		return ;
	next = elem->next;
	if (stacklen(*stack) > 2)
	{
		next->prev = elem->prev;
		elem->next = next->next;
		elem->prev->next = next;
		next->next->prev = elem;
	}
	elem->prev = next;
	next->next = elem;
	if (next->is_end == true)
	{
		next->is_end = false;
		elem->is_end = true;
	}
	*stack = next;
}

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
