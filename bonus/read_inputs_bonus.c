/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inputs_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 23:04:42 by asasada           #+#    #+#             */
/*   Updated: 2022/12/22 22:14:34 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

bool	is_valid_op(char *op)
{
	if (ft_strncmp(op, "sa\n", 3) == 0)
		return (true);
	else if (ft_strncmp(op, "sb\n", 3) == 0)
		return (true);
	else if (ft_strncmp(op, "ss\n", 3) == 0)
		return (true);
	else if (ft_strncmp(op, "pa\n", 3) == 0)
		return (true);
	else if (ft_strncmp(op, "pb\n", 3) == 0)
		return (true);
	else if (ft_strncmp(op, "ra\n", 3) == 0)
		return (true);
	else if (ft_strncmp(op, "rb\n", 3) == 0)
		return (true);
	else if (ft_strncmp(op, "rr\n", 3) == 0)
		return (true);
	else if (ft_strncmp(op, "rra\n", 4) == 0)
		return (true);
	else if (ft_strncmp(op, "rrb\n", 4) == 0)
		return (true);
	else if (ft_strncmp(op, "rrr\n", 4) == 0)
		return (true);
	return (false);
}

void	read_ops(t_info *info)
{
	char	*str;
	t_list	*elem;

	str = get_next_line(STDIN);
	while (str != NULL)
	{
		if (is_valid_op(str) == false)
			clean_exit(info, PS_ERROR);
		elem = ft_lstnew(str);
		if (elem == NULL)
			clean_exit(info, ERROR);
		ft_lstadd_back(&(info->ops), elem);
		str = get_next_line(STDIN);
	}
}

void	inputs_to_stack(t_info *info, t_elem **stack, int argc, char **argv)
{
	int		i;
	int		err;
	long	num;
	t_elem	*tmp;

	i = 1;
	err = 0;
	while (i < argc)
	{
		num = ps_atoi(argv[i], &err);
		err += ps_isnumeric(argv[i]);
		if (err > 0)
			clean_exit(info, PS_ERROR);
		tmp = new_elem(num);
		if (tmp == NULL)
			clean_exit(info, ERROR);
		elem_add_back(tmp, stack);
		i++;
	}
}
