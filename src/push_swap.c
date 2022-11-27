/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:43:44 by asasada           #+#    #+#             */
/*   Updated: 2022/11/27 16:02:21 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_elem(t_elem *elem)
{
	ft_printf("%9d <- ", elem->prev->num);
	ft_printf("%9d -> ", elem->num);
	ft_printf("%9d\n", elem->next->num);
	ft_printf("%p <- ", elem->prev);
	ft_printf("%p -> ", elem);
	ft_printf("%p\n", elem->next);
}

void	print_stack(t_elem *stack, bool extra)
{
	ft_printf("=================================\n");
	while (true)
	{
		if (extra)
			ft_printf("%d, %d, %d\n", stack->num, stack->pos, stack->need_sort);
		else
			ft_printf("%d\n", stack->num);
		if (stack->is_end == true)
			break ;
		stack = stack->next;
	}
}

// =============================================================================

void	free_stack(t_elem *stack)
{
	t_elem	*tmp;

	while ((stack)->is_end == false)
	{
		tmp = (stack)->next;
		free(stack);
		stack = tmp;
	}
	free(stack);
	stack = NULL;
}

void	clean_exit(t_info *info, int exit_code)
{
	if (info->stack_a != NULL)
		free_stack(info->stack_a);
	if (info->stack_b != NULL)
		free_stack(info->stack_b);
	if (info->stack_t != NULL)
		free_stack(info->stack_t);
	if (info->ops != NULL)
		ft_lstclear(&(info->ops), free);
	exit(exit_code);
}

// =============================================================================

size_t	index_of_stack(t_elem **stack, long num)
{
	size_t	i;
	t_elem	*tmp;

	if (stack == NULL)
		return (0);
	if (*stack == NULL)
		return (0);
	i = 0;
	tmp = *stack;
	while (tmp->num != num && tmp->next != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

size_t	stacklen(t_elem **stack)
{
	size_t	i;
	t_elem	*tmp;

	if (stack == NULL)
		return (0);
	if (*stack == NULL)
		return (0);
	i = 1;
	tmp = *stack;
	while (tmp->is_end != true && tmp->next != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

// =============================================================================

void	apply_arr_to_stack(long *arr, t_elem *stack)
{
	size_t	i;
	t_elem	*tmp;

	i = 0;
	tmp = stack;
	while (true)
	{
		tmp->num = arr[i];
		if (tmp->is_end)
			break ;
		tmp = tmp->next;
		i++;
	}
}

void	sort_long_arr(long *arr, size_t arr_size)
{
	size_t	i;
	size_t	j;
	long	tmp;

	i = 0;
	while (i < arr_size)
	{
		j = 0;
		while (j < arr_size - i - 1)
		{
			if (arr[j] > arr[j + 1])
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	sort_tmp_stack(t_elem *stack)
{
	size_t	i;
	size_t	len;
	long	*arr;
	t_elem	*tmp;

	len = stacklen(&stack);
	arr = malloc(sizeof(long) * len);
	if (arr == NULL)
		return (-1);
	tmp = stack;
	i = 0;
	while (true)
	{
		arr[i] = tmp->num;
		if (tmp->is_end)
			break ;
		tmp = tmp->next;
		i++;
	}
	sort_long_arr(arr, len);
	apply_arr_to_stack(arr, stack);
	free(arr);
	return (0);
}

int	check_duplicates(t_elem	*sorted)
{
	t_elem	*tmp;

	if (sorted == NULL)
		return (-1);
	tmp = sorted;
	while (tmp->is_end != true)
	{
		if (tmp->num == tmp->next->num)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}

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

void	map_sorted_to_stack(t_elem *sorted, t_elem *stack, size_t sorted_len)
{
	size_t	i;
	t_elem	*stack_tmp;
	t_elem	*sorted_tmp;

	if (sorted == NULL || stack == NULL || sorted_len != stacklen(&stack))
		return ;
	i = 0;
	sorted_tmp = sorted;
	while (i < sorted_len)
	{
		stack_tmp = stack;
		while (true)
		{
			if (stack_tmp->num == sorted_tmp->num)
			{
				stack_tmp->pos = i;
				break ;
			}
			stack_tmp = stack_tmp->next;
		}
		sorted_tmp = sorted_tmp->next;
		i++;
	}
}

// =============================================================================

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

t_elem	*new_elem(long num)
{
	t_elem	*tmp;

	tmp = malloc(sizeof(t_elem));
	if (tmp == NULL)
		return (NULL);
	*tmp = (t_elem){0};
	tmp->num = num;
	return (tmp);
}

void	swap(t_elem **stack)
{
	t_elem	*elem;
	t_elem	*next;

	if (stack == NULL)
		return ;
	if (*stack == NULL)
		return ;
	elem = *stack;
	if (elem->is_end || elem->next == NULL)
		return ;
	next = elem->next;
	if (elem->prev != next)
		next->prev = elem->prev;
	elem->prev = next;
	if (next->next != elem)
		elem->next = next->next;
	next->next = elem;
	if (next->is_end == true)
	{
		next->is_end = false;
		elem->is_end = true;
	}
	*stack = next;
}

void	elem_add_front(t_elem *new, t_elem **stack)
{
	t_elem	*first;
	t_elem	*last;

	if (new == NULL || stack == NULL)
		return ;
	if (*stack == NULL)
	{
		*stack = new;
		new->next = new;
		new->prev = new;
		new->is_end = true;
		return ;
	}
	first = *stack;
	last = first->prev;
	new->prev = last;
	new->next = first;
	first->prev = new;
	last->next = new;
	*stack = new;
}

t_elem	*pop_elem(t_elem **stack)
{
	t_elem	*prev;
	t_elem	*next;
	t_elem	*elem;

	if (stack == NULL)
		return (NULL);
	if (*stack == NULL)
		return (NULL);
	elem = *stack;
	prev = elem->prev;
	next = elem->next;

	prev->next = next;
	next->prev = prev;

	if (elem->is_end != true)
		*stack = next;
	else
		*stack = NULL;
	elem->is_end = false;
	return (elem);
}

void	rotate_stack(t_elem **stack)
{
	if (stack == NULL)
		return ;
	if (*stack == NULL)
		return ;
	(*stack)->prev->is_end = false;
	(*stack)->is_end = true;
	*stack = (*stack)->next;
}

void	rev_rotate_stack(t_elem **stack)
{
	if (stack == NULL)
		return ;
	if (*stack == NULL)
		return ;
	(*stack)->prev->is_end = false;
	(*stack)->prev->prev->is_end = true;
	*stack = (*stack)->prev;
}

int	insert_op_to_list(t_list **list, int op)
{
	int		*ptr;
	t_list	*new;

	ptr = malloc(sizeof(int));
	if (ptr == NULL)
		return (-1);
	*ptr = op;
	new = ft_lstnew(ptr);
	if (new == NULL)
	{
		free(ptr);
		ptr = NULL;
		return (-1);
	}
	ft_lstadd_back(list, new);
	return (0);
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
