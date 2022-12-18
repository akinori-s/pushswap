/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 21:38:28 by asasada           #+#    #+#             */
/*   Updated: 2022/12/18 22:06:27 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

int	ps_atoi(char *str, int *err)
{
	int		m_count;
	long	n;

	n = 0;
	m_count = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			m_count = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		n = (n * 10) + (*str - '0');
		if ((n > (long)INT_MAX && m_count == 1) || n * m_count < (long)INT_MIN)
		{
			*err = true;
			return (0);
		}
		str++;
	}
	return ((int)(n * m_count));
}

int	ps_isnumeric(char *str)
{
	bool	found_numeric;
	size_t	numeric_count;

	found_numeric = false;
	numeric_count = 0;
	while (*str != '\0')
	{
		if (*str >= '0' && *str <= '9')
		{
			found_numeric = true;
			numeric_count++;
		}
		if ((*str < '0' || *str > '9') && (*str != '+' && *str != '-'))
			return (1);
		if ((*str == '+' || *str == '-') && found_numeric)
			return (1);
		str++;
	}
	if (numeric_count == 0)
		return (1);
	return (0);
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

bool	is_sorted(t_elem *stack)
{
	t_elem	*tmp;

	tmp = stack;
	while (tmp->is_end != true)
	{
		if (tmp->pos >= tmp->next->pos)
			return (false);
		tmp = tmp->next;
	}
	return (true);
}

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

int	main(int argc, char **argv)
{
	t_info	info;

	info = (t_info){0};
	if (argc - 1 <= 0)
		return (0);
	inputs_to_stack(&info, &(info.stack_a), argc, argv);
	inputs_to_stack(&info, &(info.stack_t), argc, argv);
	sort_tmp_stack(info.stack_t);
	if (check_duplicates(info.stack_t))
		clean_exit(&info, PS_ERROR);
	if (is_sorted(info.stack_a))
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	clean_exit(&info, 0);
	return (0);
}