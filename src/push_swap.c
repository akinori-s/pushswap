/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:43:44 by asasada           #+#    #+#             */
/*   Updated: 2022/12/22 21:21:47 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	get_stack_info(t_info *info)
{
	size_t	stack_len;
	size_t	median_index;
	size_t	i;
	t_elem	*tmp;

	stack_len = stacklen(info->stack_t);
	median_index = stack_len / 2;
	i = 0;
	tmp = info->stack_t;
	while (i < median_index)
	{
		tmp = tmp->next;
		i++;
	}
	info->median = tmp->num;
	info->min = info->stack_t->num;
	info->max = info->stack_t->prev->num;
	info->max_pos = info->stack_t->prev->pos;
	info->stack_t_len = stack_len;
}

void	prep_push_swap(t_info *info, int argc, char **argv)
{
	inputs_to_stack(info, &(info->stack_a), argc, argv);
	inputs_to_stack(info, &(info->stack_t), argc, argv);
	sort_tmp_stack(info->stack_t);
	get_stack_info(info);
	map_sorted_to_stack(info->stack_t, info->stack_a, stacklen(info->stack_t));
}

void	print_ops(t_list *lst)
{
	while (lst != NULL)
	{
		if (*(int *)(lst->content) == OP_SA)
			ft_printf("sa\n");
		if (*(int *)(lst->content) == OP_SB)
			ft_printf("sb\n");
		if (*(int *)(lst->content) == OP_PA)
			ft_printf("pa\n");
		if (*(int *)(lst->content) == OP_PB)
			ft_printf("pb\n");
		if (*(int *)(lst->content) == OP_RA)
			ft_printf("ra\n");
		if (*(int *)(lst->content) == OP_RB)
			ft_printf("rb\n");
		if (*(int *)(lst->content) == OP_RR)
			ft_printf("rr\n");
		if (*(int *)(lst->content) == OP_RRA)
			ft_printf("rra\n");
		if (*(int *)(lst->content) == OP_RRB)
			ft_printf("rrb\n");
		if (*(int *)(lst->content) == OP_RRR)
			ft_printf("rrr\n");
		lst = lst->next;
	}
}

int	main(int argc, char **argv)
{
	t_info	info;

	info = (t_info){0};
	if (argc - 1 <= 0)
		return (0);
	prep_push_swap(&info, argc, argv);
	if (argc - 1 <= 1)
		return (0);
	if (check_duplicates(info.stack_t))
		clean_exit(&info, PS_ERROR);
	if (is_sorted(info.stack_a))
		return (0);
	if (argc - 1 <= 6)
		sort_few(&info, argc - 1);
	else
	{
		calc_longest_increasing_subsequence(&info);
		push_n_swap(&info);
	}
	compress_ops(&info, 0);
	print_ops(info.ops);
	clean_exit(&info, 0);
	return (0);
}
