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
