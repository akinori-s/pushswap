/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:43:44 by asasada           #+#    #+#             */
/*   Updated: 2022/11/23 22:58:40 by asasada          ###   ########.fr       */
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
	free_stack(info->stack_a);
	free_stack(info->stack_b);
	free_stack(info->stack_t);
	ft_lstclear(info->ops, free);
	exit(exit_code);
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

void	get_inputs(t_info *info, int argc, char **argv)
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
		elem_add_front(tmp, &(info->stack_a));
		i++;
	}
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
	get_inputs(&info, argc, argv);
	print_stack(info.stack_a);
	//  sort();
	// print_ops();
	return (0);
}