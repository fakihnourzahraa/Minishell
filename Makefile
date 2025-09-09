NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = -L libft -lft


SRCS = main/main.c \
       main/signal.c \
       builtins/echo.c \
       builtins/pwd.c \
       builtins/exit.c \
       exec/buitl.c\
       exec/execute_single.c\
       exec/execute_path.c\
       exec/utilsexec.c\
       exec/redirection.c\
       exec/redir_utils.c\
       exec/heredoc.c\
       exec/pipeline.c\
       exec/pipeline2.c\
       exec/utils2exec.c\
       exec/pipeutils.c
     

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L libft -lft -lreadline -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
