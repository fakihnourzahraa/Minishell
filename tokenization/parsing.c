/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 22:53:52 by nour              #+#    #+#             */
/*   Updated: 2025/09/08 19:28:28 by nour             ###   ########.fr       */
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
		t = t->next;
		i++;
	}
	return (i);
}

void	parse(t_shell *shell)
{
	t_token	*token;
	int		i;
	
	token = shell->tkns;
	if (!token || token->type != WORD)
		return ;
	shell->cmds = malloc(sizeof(t_cmd));
	shell->cmds->args = malloc(sizeof(char *) * (word_count(shell) + 1));
	shell->cmds->cmd = ft_strdup(token->s);
	shell->cmds->args[0] = ft_strdup(token->s);
	i = 1;
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