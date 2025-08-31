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
	tools/utils.c

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
