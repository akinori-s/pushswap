/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:43:44 by asasada           #+#    #+#             */
/*   Updated: 2022/11/27 00:06:23 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
	ft_lstclear(info->ops, free);
	exit(exit_code);
}

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

void	swap(t_info *info, t_elem **stack)
{
	t_elem	*elem;
	t_elem	*next;

	(void)info;
	elem = *stack;
	if (elem->is_end || elem->next == NULL)
		return ;
	next = elem->next;

	next->prev = elem->prev;
	elem->prev = next;

	elem->next = next->next;
	next->next = elem;

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

void	print_stack(t_elem *stack)
{
	while (stack->is_end == false)
	{
		ft_printf("%d\n", stack->num);
		stack = stack->next;
	}
	ft_printf("%d\n", stack->num);
}

int	main(int argc, char **argv)
{
	t_info	info;

	info = (t_info){0};
	inputs_to_stack(&info, &(info.stack_a), argc, argv);
	inputs_to_stack(&info, &(info.stack_t), argc, argv);
	print_stack(info.stack_a);
	swap(&info, &(info.stack_a));
	// swap(&info, &(info.stack_a));
	ft_printf("===\n");
	print_stack(info.stack_a);
	ft_printf("===\n");
	sort_tmp_stack(info.stack_a);
	print_stack(info.stack_a);
	// print_stack(info.stack_t);
	//  sort();
	// print_ops();
	clean_exit(&info, 0);
	return (0);
}
