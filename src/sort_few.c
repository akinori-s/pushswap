/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_few.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:38:15 by asasada           #+#    #+#             */
/*   Updated: 2022/12/18 14:15:01 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void    sort_3_or_less(t_info *info, int arg_count)
{
	if (arg_count == 2)
		op_ra(info);
	else
	{
		if (info->stack_a->pos == 0)
		{
			op_rra(info);
			op_sa(info);
		}
		else if (info->stack_a->pos == 1 && info->stack_a->next->pos == 0)
			op_sa(info);
		else if (info->stack_a->pos == 1 && info->stack_a->next->pos == 2)
			op_rra(info);
		else if (info->stack_a->next->pos == 1)
		{
			op_sa(info);
			op_rra(info);
		}
		else
			op_ra(info);
	}
}

void    sort_4_or_5(t_info *info)
{
    (void)info;
    // push 1 or 2 depending on argc to stack b
    // sort stack a with sort 3 or less
    // push everything in stack b back to stack a
}

void    sort_few(t_info *info, int arg_count)
{
	if (arg_count <= 3)
        sort_3_or_less(info, arg_count);
    else
        sort_4_or_5(info);
}