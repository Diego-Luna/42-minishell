# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dluna-lo <dluna-lo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/21 11:24:49 by mtrembla          #+#    #+#              #
#    Updated: 2023/02/06 17:38:23 by dluna-lo         ###   ########.fr        #
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

SRCS = srcs/utils/debug.c srcs/utils/free_utils.c srcs/utils/free.c \
				srcs/utils/ft_clean_space_str.c srcs/utils/ft_only_str_isalnum.c \
				srcs/utils/split.c srcs/utils/str_utils.c srcs/utils/tables_utils.c \
				srcs/run_comands/ft_env_export.c srcs/run_comands/ft_process_comand.c \
				srcs/run_comands/ft_process_comands_utils.c  \
				srcs/run_comands/ft_process_comands.c \
				srcs/run_comands/ft_redirect_utils.c  srcs/run_comands/ft_redirect.c \
				srcs/run_comands/ft_run_comands.c srcs/run_comands/utils.c \
				srcs/parsing/dlist.c srcs/parsing/ft_init_state.c \
				srcs/parsing/parsing.c srcs/parsing/signals.c srcs/main/main.c \
				srcs/handle_error_pipe/ft_handle_error_pipe.c \
				srcs/ft_minishell/check_pipes.c srcs/ft_minishell/env.c \
				srcs/ft_minishell/ft_minishell.c srcs/ft_minishell/ft_run_comand_build.c \
				srcs/ft_minishell/our_commands.c srcs/ft_minishell/utils.c \
				srcs/execve/ft_execve.c \
				srcs/create_command_array/ft_cmd_args_in_redirection.c \
				srcs/create_command_array/ft_content_tokens.c \
				srcs/create_command_array/ft_create_command_array_utils.c \
				srcs/create_command_array/ft_create_command_array.c \
				srcs/create_command_array/ft_create_t_redirection.c \
				srcs/create_command_array/ft_position_in_token.c \
				srcs/create_command_array/ft_save_token.c \
				srcs/create_command_array/utils.c \
				srcs/add_info_comands/ft_add_info_comands_utils.c \
				srcs/add_info_comands/ft_add_info_comands.c \
				srcs/add_info_comands/ft_handle_env_varibles_utils.c \


SRCS_DIRS	= $(foreach dir, $(SUBDIRS), $(addprefix $(S_DIR)/, $(dir)))
OBJS_DIRS	= $(foreach dir, $(SUBDIRS), $(addprefix $(S_OBJ)/, $(dir)))

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
