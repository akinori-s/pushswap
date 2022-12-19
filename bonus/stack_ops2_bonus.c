/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_ops2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 21:57:44 by asasada           #+#    #+#             */
/*   Updated: 2022/12/19 23:17:03 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

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
