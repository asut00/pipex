# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asuteau <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/04 15:07:07 by asuteau           #+#    #+#              #
#    Updated: 2024/07/04 15:07:08 by asuteau          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -------------------------------- VARIABLES --------------------------------- #

NAME		= 	pipex

SRC			= 	src/pipex_main.c \
				src/pipex_utils/pipex_utils.c \
				src/pipex_utils/ft_split_spe.c \
				src/pipex_utils/ft_strjoin_spe.c \
				src/pipex_utils/ft_atoi.c \
				src/pipex_utils/ft_strdup_and_cat.c \
				src/get/get_filepaths.c \
				src/get/get_path_var.c \
				src/get/get_cmdpaths.c \
				src/get/get_and_write_heredoc.c \
				src/get/get_handlers.c \
				src/forks/forks.c \
				src/forks/forks_special_cases.c \
				src/garbage_collector/garbage_collector.c \
				src/garbage_collector/ft_lstclear.c \
				src/init_and_finish/init_and_finish.c \
				src/init_and_finish/close.c \
				src/get_next_line/get_next_line.c \
				src/get_next_line/get_next_line_utils.c

INCL_DIR	=	./inc

OBJECTS		= 	$(SRC:.c=.o)

CC			= 	cc

CFLAGS		= 	-Wall -Wextra -Werror #-fsanitize=address #-g3 

# ---------------------------------- RULES ----------------------------------- #

.c.o:	
			$(CC) $(CFLAGS) -I $(INCL_DIR) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJECTS)
			$(CC) $(CFLAGS) -I $(INCL_DIR) -o $(NAME) $(OBJECTS)

bonus:		$(NAME)

all: 		$(NAME)

clean:
			rm -f $(OBJECTS)

fclean: 	clean
			rm -f $(NAME)

re: 		fclean all

.PHONY: 	all clean fclean re
