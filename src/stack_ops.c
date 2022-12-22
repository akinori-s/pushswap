/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 16:13:10 by asasada           #+#    #+#             */
/*   Updated: 2022/12/22 20:16:29 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
		next->is_end = false;
	if (next->is_end == true)
		elem->is_end = true;
	*stack = next;
}

t_elem	*pop_elem(t_elem **stack)
{
	t_elem	*prev;
	t_elem	*next;
	t_elem	*elem;

	if (stack == NULL)
		return (NULL);
	if (*stack == NULL)
		return (NULL);
	elem = *stack;
	prev = elem->prev;
	next = elem->next;
	prev->next = next;
	next->prev = prev;
	if (elem->is_end != true)
		*stack = next;
	else
		*stack = NULL;
	elem->is_end = false;
	return (elem);
}

void	rotate_stack(t_elem **stack)
{
	if (stack == NULL)
		return ;
	if (*stack == NULL)
		return ;
	(*stack)->prev->is_end = false;
	(*stack)->is_end = true;
	*stack = (*stack)->next;
}

void	rev_rotate_stack(t_elem **stack)
{
	if (stack == NULL)
		return ;
	if (*stack == NULL)
		return ;
	(*stack)->prev->is_end = false;
	(*stack)->prev->prev->is_end = true;
	*stack = (*stack)->prev;
}
