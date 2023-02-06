# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtrembla <mtrembla@student.42quebec>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/21 11:24:49 by mtrembla          #+#    #+#              #
#    Updated: 2023/02/01 15:07:10 by mtrembla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

S_DIR	=	srcs
S_OBJ	=	objs

SUBDIRS		= add_info_comands \
						create_command_array \
						ft_minishell \
						handle_error_pipe \
						main \
						parsing \
						run_comands \
						utils \
						execve \

SRCS_DIRS	= $(foreach dir, $(SUBDIRS), $(addprefix $(S_DIR)/, $(dir)))
OBJS_DIRS	= $(foreach dir, $(SUBDIRS), $(addprefix $(S_OBJ)/, $(dir)))
SRCS		= $(foreach dir, $(SRCS_DIRS), $(wildcard $(dir)/*.c))
OBJS		= $(subst $(S_DIR), $(S_OBJ), $(SRCS:.c=.o))

CC = gcc
CFLAGS =  -g -Wall -Wextra -Werror
RM = rm -fr
LIBFT = ./includes/libft/libft.a

READLINE = ./includes/readline/libreadline.a ./includes/readline/libhistory.a -lreadline -lcurses

$(S_OBJ)/%.o:$(S_DIR)/%.c
	@mkdir -p $(S_OBJ) $(OBJS_DIRS)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "\033[92m.\033[0m\c"

$(NAME): $(OBJS)
	@$(MAKE) all -C ./includes/libft
	@cd ./includes/readline && ./configure
	@$(MAKE) everything -C ./includes/readline
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(READLINE)

$(S_OBJ):
	@mkdir -p $(S_OBJ)

all: $(NAME)

clean:
	@$(RM) $(OFIX) $(S_OBJ)
	@echo "🧹"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C ./includes/libft

re: fclean all

do_libft:
	@$(MAKE) -C $(D_LIBFT)

do_readline:
	@$(MAKE) -C $(D_LIBFT)

.PHONY: all clean fclean re
