/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_few.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:38:15 by asasada           #+#    #+#             */
/*   Updated: 2022/12/17 16:58:09 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void    sort_3_or_less(t_info *info)
{
    asdf
}

void    sort_4_or_5(t_info *info)
{
    
    // push 1 or 2 depending on argc to stack b
    // sort stack a with sort 3 or less
    // push everything in stack b back to stack a
}

void    sort_few(t_info *info)
{
    if (info->argc)
        op_ra(info);
    else if (info->argc <= 3)
        sort_3_or_less(info);
    else
        sort_4_or_5(info);
}