/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_ops_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 21:52:52 by asasada           #+#    #+#             */
/*   Updated: 2022/12/19 23:16:43 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

void	op_sa(t_info *info)
{
	swap(&(info->stack_a));
}

void	op_sb(t_info *info)
{
	swap(&(info->stack_b));
}

void	op_pa(t_info *info)
{
	t_elem	*popped;

	popped = pop_elem(&(info->stack_b));
	if (popped == NULL)
		return ;
	elem_add_front(popped, &(info->stack_a));
}

void	op_pb(t_info *info)
{
	t_elem	*popped;

	popped = pop_elem(&(info->stack_a));
	if (popped == NULL)
		return ;
	elem_add_front(popped, &(info->stack_b));
}
