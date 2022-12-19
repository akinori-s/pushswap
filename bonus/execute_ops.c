/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 23:06:03 by asasada           #+#    #+#             */
/*   Updated: 2022/12/19 23:06:16 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

void	execute_push_swaps(t_info *info, char *op)
{
	if (ft_strncmp(op, "sa\n", 3) == 0)
		op_sa(info);
	else if (ft_strncmp(op, "sb\n", 3) == 0)
		op_sb(info);
	else if (ft_strncmp(op, "ss\n", 3) == 0)
	{
		op_sa(info);
		op_sb(info);
	}
	else if (ft_strncmp(op, "pa\n", 3) == 0)
		op_pa(info);
	else if (ft_strncmp(op, "pb\n", 3) == 0)
		op_pb(info);
}

void	execute_rotates(t_info *info, char *op)
{
	if (ft_strncmp(op, "ra\n", 3) == 0)
		op_ra(info);
	else if (ft_strncmp(op, "rb\n", 3) == 0)
		op_rb(info);
	else if (ft_strncmp(op, "rr\n", 3) == 0)
	{
		op_ra(info);
		op_rb(info);
	}
	else if (ft_strncmp(op, "rra\n", 4) == 0)
		op_rra(info);
	else if (ft_strncmp(op, "rrb\n", 4) == 0)
		op_rrb(info);
	else if (ft_strncmp(op, "rrr\n", 4) == 0)
	{
		op_rra(info);
		op_rrb(info);
	}
}

void	execute_ops(t_info *info)
{
	t_list	*tmp;

	tmp = info->ops;
	while (tmp != NULL)
	{
		execute_push_swaps(info, tmp->content);
		execute_rotates(info, tmp->content);
		tmp = tmp->next;
	}
}
