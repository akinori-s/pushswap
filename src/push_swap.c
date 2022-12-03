/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:43:44 by asasada           #+#    #+#             */
/*   Updated: 2022/11/30 23:26:32 by asasada          ###   ########.fr       */
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

	stack_len = stacklen(&(info->stack_t));
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
	info->stack_t_len = stack_len;
}

void	flag_non_increasing_nums(t_info *info, t_elem *stack)
{
	t_elem	*tmp;
	size_t	current_max;

	current_max = 0;
	tmp = stack;
	while (true)
	{
		if (tmp->pos > current_max)
			current_max = tmp->pos;
		if (tmp->pos < current_max)
		{
			tmp->need_sort = true;
			info->need_sort_count += 1;
		}
		if (tmp->pos == info->stack_t_len - 1)
			current_max = 0;
		if (tmp->is_end == true)
			break ;
		tmp = tmp->next;
	}
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


void	calc_min_cost_tool(t_cost *c)
{
	if (c->ra + c->rrb < c->rra + c->rb)
	{
		c->rra = 0;
		c->rb = 0;
	}
	else if (c->ra + c->rrb > c->rra + c->rb)
	{
		c->ra = 0;
		c->rrb = 0;
	}
}

size_t	calc_min_cost(t_cost *c)
{
	size_t	cost_indiv;
	size_t	cost_r;
	size_t	cost_rr;

	cost_indiv = min_st(c->ra, c->rra) + min_st(c->rb, c->rrb);
	cost_r = max_st(c->ra, c->rb);
	cost_rr = max_st(c->rra, c->rrb);
	if (cost_r == min_st(cost_indiv, min_st(cost_r, cost_rr)))
	{
		c->rra = 0;
		c->rrb = 0;
	}
	else if (cost_rr == min_st(cost_indiv, min_st(cost_r, cost_rr)))
	{
		c->ra = 0;
		c->rb = 0;
	}
	else
		calc_min_cost_tool(c);
	return (min_st(cost_indiv, min_st(cost_r, cost_rr)));
}

void	copy_cost(t_cost *to, t_cost *from)
{
	to->cost = from->cost;
	to->ra = from->ra;
	to->rb = from->rb;
	to->rra = from->rra;
	to->rrb = from->rrb;
}

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

size_t	calc_dest_index_old(t_elem **to, long num)
{
	t_elem	*tmp;
	size_t	index;

	if (num < stackmin(*to))
	{
		ft_printf("a\n");
		if (index_of_stack(to, stackmin(*to)) == 0)
			return (0);
		return (index_of_stack(to, stackmin(*to)));
	}
	if (num > stackmax(*to))
	{
		ft_printf("b\n");
		if (index_of_stack(to, stackmin(*to)) == stacklen(to))
			return (0);
		return (index_of_stack(to, stackmax(*to)) + 1);
	}
		ft_printf("c\n");
	index = 0;
	tmp = *to;
	while (tmp != NULL)
	{
		if (tmp->prev->num > num && tmp->num < num)
			break;
		tmp = tmp->next;
		index += 1;
	}
	return (index);
}

long	abs_long(long a)
{
	if (a == LONG_MIN)
		return (0);
	if (a < 0)
		return (-a);
	return (a);
}

long	min_long(long a, long b)
{
	if (a > b)
		return (b);
	return (a);
}

long	max_long(long a, long b)
{
	if (a < b)
		return (b);
	return (a);
}

long	calc_pos_smaller(t_elem **to, t_elem *elem)
{
	t_elem	*tmp;
	size_t	i;
	long	min_dist;
	long	min_dist_pos;

	if (*to == NULL)
		return (0);
	tmp = *to;
	min_dist = stacklen(to);
	i = 0;
	min_dist_pos = 0;
	while (true)
	{
		if (tmp->pos < elem->pos && abs_long(tmp->pos - elem->pos) < min_dist)
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

long	calc_pos_bigger(t_elem **to, t_elem *elem)
{
	t_elem	*tmp;
	size_t	i;
	long	min_dist;
	long	min_dist_pos;

	if (*to == NULL)
		return (0);
	tmp = *to;
	min_dist = abs_long(tmp->pos - elem->pos);
	i = 0;
	min_dist_pos = 0;
	while (true)
	{
		if (tmp->pos > elem->pos && abs_long(tmp->pos - elem->pos) < min_dist)
		{
			min_dist = elem->pos - tmp->pos;
			min_dist_pos = i;
		}
		if (tmp->is_end == true)
			break ;
		tmp = tmp->next;
		i += 1;
	}
	return (min_dist_pos);
}

size_t	calc_dest_index(t_elem **to, t_elem *elem)
{
	return (max_long(calc_pos_bigger(to, elem), calc_pos_smaller(to, elem)));
	// t_elem	*tmp;
	// size_t	i;
	// long	min_dist;
	// long	min_dist_pos;

	// if (*to == NULL)
	// 	return (0);
	// tmp = *to;
	// min_dist = stacklen(to);
	// i = 0;
	// while (true)
	// {
	// 	if (tmp->pos < elem->pos && min_long(tmp->pos, elem->pos) < min_dist)
	// 	{
	// 		min_dist = tmp->pos - elem->pos;
	// 		min_dist_pos = i;
	// 	}
	// 	if (tmp->is_end = true)
	// 		break ;
	// 	tmp = tmp->next;
	// 	i += 1;
	// }
	// return (max_long(min_dist_pos, 0);
}

void	calc_cost(t_cost *cost, t_elem *elem, t_elem **from, t_elem **to)
{
	size_t	index;
	size_t	to_pos;
	t_cost	cost_tmp;

	cost_tmp = (t_cost){0};
	index = index_of_stack(from, elem->num);
	cost_tmp.ra = index;
	cost_tmp.rra = stacklen(from) - index;
	to_pos = calc_dest_index(to, elem);
	cost_tmp.rb = to_pos;
	cost_tmp.rrb = stacklen(to) - to_pos;
	cost_tmp.cost = calc_min_cost(&cost_tmp);
	// print_calc_cost(&cost_tmp, elem->num);
	if (cost_tmp.cost < cost->cost || cost->cost == 0)
		copy_cost(cost, &cost_tmp);
}

void	move_elem(t_info *info, t_elem **from, t_elem **to)
{
	t_elem	*tmp;
	t_cost	cost;

	cost = (t_cost){0};
	tmp = *from;
	while (true)
	{
		if (tmp->need_sort == true)
			calc_cost(&cost, tmp, from, to);
		if (tmp->is_end == true)
			break;
		tmp = tmp->next;
	}
	// print_best_cost(&cost);
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

void	move_elem_b(t_info *info, t_elem **from, t_elem **to)
{
	t_elem	*tmp;
	t_cost	cost;

	cost = (t_cost){0};
	tmp = *from;
	while (true)
	{
		if (tmp->need_sort == true)
			calc_cost(&cost, tmp, from, to);
		if (tmp->is_end == true)
			break;
		tmp = tmp->next;
	}
	// print_best_cost(&cost);
	do_move_elem_b(info, &cost);
}

// =============================================================================

void	push_n_swap(t_info *info)
{
	print_stacks(info->stack_a, info->stack_b, false);
	while (info->need_sort_count > 0)
	{
		move_elem(info, &(info->stack_a), &(info->stack_b));
		print_stacks(info->stack_a, info->stack_b, false);
		// print_stack_elem(info->stack_a);
		info->need_sort_count -= 1;
	}
	ft_printf("#####################################\n");
	while (info->stack_b != NULL)
	{
		move_elem_b(info, &(info->stack_b), &(info->stack_a));
		print_stacks(info->stack_a, info->stack_b, false);
		// print_stack_elem(info->stack_a);
	}
	// while (info->stack_b != NULL)
	// {
	// 	ret = move_elem(&(info->stack_b), &(info->stack_a));
	// }
	// if (ret == ERROR)
	// 	clean_exit(info, ERROR);

	/*
	STACK_A -> STACK_B
	while there are need_sorts in stack a
		calculate cost of all need_sorts
			loop through whole stack to find need_sort == true
				calc cost
					cost of: rotating stacks individually
					cost of: rotating stacks together as mush as possible
				store cost and method if best

		manipulate stacks based on cost info
			rotate stack_a
			rotate stack_b
			push_b

	STACK_B -> STACK_A
	while stack_b is not empty
		rotate stack_b to have largest number at the front
		rotate stack_a to receive first elem of stack_b
		push_a
	*/
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
		elem_add_front(tmp, stack);
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
	if (check_duplicates(info.stack_a) == 0)
		ft_printf("no duplicates\n");
	else
		ft_printf("there are duplicates\n");
	get_stack_info(&info);

	map_sorted_to_stack(info.stack_t, info.stack_a, stacklen(&(info.stack_t)));
	op_pb(&info);
	info.stack_b->need_sort = true;
	op_pb(&info);
	info.stack_b->need_sort = true;
	flag_non_increasing_nums(&info, info.stack_a);

	print_stack(info.stack_a, true);
	print_stacks(info.stack_a, info.stack_b, false);

	push_n_swap(&info);
	print_ops(info.ops);

	//  sort();
	// print_ops();
	clean_exit(&info, 0);
	return (0);
}

/*
TODO
---

1. delete the printer function, both .c and from the header file
*/
