# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/21 11:24:49 by mtrembla          #+#    #+#              #
#    Updated: 2023/01/20 16:50:03 by dluna-lo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# SRC =	main.c \
# 		signals.c \
# 		parsing.c \
# 		dlist.c \
# 		split.c \
# 		ft_special_commands.c \
# 		ft_redirect.c \
# 		free.c \
# 		str_utils.c \
# 		tables_utils.c \
# 		ft_init_state.c \
# 		0_ft_minishell.c \
# 		10_ft_create_command_array.c \
# 		11_ft_create_command_array.c \
# 		12_ft_create_command_array.c \
# 		20_ft_add_info_comands.c \
# 		30_ft_run_comands.c \
# 		31_ft_run_comands.c \
# 		32_ft_run_comands.c \
# 		40_ft_handle_error_pipe.c \
# 		env.c \

# OBJ = $(SRC:.c=.o)

# SDIR = srcs
# ODIR = obj
# OFIX = $(addprefix $(ODIR)/, $(OBJ))

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
