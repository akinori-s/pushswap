/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_compression.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 21:48:47 by asasada           #+#    #+#             */
/*   Updated: 2022/12/16 21:52:58 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	join_rr(t_info *info, size_t i, size_t n)
{
	t_list	*tmp;
	size_t	rra;
	size_t	rrb;

	tmp = info->ops;
	rra = 0;
	while (rra++ < i)
		tmp = tmp->next;
	rra = 0;
	rrb = 0;
	while ((rra < n || rrb < n) && tmp != NULL)
	{
		if (*(int*)tmp->content == OP_RRA && rra < n)
		{
			*(int*)tmp->content = OP_RRR;
			rra++;
			tmp = tmp->next;
		}
		else if (*(int*)tmp->content == OP_RRB && rrb < n)
		{
			*(int*)tmp->content = OP_NONE;
			rrb++;
		}
		else
			tmp = tmp->next;
	}
}

void	join_r(t_info *info, size_t i, size_t n)
{
	t_list	*tmp;
	size_t	ra;
	size_t	rb;

	tmp = info->ops;
	ra = 0;
	while (ra++ < i)
		tmp = tmp->next;
	ra = 0;
	rb = 0;
	while ((ra < n || rb < n) && tmp != NULL)
	{
		if (*(int*)tmp->content == OP_RA && ra < n)
		{
			*(int*)tmp->content = OP_RR;
			ra++;
			tmp = tmp->next;
		}
		else if (*(int*)tmp->content == OP_RB && rb < n)
		{
			*(int*)tmp->content = OP_NONE;
			rb++;
		}
		else
			tmp = tmp->next;
	}
}

int	join_rev_rotates(t_info *info, size_t i, size_t j)
{
	t_list	*tmp;
	size_t	rra;
	size_t	rrb;
	size_t	t;

	tmp = info->ops;
	rra = 0;
	rrb = 0;
	t = 0;
	while (t++ < i)
		tmp = tmp->next;
	t = 0;
	while (t++ < j)
	{
		if (*(int*)tmp->content == OP_RRA)
			rra++;
		else if (*(int*)tmp->content == OP_RRB)
			rrb++;
		tmp = tmp->next;
	}
	if (min_st(rra, rrb) == 0)
		return (0);
	join_rr(info, i, min_st(rra, rrb));
	return (1);
}

int	join_rotates(t_info *info, size_t i, size_t j)
{
	t_list	*tmp;
	size_t	ra;
	size_t	rb;
	size_t	t;

	tmp = info->ops;
	ra = 0;
	rb = 0;
	t = 0;
	while (t++ < i)
		tmp = tmp->next;
	t = 0;
	while (t++ < j)
	{
		if (*(int*)tmp->content == OP_RA)
			ra++;
		else if (*(int*)tmp->content == OP_RB)
			rb++;
		tmp = tmp->next;
	}
	if (min_st(ra, rb) == 0)
		return (0);
	join_r(info, i, min_st(ra, rb));
	return (1);
}

void	compress_ops(t_info *info)
{
	size_t	i;
	size_t	j;
	t_list	*tmp;

	i = 0;
	tmp = info->ops;
	while (tmp != NULL)
	{
		j = 0;
		while (tmp != NULL && (*(int*)tmp->content) >= OP_RA)
		{
			j++;
			tmp = tmp->next;
		}
		if (tmp != NULL)
		{
			if (join_rotates(info, i, j) == 1 || join_rev_rotates(info, i, j) == 1)
			{
				tmp = info->ops;
				i = 0;
				continue ;
			}
			i += j + 1;
			tmp = tmp->next;
		}
	}
}
