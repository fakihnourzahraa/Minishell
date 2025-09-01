/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:10:17 by nour              #+#    #+#             */
/*   Updated: 2025/09/01 08:23:19 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include "libft.h"

typedef struct s_token	t_token;
typedef struct s_cmd	t_cmd;
typedef struct s_redir	t_redir;
typedef struct s_env	t_env;
typedef struct s_shell	t_shell;

typedef	enum	s_token_type
{
	WORD,
	PIPE,
	IN,
	OUT,
	APPEND,
	HEREDOC,
	AND,
	OR,
	T_EOF
}				t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*s;
	bool			quotes;
	t_token			*next;
}				t_token;
//type: command or pipe or direction
//s: the actual string (the words)
//quotes: there or not

typedef enum e_builtin
{
  NOT_BUILTIN,
  BUILTIN_CD,
  BUILTIN_ECHO,
  BUILTIN_ENV,
  BUILTIN_EXIT,
  BUILTIN_EXPORT,
  BUILTIN_PWD,
  BUILTIN_UNSET
} t_builtin;

typedef struct s_cmd
{
	char	**args;
	char	*path;
	t_redir	*rd;
	int		i_fd;
	int		o_fd;
	pid_t	pid;
	t_builtin builtin;
	t_cmd	*next;
}			t_cmd;
//rd: redirections
//i_fd: input fd
//o_fd: output fd
//pid: so we can wait on it later

typedef enum e_r_type
{
  R_IN,
  R_OUT,
  R_APPEND,
  R_HEREDOC
} t_r_type;
typedef struct s_redir
{
	t_r_type	type;
	char		*s;
	int			fd;
	t_redir		*next;
}				t_redir;
//type: input, output, append, or heredoc
//s: filename or heredoc
typedef struct s_env
{
	char	*name;
	char	*val;
	bool	avail;
	t_env	*next;
}			t_env;
//name: before =
//val: after =
//avail: if available to child processes

typedef struct s_shell
{
	t_env	*env;
	t_token	*tkns;
	t_cmd	*cmds;
	char	*in;
	char	**envp;
	int		exit_status;
	bool	exit;
	int		in_h;
	char	*cwd;
	int		*sti;
	int		*sto;
}			t_shell;

//in string immediately from read line
//exit_status: last cmds exit code (for $?)
//exit: if should exit or not
//in_h: in heredoc or not
//current working directory (for pwd builtin)
//sti: original std in fd
//sto: original std out fd

#endif

//nour work on it week 1 
//nour should define struct:t_token, t_cmd, t_redir, t_env, t_shell.