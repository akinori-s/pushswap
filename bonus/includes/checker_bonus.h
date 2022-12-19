/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 21:38:53 by asasada           #+#    #+#             */
/*   Updated: 2022/12/19 23:18:02 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_BONUS_H
# define CHECKER_BONUS_H

# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

# define STDIN 1
# define ERROR -1
# define PS_ERROR -2

# define OP_NONE 0
# define OP_SA 1
# define OP_SB 2
# define OP_SS 3

# define OP_PA 4
# define OP_PB 5

# define OP_RA 6
# define OP_RB 7
# define OP_RR 8

# define OP_RRA 9
# define OP_RRB 10
# define OP_RRR 11

typedef struct s_elem
{
	struct s_elem	*prev;
	struct s_elem	*next;
	long			num;
	bool			need_sort;
	bool			is_end;
	bool			lis;
	size_t			pos;
	size_t			tmp_pos;
	size_t			lis_len;
	int				move_b_cost;
}	t_elem;

typedef struct s_info
{
	t_elem	*stack_a;
	t_elem	*stack_b;
	t_elem	*stack_t;
	t_elem	*lis_head;
	t_list	*ops;

	long	min;
	long	median;
	long	max;
	size_t	max_pos;
	size_t	stack_t_len;
	size_t	need_sort_count;
}	t_info;

// checker_bonus.c
int		ps_atoi(char *str, int *err);
int		ps_isnumeric(char *str);
bool	is_sorted(t_elem *stack);

// clean_exit_bonus.c
void	free_stack(t_elem *stack);
void	clean_exit(t_info *info, int exit_code);

// stack_utils_bonus.c
t_elem	*new_elem(long num);
size_t	stacklen(t_elem *stack);

// prep_stack_bonus.c
void	apply_arr_to_stack(long *arr, t_elem *stack);
void	sort_long_arr(long *arr, size_t arr_size);
int		sort_tmp_stack(t_elem *stack);
int		check_duplicates(t_elem	*sorted);

// stack_ops_bonus.c
void	swap(t_elem **stack);
void	elem_add_back(t_elem *new, t_elem **stack);
void	elem_add_front(t_elem *new, t_elem **stack);

// stack_ops2_bonus.c
t_elem	*pop_elem(t_elem **stack);
void	rotate_stack(t_elem **stack);
void	rev_rotate_stack(t_elem **stack);

// push_swap_ops_bonus.c
void	op_sa(t_info *info);
void	op_sb(t_info *info);
void	op_pa(t_info *info);
void	op_pb(t_info *info);

// rotate_ops_bonus.c
void	op_ra(t_info *info);
void	op_rb(t_info *info);
void	op_rra(t_info *info);
void	op_rrb(t_info *info);

// read_inputs.c
bool	is_valid_op(char *op);
void	read_ops(t_info *info);
void	inputs_to_stack(t_info *info, t_elem **stack, int argc, char **argv);

// execute_ops.c
void	execute_push_swaps(t_info *info, char *op);
void	execute_rotates(t_info *info, char *op);
void	execute_ops(t_info *info);

#endif
