/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_few.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:38:15 by asasada           #+#    #+#             */
/*   Updated: 2022/12/18 15:40:11 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	assign_tmp_pos(t_elem *stack)
{
	t_elem	*tmp1;
	t_elem	*tmp2;
	size_t	pos;

	tmp2 = stack;
	while (true)
	{
		tmp1 = stack;
		pos = 0;
		while (true)
		{
			if (tmp1->pos < tmp2->pos)
				pos++;
			if (tmp1->is_end == true)
				break ;
			tmp1 = tmp1->next;
		}
		tmp2->tmp_pos = pos;
		if (tmp2->is_end == true)
			break ;
		tmp2 = tmp2->next;
	}
}

void	sort_3_or_less(t_info *info, int arg_count)
{
	if (arg_count == 2)
		op_ra(info);
	else
	{
		assign_tmp_pos(info->stack_a);
		if (info->stack_a->tmp_pos == 0)
		{
			op_rra(info);
			op_sa(info);
		}
		else if (info->stack_a->tmp_pos == 1 && info->stack_a->next->tmp_pos == 0)
			op_sa(info);
		else if (info->stack_a->tmp_pos == 1 && info->stack_a->next->tmp_pos == 2)
			op_rra(info);
		else if (info->stack_a->next->tmp_pos == 1)
		{
			op_sa(info);
			op_rra(info);
		}
		else
			op_ra(info);
	}
}

void	sort_4_to_6(t_info *info, int arg_count)
{
	size_t	ra;
	size_t	rra;

	// print_stacks(info->stack_a, info->stack_b, false);
	while (arg_count-- > 3)
		op_pb(info);
	// print_stacks(info->stack_a, info->stack_b, false);
	if (is_sorted(info->stack_a) != true)
		sort_3_or_less(info, 3);
	// print_stacks(info->stack_a, info->stack_b, false);
	while (info->stack_b != NULL)
		move_elem_b(info, info->stack_b);
	// print_stacks(info->stack_a, info->stack_b, false);
	ra = index_of_stack(info->stack_a, stackminnum(info->stack_a));
	rra = stacklen(info->stack_a) - ra;
	if (ra > rra)
		while (rra-- > 0)
			op_rra(info);
	else
		while (ra-- > 0)
			op_ra(info);
	// print_stacks(info->stack_a, info->stack_b, false);
	// push 1 or 2 depending on argc to stack b
	// sort stack a with sort 3 or less
	// push everything in stack b back to stack a
}

void	sort_few(t_info *info, int arg_count)
{
	if (arg_count <= 3)
		sort_3_or_less(info, arg_count);
	else
		sort_4_to_6(info, arg_count);
}