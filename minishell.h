/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:10:17 by nour              #+#    #+#             */
/*   Updated: 2025/10/24 12:10:47 by nfakih           ###   ########.fr       */
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
# include "struct.h"
# include "libft/libft.h"
# include "tokenization/tokenization.h"
# include "main/main.h"
# include "builtins/builtin.h"
# include "env/env.h"
# include "exec/exec.h"
# include "expansion/expansion.h"

typedef struct s_token	t_token;
typedef struct s_cmd	t_cmd;
typedef struct s_redir	t_redir;
typedef struct s_env	t_env;
typedef struct s_shell	t_shell;

void	cleanup_in_shell(t_shell *shell);
void	cleanup_shell(t_shell *shell);
void	cleanup_t(t_shell *shell);
void	cleanup_p(t_shell *shell);
void	cleanup_env(t_shell *shell);
void	cleanup_pipeline_resources(t_shell *shell);
#endif
