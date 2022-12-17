/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:43:44 by asasada           #+#    #+#             */
/*   Updated: 2022/12/17 12:41:16 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// =============================================================================

void	get_stack_info(t_info *info)
{
	size_t	stack_len;
	size_t	median_index;
	size_t	i;
	t_elem	*tmp;

	stack_len = stacklen(info->stack_t);
	median_index = stack_len / 2;
	i = 0;
	tmp = info->stack_t;
	while (i < median_index)
	{
		tmp = tmp->next;
		i++;
	}
	info->median = tmp->num;
	info->min = info->stack_t->num;
	info->max = info->stack_t->prev->num;
	info->max_pos = info->stack_t->prev->pos;
	info->stack_t_len = stack_len;
}

// =============================================================================

void	do_move_elem(t_info *info, t_cost *cost)
{
	size_t	i;

	i = 0;
	while (i++ < cost->ra)
		op_ra(info);
	i = 0;
	while (i++ < cost->rb)
		op_rb(info);
	i = 0;
	while (i++ < cost->rra)
		op_rra(info);
	i = 0;
	while (i++ < cost->rrb)
		op_rrb(info);
	op_pb(info);
}

long	calc_pos_bigger(t_info *info, t_elem *to, t_elem *elem)
{
	t_elem	*tmp;
	size_t	i;
	long	min_dist;
	long	min_dist_pos;

	(void)info;
	if (to == NULL)
		return (0);
	tmp = to;
	min_dist = stackmaxnum(to);
	i = 0;
	min_dist_pos = 0;
	while (true)
	{
		if (tmp->pos > elem->pos && abs_long(tmp->pos - elem->pos) < min_dist)
		{
			min_dist = tmp->pos - elem->pos;
			min_dist_pos = i;
		}
		if (tmp->is_end == true)
			break ;
		tmp = tmp->next;
		i += 1;
	}
	min_dist_pos++;
	return (min_dist_pos);
}

size_t	calc_dest_index(t_info *info, t_elem *to, t_elem *elem)
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
		return (index_max);
	if (elem->num < min)
		return (index_min + 1);
	return (calc_pos_bigger(info, to, elem));
}

void	calc_cost(t_cost *cost, t_elem *elem, t_info *info)
{
	size_t	index;
	size_t	to_pos;
	t_cost	cost_tmp;

	cost_tmp = (t_cost){0};
	index = index_of_stack(info->stack_a, elem->num);
	cost_tmp.ra = index;
	cost_tmp.rra = stacklen(info->stack_a) - index;
	to_pos = calc_dest_index(info, info->stack_b, elem) % stacklen(info->stack_b);
	cost_tmp.rb = to_pos;
	cost_tmp.rrb = stacklen(info->stack_b) - to_pos;
	cost_tmp.cost = calc_min_cost(&cost_tmp);
	if (cost_tmp.cost < cost->cost || cost->cost == 0)
		copy_cost(cost, &cost_tmp);
}

void	move_elem(t_info *info, t_elem *from)
{
	t_elem	*tmp;
	t_cost	cost;

	cost = (t_cost){0};
	tmp = from;
	while (true)
	{
		if (tmp->need_sort == true)
			calc_cost(&cost, tmp, info);
		if (tmp->is_end == true)
			break;
		tmp = tmp->next;
	}
	do_move_elem(info, &cost);
}

// =============================================================================

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
			tmp->need_sort = true;
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
	q2 = info->stack_t_len / 2;
	q3 = info->stack_t_len / 4 * 3;
	// ft_printf("====%d, %d, %d=====\n", q1, q2, q3);
	// print_stacks(info->stack_a, info->stack_b, true);
	quick_sort_1(info, q2, q3);
	// print_stacks(info->stack_a, info->stack_b, false);
	quick_sort_1(info, 0, q1);
	// print_stacks(info->stack_a, info->stack_b, false);

}

// =============================================================================

void	push_n_swap(t_info *info)
{
	size_t	ra;
	size_t	rra;

	quick_sort_to_b(info);
	// exit(0);
	// move to b
	// while (info->need_sort_count > 0 && stacklen(info->stack_a) > 2)
	// {
	// 	move_elem(info, info->stack_a);
	// 	info->need_sort_count -= 1;
	// }
	// --move to b
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


// =============================================================================

void	inputs_to_stack(t_info *info, t_elem **stack, int argc, char **argv)
{
	int		i;
	int		err;
	long	num;
	t_elem	*tmp;

	i = 1;
	err = 0;
	while (i < argc)
	{
		num = ft_atoi(argv[i]);
		if (err)
			clean_exit(info, ERROR);
		tmp = new_elem(num);
		if (tmp == NULL)
			clean_exit(info, ERROR);
		elem_add_back(tmp, stack);
		i++;
	}
}

// =============================================================================

int	main(int argc, char **argv)
{
	t_info	info;

	info = (t_info){0};
	inputs_to_stack(&info, &(info.stack_a), argc, argv);
	inputs_to_stack(&info, &(info.stack_t), argc, argv);

	sort_tmp_stack(info.stack_t);
	get_stack_info(&info);

	map_sorted_to_stack(info.stack_t, info.stack_a, stacklen(info.stack_t));
	op_pb(&info);
	info.stack_b->need_sort = true;
	op_pb(&info);
	info.stack_b->need_sort = true;
	calc_longest_increasing_subsequence(&info);
	push_n_swap(&info);
	compress_ops(&info);

	print_ops(info.ops, false);

	clean_exit(&info, 0);
	return (0);
}

/*
TODO
---

1. delete the printer function, both .c and from the header file
2. add error handling
3. add sorting for numbers that are 5 or less
*/
