/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 22:53:52 by nour              #+#    #+#             */
/*   Updated: 2025/09/11 21:54:49 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "tokenization.h"

int	word_count(t_shell *shell)
{
	t_token *t;
	int		i;

	i = 0;
	t = shell->tkns;
	while (t && t->type != T_EOF)
	{
		if (t->type == WORD)
			i++;
		t = t->next;
	}
	return (i);
}
void	init_args(t_shell *shell, int wc)
{
	shell->cmds->args = malloc(sizeof(char *) * (wc + 1));
	shell->cmds->path =	NULL;
	shell->cmds->rd = NULL;
	shell->cmds->i_fd =	-1;
	shell->cmds->o_fd = -1;
	shell->cmds->pid = -1;
	shell->cmds->builtin = NULL;
}

void	parse(t_shell *shell)
{
	t_token	*token;
	int		i;
	int		wc;
	
	token = shell->tkns;
	if (!token || token->type != WORD)
		return ;
	shell->cmds = malloc(sizeof(t_cmd));
	wc = word_count(shell);
	init_args(shell, wc);
	shell->cmds->cmd = ft_strdup(token->s);
	shell->cmds->args[0] = ft_strdup(token->s);
	i = 1;
	token = token->next;
	while (token && token->type == WORD)
	{
		if (token->quotes == 1)
			shell->cmds->args[i] = ft_strtrim(token->s, "'");
		else if (token->quotes == 2)
			shell->cmds->args[i] = ft_strtrim(token->s, "\"");
		shell->cmds->args[i] = ft_strdup(token->s);
		token = token->next;
		i++;
	}
	fill_r(token, shell);
	shell->cmds->args[i] = NULL;
}

//parses till eof only

//should take the first token
// typedef struct s_cmd
// {
// 	char	*cmd;
// 	char	**args;
// 	char	*path;
// 	t_redir	*rd;
// 	int		i_fd;
// 	int		o_fd;
// 	pid_t	pid;
// 	t_builtin builtin;
// 	t_cmd	*next;
// }			t_cmd;
//rd: redirections
//i_fd: input fd
//o_fd: output fd
//pid: so we can wait on it later