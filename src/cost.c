/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:47:03 by asasada           #+#    #+#             */
/*   Updated: 2022/12/04 18:24:22 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	calc_min_cost_tool(t_cost *c)
{
	if (c->ra + c->rrb < c->rra + c->rb)
	{
		c->rra = 0;
		c->rb = 0;
	}
	// else if (c->ra + c->rrb > c->rra + c->rb)
    else
	{
		c->ra = 0;
		c->rrb = 0;
	}
}

size_t	calc_min_cost(t_cost *c)
{
	size_t	cost_indiv;
	size_t	cost_r;
	size_t	cost_rr;

	cost_indiv = min_st(c->ra, c->rra) + min_st(c->rb, c->rrb);
	cost_r = max_st(c->ra, c->rb);
	cost_rr = max_st(c->rra, c->rrb);
    // ft_printf("%d, %d, %d, %d\n", c->ra, c->rra, c->rb, c->rrb);
    // ft_printf("%d, %d, %d\n", cost_indiv, cost_r, cost_rr);
    // ft_printf("%d\n", min_st(cost_indiv, min_st(cost_r, cost_rr)));
	if (cost_r == min_st(cost_indiv, min_st(cost_r, cost_rr)))
	{
		c->rra = 0;
		c->rrb = 0;
	}
	else if (cost_rr == min_st(cost_indiv, min_st(cost_r, cost_rr)))
	{
		c->ra = 0;
		c->rb = 0;
	}
	else
		calc_min_cost_tool(c);
	return (min_st(cost_indiv, min_st(cost_r, cost_rr)));
}

void	copy_cost(t_cost *to, t_cost *from)
{
	to->cost = from->cost;
	to->ra = from->ra;
	to->rb = from->rb;
	to->rra = from->rra;
	to->rrb = from->rrb;
}
