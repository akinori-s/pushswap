/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_longest_increasing_subseq.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 21:50:31 by asasada           #+#    #+#             */
/*   Updated: 2022/12/16 22:27:35 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	mark_lis_elems(t_elem *start, t_info *info)
{
	size_t	j;
	t_elem	*prev;

	j = 0;
	prev = start;
	start->lis = true;
	while (prev && prev->is_end == false && j < info->lis_head->lis_len)
	{
		if (prev->lis_len + 1 == start->lis_len)
		{
			prev->lis = true;
			prev->need_sort = false;
			info->need_sort_count -= 1;
			start = prev;
			j++;
		}
		prev = prev->prev;
	}
}

int	calc_elem_lis_count(t_elem *start)
{
	size_t	lis_len;
	t_elem	*prev;

	lis_len = 0;
	prev = start->prev;
	while (prev && prev->is_end == false)
	{
		if (prev->pos < start->pos)
		{
			if (prev->lis_len > lis_len)
				lis_len = prev->lis_len;
		}
		prev = prev->prev;
	}
	return (lis_len + 1);
}

void	calc_longest_increasing_subsequence(t_info *info)
{
	t_elem	*next;

	if (!info->stack_a)
		return ;
	next = info->stack_a;
	info->lis_head = info->stack_a;
	while (next)
	{
		next->need_sort = true;
		info->need_sort_count += 1;

		next->lis = false;
		next->lis_len = calc_elem_lis_count(next);
		if (next->lis_len > info->lis_head->lis_len)
			info->lis_head = next;
		if (next->is_end == true)
			break ;
		next = next->next;
	}
	mark_lis_elems(info->lis_head, info);
}
