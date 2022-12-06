/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:43:44 by asasada           #+#    #+#             */
/*   Updated: 2022/12/06 23:06:47 by asasada          ###   ########.fr       */
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

// size_t	calc_dest_index(t_elem **to, long num)
// {
// 	t_elem	*tmp;
// 	size_t	index;

// 	if (num < stackmin(*to))
// 	{
// 		ft_printf("a\n");
// 		if (index_of_stack(to, stackmin(*to)) == 0)
// 			return (0);
// 		return (index_of_stack(to, stackmin(*to)));
// 	}
// 	if (num > stackmax(*to))
// 	{
// 		ft_printf("b\n");
// 		if (index_of_stack(to, stackmin(*to)) == stacklen(to))
// 			return (0);
// 		return (index_of_stack(to, stackmax(*to)) + 1);
// 	}
// 		ft_printf("c\n");
// 	index = 0;
// 	tmp = *to;
// 	while (tmp != NULL)
// 	{
// 		if (tmp->prev->num > num && tmp->num < num)
// 			break;
// 		tmp = tmp->next;
// 		index += 1;
// 	}
// 	return (index);
// }

long	calc_pos_smaller(t_elem *to, t_elem *elem)
{
	t_elem	*tmp;
	size_t	i;
	long	min_dist;
	long	min_dist_pos;

	if (to == NULL)
		return (0);
	tmp = to;
	min_dist = stacklen(to);
	i = 0;
	min_dist_pos = 0;
	while (true)
	{
		if (tmp->pos < elem->pos && abs_long(tmp->pos - elem->pos) < min_dist)
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
	// if (min_dist_pos != 0)
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
	// a = calc_pos_bigger(to, elem);
	// b = calc_pos_smaller(to, elem);
	// return (min_long(a, b));
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
	// ft_printf("%d\n", to_pos);
	// ft_printf("%d\n", stacklen(info->stack_b));
	// print_calc_cost(&cost_tmp, elem->num);
	cost_tmp.cost = calc_min_cost(&cost_tmp);
	// print_calc_cost(&cost_tmp, elem->num);
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
	// ft_printf("%d\n", to_pos);
	// ft_printf("%d\n", stacklen(info->stack_a));
	// print_calc_cost(&cost_tmp, elem->num);
	cost_tmp.cost = calc_min_cost(&cost_tmp);
	// print_calc_cost(&cost_tmp, elem->num);
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
	// print_best_cost(&cost);
	do_move_elem_b(info, &cost);
}

// =============================================================================

void	push_n_swap(t_info *info)
{
	size_t	ra;
	size_t	rra;

	// print_stacks(info->stack_a, info->stack_b, false);
	while (info->need_sort_count > 0)
	{
		move_elem(info, info->stack_a);
		// print_stacks(info->stack_a, info->stack_b, false);
		info->need_sort_count -= 1;
	}
	// ft_printf("#####################################\n");
	while (info->stack_b != NULL)
	{
		move_elem_b(info, info->stack_b);
		// print_stacks(info->stack_a, info->stack_b, false);
	}
	ra = index_of_stack(info->stack_a, stackmin(info->stack_a));
	rra = stacklen(info->stack_a) - ra;
	// ft_printf("%d, %d\n", ra, rra);
	if (ra > rra)
		while (rra-- > 0)
			op_rra(info);
	else
		while (ra-- > 0)
			op_ra(info);
	// print_stacks(info->stack_a, info->stack_b, false);

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

bool	op_is_push_swap(int	op)
{
	if (op <= 5)
		return (true);
	return (false);
}

void	remove_n_ops(t_list **prev, size_t n, int op)
{
	size_t	i;
	t_list	*tmp;

	tmp = *prev;
	i = 0;
	while (i < n && tmp)
	{
		if (*(int*)(tmp->content) == op)
		{
			*prev = tmp->next;
			ft_lstdelone(tmp, free);
			tmp = *prev;
			i++;
		}
		else
		{
			tmp = tmp->next;
			prev = &(tmp->next);
		}	
	}
}

int	insert_n_ops(t_list **prev, size_t n, int op)
{
	t_list	*tmp;
	size_t	i;

	tmp = NULL;
	i = 0;
	while (i < n)
	{
		if (insert_op_to_list(&tmp, op) == ERROR)
		{
			ft_lstclear(&tmp, free);
			return (ERROR);
		}
		i++;
	}
	ft_lstlast(tmp)->next = *prev;
	*prev = tmp;
	return (0);
}

int	join_r(t_info *info, t_list **prev, size_t len)
{
	size_t	ra;
	size_t	rb;
	size_t	i;
	t_list	*tmp;
	int		ret;

	tmp = *prev;
	i = 0;
	ra = 0;
	rb = 0;
	while (i++ < len && tmp != NULL)
	{
		if (*(int*)tmp->content == OP_RA)
			ra++;
		else if (*(int*)tmp->content == OP_RB)
			rb++;
		tmp = tmp->next;
	}
	if (min_st(ra, rb) == 0)
		return (0);
	remove_n_ops(prev, min_st(ra, rb), OP_RA);
	remove_n_ops(prev, min_st(ra, rb), OP_RB);
	ret = insert_n_ops(prev, min_st(ra, rb), OP_RR);
	(void)info;
	return (ret);
}

void	join_rotates(t_info *info, size_t start, size_t len)
{
	size_t	i;
	t_list	*tmp;
	t_list	**prev;
	int		ret;

	tmp = info->ops;
	prev = &(info->ops);
	i = 0;
	while (i++ < start)
	{
		tmp = tmp->next;
		prev = &(tmp->next);
	}
	ret = 0;
	ret += join_r(info, prev, len);
	// ret += join_rr(info, start, len);
	if (ret != 0)
		clean_exit(info, ERROR);
}

void	compress_ops(t_info *info, size_t lst_size)
{
	size_t	i;
	size_t	j;
	t_list	*tmp;

	ft_printf("%d\n", ft_lstsize(info->ops));
	tmp = info->ops;
	i = 0;
	while (i < lst_size && tmp != NULL)
	{
		j = 0;
		while (!op_is_push_swap(*(int*)tmp->content) && tmp != NULL)
		{
			j++;
			tmp = tmp->next;
			if (tmp == NULL)
				break ;
		}
		if (j != 0)
			join_rotates(info, i, j);
		if (tmp != NULL)
		{
			tmp = tmp->next;
			i += j + 1;
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
	// if (check_duplicates(info.stack_a) == 0)
	// 	ft_printf("no duplicates\n");
	// else
	// 	ft_printf("there are duplicates\n");
	get_stack_info(&info);

	map_sorted_to_stack(info.stack_t, info.stack_a, stacklen(info.stack_t));
	op_pb(&info);
	info.stack_b->need_sort = true;
	op_pb(&info);
	info.stack_b->need_sort = true;
	flag_non_increasing_nums(&info, info.stack_a);

	// print_stack(info.stack_a, true);
	// print_stacks(info.stack_a, info.stack_b, false);

	push_n_swap(&info);
	print_ops(info.ops);
	compress_ops(&info, ft_lstsize(info.ops));
	// print_ops(info.ops);
	ft_printf("%d\n", ft_lstsize(info.ops));

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
