/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 08:38:42 by asasada           #+#    #+#             */
/*   Updated: 2022/12/22 08:39:05 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	op_ra(t_info *info)
{
	rotate_stack(&(info->stack_a));
	if (insert_op_to_list(&(info->ops), OP_RA) == ERROR)
		clean_exit(info, ERROR);
}

void	op_rb(t_info *info)
{
	rotate_stack(&(info->stack_b));
	if (insert_op_to_list(&(info->ops), OP_RB) == ERROR)
		clean_exit(info, ERROR);
}

void	op_rra(t_info *info)
{
	rev_rotate_stack(&(info->stack_a));
	if (insert_op_to_list(&(info->ops), OP_RRA) == ERROR)
		clean_exit(info, ERROR);
}

void	op_rrb(t_info *info)
{
	rev_rotate_stack(&(info->stack_b));
	if (insert_op_to_list(&(info->ops), OP_RRB) == ERROR)
		clean_exit(info, ERROR);
}
