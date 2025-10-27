# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/24 13:03:30 by nfakih            #+#    #+#              #
#    Updated: 2025/10/24 13:03:30 by nfakih           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = main/main.c \
       main/signal.c \
       main/processing.c \
       builtins/echo.c \
       builtins/pwd.c \
       builtins/exit.c \
       builtins/cd.c \
       builtins/env.c \
       builtins/envhelp.c \
       builtins/export.c \
       builtins/unset.c \
       builtins/builutils.c \
       exec/exec_built.c \
       exec/buitl.c \
       exec/execute_single.c \
       exec/execute_path.c \
       exec/utilsexec.c \
       exec/redirection.c \
       exec/clean.c \
       exec/redir_utils.c \
       exec/heredoc.c \
       exec/heredoc_util.c \
       exec/heredoc_util2.c \
       exec/redirecttion_utils.c \
       exec/exec_single_help.c \
       exec/exec_single_help2.c \
       exec/multcmnd.c \
       exec/pipeline.c \
       exec/pipeline2.c \
       exec/utils2exec.c \
       exec/pipeutils.c \
       exec/exec_pip.c \
       exec/input_redr.c \
       exec/output_redr.c \
       exec/some_utils.c \
       env/envir.c \
       env/envir2.c \
       env/envir3.c \
       env/envir.utils.c \
       expansion/expansion.c \
       expansion/expand_var.c \
       expansion/trim.c \
       expansion/replace_var.c \
       tokenization/data_structure.c \
       tokenization/edge.c \
       tokenization/parsing.c \
       tokenization/redir.c \
       tokenization/splits.c \
       tokenization/chars.c \
       tokenization/token_helpers.c \
       tokenization/token.c \
       cleanup.c \
       expansion/split_help.c\
       expansion/segments.c\
	   expansion/quotes.c\
       cleanup_two.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re