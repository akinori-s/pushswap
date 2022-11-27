/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 16:08:59 by asasada           #+#    #+#             */
/*   Updated: 2022/11/27 21:20:18 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_stack_elem(t_elem *stack)
{
	t_elem	*tmp;

	tmp = stack;
	while (true)
	{
		print_elem(tmp);
		if (tmp->is_end == true)
			break ;
		tmp = tmp->next;
	}
}

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

void	print_stacks(t_elem *stack_a, t_elem *stack_b, bool extra)
{
	bool	a;
	bool	b;

	a = true;
	b = true;
	if (stack_a == NULL)
		a = false;
	if (stack_b == NULL)
		b = false;
	ft_printf("================================\n");
	ft_printf("        A               B\n");
	ft_printf("================ ===============\n");
	while (true)
	{
		if (extra)
			ft_printf("%d, %d, %d\n", stack_a->num, stack_a->pos, stack_a->need_sort);
		else
		{
			if (a)
				ft_printf("%14d", stack_a->num);
			else
				ft_printf("              ");
			if (b)
				ft_printf(" %14d\n", stack_b->num);
			else
				ft_printf("\n");
		}
		if (stack_a != NULL)
		{
			if (stack_a->is_end == true)
				a = false;
		}
		if (stack_b != NULL)
		{
			if (stack_b->is_end == true)
				b = false;
		}
		if (!a && !b)
			break ;
		if (stack_a)
			stack_a = stack_a->next;
		if (stack_b)
			stack_b = stack_b->next;
	}
}

void	print_best_cost(t_cost *cost)
{
	ft_printf("==========best cost============\n");
	ft_printf("ra: %5d, rra: %5d\n", cost->ra, cost->rra);
	ft_printf("rb: %5d, rrb: %5d\n", cost->rb, cost->rb);
	ft_printf("cost: %d\n", cost->cost);
}

void	print_calc_cost(t_cost *cost, long num)
{
	ft_printf("======================\n");
	ft_printf("num: %d\n", num);
	ft_printf("ra: %5d, rra: %5d\n", cost->ra, cost->rra);
	ft_printf("rb: %5d, rrb: %5d\n", cost->rb, cost->rb);
}

void	print_ops(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp != NULL)
	{
		if (*(int *)(tmp->content) == OP_SA)
			ft_printf("SA\n");
		if (*(int *)(tmp->content) == OP_SB)
			ft_printf("SB\n");
		if (*(int *)(tmp->content) == OP_PA)
			ft_printf("PA\n");
		if (*(int *)(tmp->content) == OP_PB)
			ft_printf("PB\n");
		if (*(int *)(tmp->content) == OP_RA)
			ft_printf("RA\n");
		if (*(int *)(tmp->content) == OP_RB)
			ft_printf("RB\n");
		if (*(int *)(tmp->content) == OP_RRA)
			ft_printf("RRA\n");
		if (*(int *)(tmp->content) == OP_RRB)
			ft_printf("RRB\n");
		tmp = tmp->next;
	}
}
