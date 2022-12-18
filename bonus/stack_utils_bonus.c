/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 21:45:39 by asasada           #+#    #+#             */
/*   Updated: 2022/12/18 22:05:25 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

t_elem	*new_elem(long num)
{
	t_elem	*tmp;

	tmp = malloc(sizeof(t_elem));
	if (tmp == NULL)
		return (NULL);
	*tmp = (t_elem){0};
	tmp->num = num;
	return (tmp);
}

size_t	stacklen(t_elem *stack)
{
	size_t	i;
	t_elem	*tmp;

	if (stack == NULL)
		return (0);
	i = 1;
	tmp = stack;
	while (tmp->is_end != true && tmp->next != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
