/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:44:30 by asasada           #+#    #+#             */
/*   Updated: 2022/11/27 12:47:31 by asasada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdbool.h>
# include <stdlib.h>
# include "libft.h"
# include "ft_printf.h"

# define ERROR -1

typedef struct s_elem
{
	struct s_elem	*prev;
	struct s_elem	*next;
	long			num;
	bool			need_sort;
	bool			is_end;
	int				pos;
	int				move_b_cost;
}	t_elem;

typedef struct s_info
{
	t_elem	*stack_a;
	t_elem	*stack_b;
	t_elem	*stack_t;
	t_list	**ops;
	int		a_len;
	int		b_len;

}	t_info;

#endif
