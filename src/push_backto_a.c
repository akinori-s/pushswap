/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_backto_a.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 21:47:21 by asasada           #+#    #+#             */
/*   Updated: 2022/12/16 23:56:01 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	do_move_elem_b(t_info *info, t_cost *cost)
{
	size_t	i;

	i = 0;
	while (i++ < cost->ra)
		op_rb(info);
	i = 0;
	while (i++ < cost->rb)
		op_ra(info);
	i = 0;
	while (i++ < cost->rra)
		op_rrb(info);
	i = 0;
	while (i++ < cost->rrb)
		op_rra(info);
	op_pa(info);
}

long	calc_pos_bigger_b(t_info *info, t_elem *to, t_elem *elem)
{
	t_elem	*tmp;
	size_t	i;
	size_t	min;
	size_t	min_pos;

	min = info->stack_t_len;
	if (to == NULL)
		return (0);
	tmp = to;
	i = 0;
	while (true)
	{
		if (elem->pos < tmp->pos && tmp->pos - elem->pos < min)
		{
			min = tmp->pos - elem->pos;
			min_pos = i;
		}
		if (tmp->is_end == true)
			break ;
		tmp = tmp->next;
		i++;
	}
	return (min_pos);
}

size_t	calc_dest_index_b(t_info *info, t_elem *to, t_elem *elem)
{
	long	max;
	long	min;
	size_t	index_max;
	size_t	index_min;

	max = stackmaxnum(to);
	min = stackminnum(to);
	index_max = index_of_stack(to, max);
	index_min = index_of_stack(to, min);
	if (elem->num > max)
		return (index_max + 1);
	if (elem->num < min)
		return (index_min);
	return (calc_pos_bigger_b(info, to, elem));
}

void	calc_cost_b(t_cost *cost, t_elem *elem, t_info *info)
{
	size_t	index;
	size_t	to_pos;
	t_cost	cost_tmp;

	cost_tmp = (t_cost){0};
	index = index_of_stack(info->stack_b, elem->num);
	cost_tmp.ra = index;
	cost_tmp.rra = stacklen(info->stack_b) - index;
	to_pos = calc_dest_index_b(info, info->stack_a, elem) % stacklen(info->stack_a);
	cost_tmp.rb = to_pos;
	cost_tmp.rrb = stacklen(info->stack_a) - to_pos;
	cost_tmp.cost = calc_min_cost(&cost_tmp);
	if (cost_tmp.cost < cost->cost)
		copy_cost(cost, &cost_tmp);
}

void	move_elem_b(t_info *info, t_elem *from)
{
	t_elem	*tmp;
	t_cost	cost;

	cost = (t_cost){0};
	cost.cost = stacklen(info->stack_a) + stacklen(info->stack_b);
	tmp = from;
	while (true)
	{
		if (tmp->need_sort == true)
			calc_cost_b(&cost, tmp, info);
		if (tmp->is_end == true)
			break;
		tmp = tmp->next;
	}
	do_move_elem_b(info, &cost);
}
