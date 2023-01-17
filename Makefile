# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: diegofranciscolunalopez <diegofrancisco    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/21 11:24:49 by mtrembla          #+#    #+#              #
#    Updated: 2023/01/14 12:37:56 by diegofranci      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	main.c \
		signals.c \
		parsing.c \
		dlist.c \
		split.c \
		ft_run_comands.c \
		ft_special_commands.c \
		ft_redirect.c \
		free.c \
		str_utils.c \

OBJ = $(SRC:.c=.o)

SDIR = srcs
ODIR = obj
OFIX = $(addprefix $(ODIR)/, $(OBJ))

CC = gcc
CFLAGS =  -g -Wall -Wextra -Werror
RM = rm -fr
LIBFT = ./includes/libft/libft.a
READLINE = ./includes/readline/libreadline.a ./includes/readline/libhistory.a -lreadline -lcurses

$(ODIR)/%.o:$(SDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
# @echo "\033[92m.\033[0m\c"

$(NAME): $(ODIR) $(OFIX)
	@$(MAKE) -C ./includes/libft
	@$(CC) $(CFLAGS) $(OFIX) -o $(NAME) $(LIBFT) $(READLINE)

$(ODIR):
	@mkdir -p $(ODIR)

all: $(NAME)

clean:
	@$(RM) $(OFIX) $(ODIR)
	@echo "🧹"

fclean: clean
	@$(MAKE) all -C ./includes/libft fclean
	@$(RM) $(NAME)

re: fclean all

do_libft:
	@$(MAKE) -C $(D_LIBFT)

do_readline:
	@$(MAKE) -C $(D_LIBFT)

.PHONY: all clean fclean re
