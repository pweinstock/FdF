# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/25 09:46:37 by pweinsto          #+#    #+#              #
#    Updated: 2021/08/25 11:19:18 by pweinsto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRCS_PATH = ./srcs/

GET_NEXT_LINE_PATH = ./includes/get_next_line/

SRCS =	$(SRCS_PATH)fdf.c \
		$(SRCS_PATH)read_data.c \

GET_NEXT_LINE_SRCS =	$(GET_NEXT_LINE_PATH)get_next_line.c \
						$(GET_NEXT_LINE_PATH)get_next_line_utils.c \

LIBFT_PATH	= ./includes/libft/

CC		=		gcc

CFLAGS	=		-Wall -Wextra -Werror

MLXFLAGS =		./minilibx_macos/libmlx.a -framework OpenGL -framework AppKit

all:	target_libft $(NAME)

target_libft:		
			make -C $(LIBFT_PATH)

$(NAME): target_libft
		$(CC) $(CFLAGS) $(MLXFLAGS) -o $(NAME) $(SRCS) $(GET_NEXT_LINE_SRCS) $(LIBFT_PATH)libft.a

clean:
			make clean -C $(LIBFT_PATH)

fclean_libft:
			make fclean -C $(LIBFT_PATH)

fclean:		clean fclean_libft 
			$(RM) $(NAME)

re:			fclean all


