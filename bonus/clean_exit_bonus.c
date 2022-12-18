/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 21:43:21 by asasada           #+#    #+#             */
/*   Updated: 2022/12/18 21:44:14 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

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
	if (exit_code == PS_ERROR)
		ft_printf("Error\n");
	exit(exit_code);
}
