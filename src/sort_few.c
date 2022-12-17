/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_few.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:38:15 by asasada           #+#    #+#             */
/*   Updated: 2022/12/17 21:47:34 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void    sort_3_or_less(t_info *info)
{
    (void)info;
}

void    sort_4_or_5(t_info *info)
{
    (void)info;
    // push 1 or 2 depending on argc to stack b
    // sort stack a with sort 3 or less
    // push everything in stack b back to stack a
}

void    sort_few(t_info *info)
{
	ft_printf("asdf\n");
    if (info->argc)
        op_ra(info);
    else if (info->argc <= 3)
        sort_3_or_less(info);
    else
        sort_4_or_5(info);
}