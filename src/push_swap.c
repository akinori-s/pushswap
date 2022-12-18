/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:43:44 by asasada           #+#    #+#             */
/*   Updated: 2022/12/18 21:33:48 by asasada          ###   ########.fr       */
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
	// ft_printf("%d, %d, %d\n", q1, q2, q3);
	quick_sort_1(info, q2, q3);
	quick_sort_1(info, 0, q1);
}

// =============================================================================

void	push_n_swap(t_info *info)
{
	size_t	ra;
	size_t	rra;

	// print_stacks(info->stack_a, info->stack_b, true);
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


// =============================================================================

int	ps_atoi(char *str, int *err)
{
	int		m_count;
	long	n;

	n = 0;
	m_count = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			m_count = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		n = (n * 10) + (*str - '0');
		if ((n > (long)INT_MAX && m_count == 1) || n * m_count < (long)INT_MIN)
		{
			*err = true;
			return (0);
		}
		str++;
	}
	return ((int)(n * m_count));
}

int	ps_isnumeric(char *str)
{
	bool	found_numeric;
	size_t	numeric_count;

	found_numeric = false;
	numeric_count = 0;
	while (*str != '\0')
	{
		if (*str >= '0' && *str <= '9')
		{
			found_numeric = true;
			numeric_count++;
		}
		if ((*str < '0' || *str > '9') && (*str != '+' && *str != '-'))
			return (1);
		if ((*str == '+' || *str == '-') && found_numeric)
			return (1);
		str++;
	}
	if (numeric_count == 0)
		return (1);
	return (0);
}

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
		num = ps_atoi(argv[i], &err);
		err += ps_isnumeric(argv[i]);
		if (err > 0)
			clean_exit(info, PS_ERROR);
		tmp = new_elem(num);
		if (tmp == NULL)
			clean_exit(info, ERROR);
		elem_add_back(tmp, stack);
		i++;
	}
}

bool	is_sorted(t_elem *stack)
{
	t_elem	*tmp;

	tmp = stack;
	while (tmp->is_end != true)
	{
		if (tmp->pos >= tmp->next->pos)
			return (false);
		tmp = tmp->next;
	}
	return (true);
}

// =============================================================================

int	main(int argc, char **argv)
{
	t_info	info;

	info = (t_info){0};
	if (argc - 1 <= 0)
		return (0);
	inputs_to_stack(&info, &(info.stack_a), argc, argv);
	inputs_to_stack(&info, &(info.stack_t), argc, argv);
	sort_tmp_stack(info.stack_t);
	get_stack_info(&info);
	map_sorted_to_stack(info.stack_t, info.stack_a, stacklen(info.stack_t));
	if (argc - 1 <= 1)
		return (0);
	if (check_duplicates(info.stack_t))
		clean_exit(&info, PS_ERROR);
	if (is_sorted(info.stack_a))
	{
		// ft_printf("issorted\n");
		return (0);
	}
	if (argc - 1 <= 6)
		sort_few(&info, argc - 1);
	else
	{
		calc_longest_increasing_subsequence(&info);
		push_n_swap(&info);
	}
	compress_ops(&info);
	print_ops(info.ops, false);
	// print_stacks(info.stack_a, info.stack_b, true);
	clean_exit(&info, 0);
	return (0);
}

/*
TODO
---

1. delete the printer function, both .c and from the header file
2. add error handling
	* non-numerical inputs
	* numerical inputs greater than int
	* there are duplicates
	* it is already sorted
3. add sorting for numbers that are 5 or less
4. DONE handle command line arguments
	* only one argument (program name)
	* only two arguments (no sorting needed)
	* three arguments (might not need to sort)
	* four to six arguments (might not need to sort)
5. allow spaces in ps_atoi
*/
