/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 21:38:28 by asasada           #+#    #+#             */
/*   Updated: 2022/12/22 21:47:07 by asasada          ###   ########.fr       */
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
	size_t	numeric_count;

	numeric_count = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
		str++;
	while (*str != '\0')
	{
		if (*str >= '0' && *str <= '9')
		{
			numeric_count++;
			str++;
		}
		else
			return (1);
	}
	if (numeric_count == 0)
		return (1);
	return (0);
}

bool	is_sorted(t_elem *stack)
{
	t_elem	*tmp;

	tmp = stack;
	while (tmp->is_end != true)
	{
		if (tmp->num >= tmp->next->num)
			return (false);
		tmp = tmp->next;
	}
	return (true);
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
	read_ops(&info);
	execute_ops(&info);
	if (is_sorted(info.stack_a) && stacklen(info.stack_b) == 0)
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	clean_exit(&info, 0);
	return (0);
}
