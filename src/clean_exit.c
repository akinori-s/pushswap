/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 16:05:14 by asasada           #+#    #+#             */
/*   Updated: 2022/11/27 16:05:26 by asasada          ###   ########.fr       */
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
	if (info->ops != NULL)
		ft_lstclear(&(info->ops), free);
	exit(exit_code);
}
