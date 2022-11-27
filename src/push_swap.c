/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:43:44 by asasada           #+#    #+#             */
/*   Updated: 2022/11/27 16:13:56 by asasada          ###   ########.fr       */
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
			tmp->need_sort = true;
		if (tmp->pos == info->stack_t_len - 1)
			current_max = 0;
		if (tmp->is_end == true)
			break ;
		tmp = tmp->next;
	}
}

// =============================================================================

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
	// print_stack(info.stack_a, false);
	// print_stack(info.stack_t, false);
	// print_elem(info.stack_a);
	// print_elem(info.stack_a->next);
	// swap(&(info.stack_a));
	// swap(&(info.stack_a->next));
	// swap(&(info.stack_a));
	// print_stack(info.stack_a, false);
	// print_stack(info.stack_t, false);

	sort_tmp_stack(info.stack_t);

	// print_stack(info.stack_a, false);
	// print_stack(info.stack_t, false);
	if (check_duplicates(info.stack_a) == 0)
		ft_printf("no duplicates\n");
	else
		ft_printf("there are duplicates\n");
	get_stack_info(&info);
	ft_printf("%d, %d, %d\n", info.min, info.max, info.median);
	print_stack(info.stack_t, true);
	print_stack(info.stack_a, true);
	map_sorted_to_stack(info.stack_t, info.stack_a, stacklen(&(info.stack_t)));
	flag_non_increasing_nums(&info, info.stack_a);
	print_stack(info.stack_t, true);
	print_stack(info.stack_a, true);
	// print_stack(info.stack_t, false);
	//  sort();
	// print_ops();
	clean_exit(&info, 0);
	return (0);
}
