/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 21:28:34 by asasada           #+#    #+#             */
/*   Updated: 2022/11/27 21:36:21 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

size_t	min_st(size_t a, size_t b)
{
	if (a > b)
		return (b);
	return (a);
}

size_t	max_st(size_t a, size_t b)
{
	if (a < b)
		return (b);
	return (a);
}


long	abs_long(long a)
{
	if (a == LONG_MIN)
		return (0);
	if (a < 0)
		return (-a);
	return (a);
}

long	min_long(long a, long b)
{
	if (a > b)
		return (b);
	return (a);
}

long	max_long(long a, long b)
{
	if (a < b)
		return (b);
	return (a);
}
