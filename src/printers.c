/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 16:08:59 by asasada           #+#    #+#             */
/*   Updated: 2022/11/27 16:09:08 by asasada          ###   ########.fr       */
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
