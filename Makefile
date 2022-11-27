# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asasada <asasada@student.42tokyo.j>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/05 19:45:54 by asasada           #+#    #+#              #
#    Updated: 2022/11/05 19:45:54 by asasada          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_DIR	:= src/
SRCS	:= push_swap.c \
			ops.c \
			clean_exit.c \
			stack_utils.c \
			stack_ops.c \
			prep_stack.c \
			math_utils.c \
			printers.c

SRCS	:= $(addprefix $(SRCS_DIR), $(SRCS))
OBJS	:= ${SRCS:.c=.o}

HEADERS :=	./includes/push_swap.h
NAME	:= push_swap

# B_SRCS_DIR	:= bonus/
# B_SRCS		:= push_swap_bonus.c

# B_SRCS	:= $(addprefix $(B_SRCS_DIR), $(B_SRCS))
# B_OBJS	:= ${B_SRCS:.c=.o}

# B_INCLDIR	:=	-I ./bonus/includes
# B_HEADERS	:=	./bonus/includes/solong_bonus.h \
# 				./bonus/includes/math_utils_bonus.h
# B_NAME	:=	so_long_bonus

LIBFT		:= ./libft/libft.a

INCLDIR			:= -I ./includes
LIBFT_INCLDIR	:= -I ./libft
PF_INCLDIR		:= -I ./libft/ft_printf_includes

CC		:= cc
RM		:= rm -f
CFLAGS	:= -Wall -Wextra -Werror

all:		${NAME}

${OBJS}:	${SRCS_DIR}%.o : ${SRCS_DIR}%.c
	${CC} ${CFLAGS} ${INCLDIR} ${LIBFT_INCLDIR} ${PF_INCLDIR} -c $< -o $@

${NAME}:	${OBJS} ${HEADERS} ${LIBFT}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME} ${LIBFT}

${LIBFT}:
	$(MAKE) -C ./libft

clean:
	${RM} ${OBJS} ${B_OBJS}
	$(MAKE) -C ./libft clean

fclean:	clean
	${RM} ${NAME} ${B_NAME}

# ${B_OBJS}:	${B_SRCS_DIR}%.o : ${B_SRCS_DIR}%.c
# 	${CC} ${CFLAGS} ${B_INCLDIR} ${LIBFT_INCLDIR} ${PF_INCLDIR} -c $< -o $@

# ${B_NAME}:	${B_OBJS} ${B_HEADERS} ${LIBFT}
# 	${CC} ${CFLAGS} ${B_OBJS} -o ${B_NAME} ${LIBFT}

# bonus:	${B_NAME}

re:		fclean all

do:		all clean

norm:s
	norminette src includes libft bonus

.PHONY:	all clean fclean re bonus do norm
