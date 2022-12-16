/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_longest_increasing_subseq.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 21:50:31 by asasada           #+#    #+#             */
/*   Updated: 2022/12/17 00:16:26 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	mark_lis_elems(t_elem *elem, t_info *info)
{
	size_t	j;
	t_elem	*tmp;

	j = 0;
	tmp = elem;
	elem->lis = true;
	while (tmp && j < info->lis_head->lis_len)
	{
		if (tmp->lis_len + 1 == elem->lis_len)
		{
			tmp->lis = true;
			tmp->need_sort = false;
			info->need_sort_count -= 1;
			elem = tmp;
			j++;
		}
		tmp = tmp->prev;
		if (tmp->is_end == true)
			break ;
	}
}

int	calc_elem_lis_count(t_elem *elem)
{
	size_t	lis_len;
	t_elem	*tmp;

	lis_len = 0;
	tmp = elem->prev;
	while (tmp && tmp->is_end == false)
	{
		if (tmp->pos < elem->pos)
		{
			if (tmp->lis_len > lis_len)
				lis_len = tmp->lis_len;
		}
		tmp = tmp->prev;
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
