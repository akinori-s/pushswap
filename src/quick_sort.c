/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 09:40:22 by asasada           #+#    #+#             */
/*   Updated: 2022/12/22 09:40:40 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	quick_sort_1(t_info *info, size_t ax1_pos, size_t ax2_pos)
{
	t_elem	*tmp;
	size_t	stack_len;
	size_t	i;

	stack_len = stacklen(info->stack_a);
	tmp = info->stack_a;
	i = 0;
	while (i < stack_len)
	{
		while (!tmp->need_sort && i++ < stack_len)
		{
			op_ra(info);
			tmp = info->stack_a;
		}
		if (tmp->pos >= ax1_pos)
		{
			op_pb(info);
			if (tmp->pos > ax2_pos)
				op_rb(info);
		}
		else
			op_ra(info);
		tmp = info->stack_a;
		i++;
	}
}

void	quick_sort_to_b(t_info *info)
{
	size_t	q1;
	size_t	q2;
	size_t	q3;

	q1 = info->stack_t_len / 4;
	q2 = info->stack_t_len / 4 * 2;
	q3 = info->stack_t_len / 4 * 3;
	quick_sort_1(info, q2, q3);
	quick_sort_1(info, 0, q1);
}

void	push_n_swap(t_info *info)
{
	size_t	ra;
	size_t	rra;

	quick_sort_to_b(info);
	while (info->stack_b != NULL)
	{
		move_elem_b(info, info->stack_b);
	}
	ra = index_of_stack(info->stack_a, stackminnum(info->stack_a));
	rra = stacklen(info->stack_a) - ra;
	if (ra > rra)
		while (rra-- > 0)
			op_rra(info);
	else
		while (ra-- > 0)
			op_ra(info);
}
