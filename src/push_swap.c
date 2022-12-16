/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:43:44 by asasada           #+#    #+#             */
/*   Updated: 2022/12/16 21:39:55 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"


static void	mark_lis_elems(t_elem *start, t_info *info)
{
	size_t	j;
	t_elem	*prev;

	j = 0;
	prev = start;
	start->lis = true;
	while (prev && prev->is_end == false && j < info->lis_head->lis_len)
	{
		if (prev->lis_len + 1 == start->lis_len)
		{
			prev->lis = true;
			prev->need_sort = false;
			info->need_sort_count -= 1;
			start = prev;
			j++;
		}
		prev = prev->prev;
	}
}

static int	calc_elem_lis_count(t_elem *start)
{
	size_t	lis_len;
	t_elem	*prev;

	lis_len = 0;
	prev = start->prev;
	while (prev && prev->is_end == false)
	{
		if (prev->pos < start->pos)
		{
			if (prev->lis_len > lis_len)
				lis_len = prev->lis_len;
		}
		prev = prev->prev;
	}
	return (lis_len + 1);
}

void	calc_longest_increasing_subsequence(t_info *info)
{
	t_elem	*next;

	if (!info->stack_a)
		return ;
	next = info->stack_a;
	info->lis_head = info->stack_a;
	while (next)
	{
		next->need_sort = true;
		info->need_sort_count += 1;

		next->lis = false;
		next->lis_len = calc_elem_lis_count(next);
		if (next->lis_len > info->lis_head->lis_len)
			info->lis_head = next;
		if (next->is_end == true)
			break ;
		next = next->next;
	}
	mark_lis_elems(info->lis_head, info);
}

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

void	flag_non_increasing_nums(t_info *info, t_elem *stack)
{
	t_elem	*tmp;
	size_t	current_max;
	size_t	current_min;

	current_max = 0;
	current_min = info->max;
	tmp = stack;
	while (true)
	{
		if (tmp->pos > current_max)
			current_max = tmp->pos;
		if (tmp->pos < current_min)
			current_min = tmp->pos;
		if (info->max_pos == current_max && tmp->pos < current_min)
		{
			tmp->need_sort = true;
			info->need_sort_count += 1;
		}
		else if (tmp->pos < current_max)
		{
			tmp->need_sort = true;
			info->need_sort_count += 1;
		}
		if (tmp->is_end == true)
			break ;
		tmp = tmp->next;
	}
}

// =============================================================================

long	stackmax(t_elem *stack)
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

long	stackmin(t_elem *stack)
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

// =============================================================================

void	do_move_elem(t_info *info, t_cost *cost)
{
	size_t	i;

	i = 0;
	while (i < cost->ra)
	{
		op_ra(info);
		i++;
	}
	i = 0;
	while (i < cost->rb)
	{
		op_rb(info);
		i++;
	}
	i = 0;
	while (i < cost->rra)
	{
		op_rra(info);
		i++;
	}
	i = 0;
	while (i < cost->rrb)
	{
		op_rrb(info);
		i++;
	}
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
	min_dist = stackmax(to);
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

	max = stackmax(to);
	min = stackmin(to);
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

void	do_move_elem_b(t_info *info, t_cost *cost)
{
	size_t	i;

	i = 0;
	while (i < cost->ra)
	{
		op_rb(info);
		i++;
	}
	i = 0;
	while (i < cost->rb)
	{
		op_ra(info);
		i++;
	}
	i = 0;
	while (i < cost->rra)
	{
		op_rrb(info);
		i++;
	}
	i = 0;
	while (i < cost->rrb)
	{
		op_rra(info);
		i++;
	}
	op_pa(info);
}

long	calc_pos_bigger_b(t_info *info, t_elem *to, t_elem *elem)
{
	t_elem	*tmp;
	size_t	i;
	long	min_dist;
	long	min_dist_pos;

	(void)info;
	if (to == NULL)
		return (0);
	tmp = to;
	min_dist = stackmax(to);
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
	return (min_dist_pos);
}

size_t	calc_dest_index_b(t_info *info, t_elem *to, t_elem *elem)
{
	long	max;
	long	min;
	size_t	index_max;
	size_t	index_min;

	max = stackmax(to);
	min = stackmin(to);
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
	if (cost_tmp.cost < cost->cost || cost->cost == 0)
		copy_cost(cost, &cost_tmp);
}

void	move_elem_b(t_info *info, t_elem *from)
{
	t_elem	*tmp;
	t_cost	cost;

	cost = (t_cost){0};
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

// =============================================================================

void	push_n_swap(t_info *info)
{
	size_t	ra;
	size_t	rra;

	while (info->need_sort_count > 0)
	{
		move_elem(info, info->stack_a);
		info->need_sort_count -= 1;
	}
	while (info->stack_b != NULL)
	{
		move_elem_b(info, info->stack_b);
	}
	ra = index_of_stack(info->stack_a, stackmin(info->stack_a));
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

bool	op_is_push_swap(int	op)
{
	if (op <= 5)
		return (true);
	return (false);
}

// =============================================================================

void	join_rr(t_info *info, size_t i, size_t n)
{
	t_list	*tmp;
	size_t	rra;
	size_t	rrb;

	tmp = info->ops;
	rra = 0;
	while (rra++ < i)
		tmp = tmp->next;
	rra = 0;
	rrb = 0;
	while ((rra < n || rrb < n) && tmp != NULL)
	{
		if (*(int*)tmp->content == OP_RRA && rra < n)
		{
			*(int*)tmp->content = OP_RRR;
			rra++;
			tmp = tmp->next;
		}
		else if (*(int*)tmp->content == OP_RRB && rrb < n)
		{
			*(int*)tmp->content = OP_NONE;
			rrb++;
		}
		else
			tmp = tmp->next;
	}
}

void	join_r(t_info *info, size_t i, size_t n)
{
	t_list	*tmp;
	size_t	ra;
	size_t	rb;

	tmp = info->ops;
	ra = 0;
	while (ra++ < i)
		tmp = tmp->next;
	ra = 0;
	rb = 0;
	while ((ra < n || rb < n) && tmp != NULL)
	{
		if (*(int*)tmp->content == OP_RA && ra < n)
		{
			*(int*)tmp->content = OP_RR;
			ra++;
			tmp = tmp->next;
		}
		else if (*(int*)tmp->content == OP_RB && rb < n)
		{
			*(int*)tmp->content = OP_NONE;
			rb++;
		}
		else
			tmp = tmp->next;
	}
}

int	join_rev_rotates(t_info *info, size_t i, size_t j)
{
	t_list	*tmp;
	size_t	rra;
	size_t	rrb;
	size_t	t;

	tmp = info->ops;
	rra = 0;
	rrb = 0;
	t = 0;
	while (t++ < i)
		tmp = tmp->next;
	t = 0;
	while (t++ < j)
	{
		if (*(int*)tmp->content == OP_RRA)
			rra++;
		else if (*(int*)tmp->content == OP_RRB)
			rrb++;
		tmp = tmp->next;
	}
	if (min_st(rra, rrb) == 0)
		return (0);
	join_rr(info, i, min_st(rra, rrb));
	return (1);
}

int	join_rotates(t_info *info, size_t i, size_t j)
{
	t_list	*tmp;
	size_t	ra;
	size_t	rb;
	size_t	t;

	tmp = info->ops;
	ra = 0;
	rb = 0;
	t = 0;
	while (t++ < i)
		tmp = tmp->next;
	t = 0;
	while (t++ < j)
	{
		if (*(int*)tmp->content == OP_RA)
			ra++;
		else if (*(int*)tmp->content == OP_RB)
			rb++;
		tmp = tmp->next;
	}
	if (min_st(ra, rb) == 0)
		return (0);
	join_r(info, i, min_st(ra, rb));
	return (1);
}

void	compress_ops(t_info *info)
{
	size_t	i;
	size_t	j;
	t_list	*tmp;

	i = 0;
	tmp = info->ops;
	while (tmp != NULL)
	{
		j = 0;
		while (tmp != NULL && !op_is_push_swap(*(int*)tmp->content))
		{
			j++;
			tmp = tmp->next;
		}
		if (tmp != NULL)
		{
			if (join_rotates(info, i, j) == 1 || join_rev_rotates(info, i, j) == 1)
			{
				tmp = info->ops;
				i = 0;
				continue ;
			}
			i += j + 1;
			tmp = tmp->next;
		}
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
*/
