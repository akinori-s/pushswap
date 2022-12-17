/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:44:30 by asasada           #+#    #+#             */
/*   Updated: 2022/12/17 16:41:16 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdbool.h>
# include <stdlib.h>
# include "libft.h"
# include "ft_printf.h"

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

	int		argc;

	long	min;
	long	median;
	long	max;
	size_t	max_pos;
	size_t	stack_t_len;
	size_t	need_sort_count;
}	t_info;

typedef struct s_cost
{
	size_t	ra;
	size_t	rb;
	size_t	rra;
	size_t	rrb;
	size_t	cost;
}	t_cost;

// clean_exit.c
void	free_stack(t_elem *stack);
void	clean_exit(t_info *info, int exit_code);

// stack_utils.c
t_elem	*new_elem(long num);
size_t	index_of_stack(t_elem *stack, long num);
size_t	stacklen(t_elem *stack);
long	stackmaxnum(t_elem *stack);
long	stackminnum(t_elem *stack);

// prep_stack.c
void	apply_arr_to_stack(long *arr, t_elem *stack);
void	sort_long_arr(long *arr, size_t arr_size);
int	sort_tmp_stack(t_elem *stack);
int	check_duplicates(t_elem	*sorted);
void	map_sorted_to_stack(t_elem *sorted, t_elem *stack, size_t sorted_len);

// stack_ops.c
void	swap(t_elem **stack);
void	elem_add_back(t_elem *new, t_elem **stack);
void	elem_add_front(t_elem *new, t_elem **stack);
t_elem	*pop_elem(t_elem **stack);
void	rotate_stack(t_elem **stack);
void	rev_rotate_stack(t_elem **stack);

// printers.c
void	print_stack_elem(t_elem *stack);
void	print_elem(t_elem *elem);
void	print_stack(t_elem *stack, bool extra);
void	print_best_cost(t_cost *cost);
void	print_stacks(t_elem *stack_a, t_elem *stack_b, bool extra);
void	print_calc_cost(t_cost *cost, long num, long pos, bool is_b);
void	print_ops(t_list *lst, bool debug);
void	print_lis(t_elem *lst);

// math_utils.c
size_t	min_st(size_t a, size_t b);
size_t	max_st(size_t a, size_t b);
long	abs_long(long a);
long	min_long(long a, long b);
long	max_long(long a, long b);

// stack_ops.c
void	swap(t_elem **stack);
void	elem_add_front(t_elem *new, t_elem **stack);
t_elem	*pop_elem(t_elem **stack);
void	rotate_stack(t_elem **stack);
void	rev_rotate_stack(t_elem **stack);

// cost.c
void	calc_min_cost_tool(t_cost *c);
size_t	calc_min_cost(t_cost *c);
void	copy_cost(t_cost *to, t_cost *from);

// push_backto_a.c
void	do_move_elem_b(t_info *info, t_cost *cost);
long	calc_pos_bigger_b(t_info *info, t_elem *to, t_elem *elem);
size_t	calc_dest_index_b(t_info *info, t_elem *to, t_elem *elem);
void	calc_cost_b(t_cost *cost, t_elem *elem, t_info *info);
void	move_elem_b(t_info *info, t_elem *from);

// ops_compression.c
void	join_rr(t_info *info, size_t i, size_t n);
void	join_r(t_info *info, size_t i, size_t n);
int		join_rev_rotates(t_info *info, size_t i, size_t j);
int		join_rotates(t_info *info, size_t i, size_t j);
void	compress_ops(t_info *info);

// calc_longest_increasing_subseq.c
void	calc_longest_increasing_subsequence(t_info *info);

// ops_utils.c
int	insert_op_to_list(t_list **list, int op);

// sort_few.c
// void	sort_few();

void	op_sa(t_info *info);
void	op_sb(t_info *info);
void	op_pa(t_info *info);
void	op_pb(t_info *info);
void	op_ra(t_info *info);
void	op_rb(t_info *info);
void	op_rra(t_info *info);
void	op_rrb(t_info *info);



#endif
