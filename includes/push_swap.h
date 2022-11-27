/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:44:30 by asasada           #+#    #+#             */
/*   Updated: 2022/11/27 15:59:51 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdbool.h>
# include <stdlib.h>
# include "libft.h"
# include "ft_printf.h"

# define ERROR -1

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
	size_t			pos;
	int				move_b_cost;
}	t_elem;

typedef struct s_info
{
	t_elem	*stack_a;
	t_elem	*stack_b;
	t_elem	*stack_t;
	t_list	*ops;
	
	long	min;
	long	median;
	long	max;
	size_t	stack_t_len;
}	t_info;

void	clean_exit(t_info *info, int exit_code);


void	swap(t_elem **stack);
void	elem_add_front(t_elem *new, t_elem **stack);
t_elem	*pop_elem(t_elem **stack);
void	rotate_stack(t_elem **stack);
void	rev_rotate_stack(t_elem **stack);
int	insert_op_to_list(t_list **list, int op);


void	op_sa(t_info *info);
void	op_sb(t_info *info);
void	op_pa(t_info *info);
void	op_pb(t_info *info);
void	op_ra(t_info *info);
void	op_rb(t_info *info);
void	op_rra(t_info *info);
void	op_rrb(t_info *info);



#endif
