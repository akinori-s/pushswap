/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 16:06:04 by asasada           #+#    #+#             */
/*   Updated: 2022/11/27 21:19:43 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	insert_op_to_list(t_list **list, int op)
{
	int		*ptr;
	t_list	*new;

	ptr = malloc(sizeof(int));
	if (ptr == NULL)
		return (-1);
	*ptr = op;
	new = ft_lstnew(ptr);
	if (new == NULL)
	{
		free(ptr);
		ptr = NULL;
		return (-1);
	}
	ft_lstadd_back(list, new);
	return (0);
}

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

size_t	index_of_stack(t_elem **stack, long num)
{
	size_t	i;
	t_elem	*tmp;

	if (stack == NULL)
		return (0);
	if (*stack == NULL)
		return (0);
	i = 0;
	tmp = *stack;
	while (tmp->num != num && tmp->next != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

size_t	stacklen(t_elem **stack)
{
	size_t	i;
	t_elem	*tmp;

	if (stack == NULL)
		return (0);
	if (*stack == NULL)
		return (0);
	i = 1;
	tmp = *stack;
	while (tmp->is_end != true && tmp->next != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
