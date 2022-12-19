/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_ops_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 21:53:19 by asasada           #+#    #+#             */
/*   Updated: 2022/12/19 23:16:48 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

void	op_ra(t_info *info)
{
	rotate_stack(&(info->stack_a));
}

void	op_rb(t_info *info)
{
	rotate_stack(&(info->stack_b));
}

void	op_rra(t_info *info)
{
	rev_rotate_stack(&(info->stack_a));
}

void	op_rrb(t_info *info)
{
	rev_rotate_stack(&(info->stack_b));
}
