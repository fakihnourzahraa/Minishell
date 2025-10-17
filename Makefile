NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Include libft sources directly
LIBFT_SRCS = libft/ft_isalpha.c libft/ft_isdigit.c libft/ft_isalnum.c libft/ft_isascii.c \
       libft/ft_isprint.c libft/ft_strlen.c libft/ft_memset.c libft/ft_bzero.c \
       libft/ft_memcpy.c libft/ft_memmove.c libft/ft_strlcpy.c libft/ft_strlcat.c \
       libft/ft_calloc.c libft/ft_strdup.c libft/ft_toupper.c libft/ft_tolower.c \
       libft/ft_strchr.c libft/ft_strncmp.c libft/ft_memchr.c libft/ft_memcmp.c \
       libft/ft_strnstr.c libft/ft_atoi.c libft/ft_strrchr.c libft/ft_substr.c \
       libft/ft_strjoin.c libft/ft_strtrim.c libft/ft_split.c libft/ft_itoa.c \
       libft/ft_strmapi.c libft/ft_striteri.c libft/ft_putchar_fd.c \
       libft/ft_putstr_fd.c libft/ft_putendl_fd.c libft/ft_putnbr_fd.c\
       libft/ft_strcmp.c libft/ft_strndup.c libft/ft_strcat.c libft/ft_strcpy.c\
       libft/ft_is_numeric.c libft/ft_size_of_arg.c libft/ft_atoll.c

SRCS = main/main.c \
       main/signal.c \
       builtins/echo.c \
       builtins/pwd.c \
       builtins/exit.c \
	   exec/exec_built.c\
       builtins/cd.c\
       builtins/env.c\
	   builtins/envhelp.c\
       builtins/export.c\
       builtins/unset.c\
       builtins/builutils.c\
       exec/buitl.c\
       exec/execute_single.c\
       exec/execute_path.c\
       exec/utilsexec.c\
       exec/redirection.c\
       exec/clean.c\
       exec/redir_utils.c\
       exec/heredoc.c\
       exec/pipeline.c\
       exec/pipeline2.c\
       exec/utils2exec.c\
       exec/pipeutils.c\
       env/envir.c \
       env/envir2.c \
       env/envir3.c \
       env/envir.utils.c expansion/expansion.c \
       tokenization/data_structure.c tokenization/debug.c\
       tokenization/edge.c tokenization/parsing.c tokenization/redir.c\
	   tokenization/splits.c tokenization/chars.c \
       tokenization/token_helpers.c tokenization/token.c\
       cleanup.c expansion/expand_var.c\
       $(LIBFT_SRCS)

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re