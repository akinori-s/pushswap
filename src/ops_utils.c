/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 22:23:31 by asasada           #+#    #+#             */
/*   Updated: 2022/12/16 22:23:36 by asasada          ###   ########.fr       */
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
