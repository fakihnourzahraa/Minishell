/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 22:53:52 by nour              #+#    #+#             */
/*   Updated: 2025/09/16 11:19:55 by nour             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "tokenization.h"

int	word_count(t_token *token)
{
	int		i;

	i = 0;
	while (token && token->type != T_EOF && token->type != PIPE)
	{
		if (token->type == WORD)
			i++;
		token = token->next;
	}
	return (i);
}
void	add_cmd(t_shell *shell, t_cmd *cmd)
{
	t_cmd	*cur;

	if (!shell->cmds)
		shell->cmds = cmd;
	else
	{
		cur = shell->cmds;
		while (cur->next)
			cur = cur->next;
		cur->next = cmd;
	}
}
t_cmd	*init_cmd(t_shell *shell, t_token *t)
{
	int	wc;
	t_cmd	*cmd;
	
	wc = word_count(t);
	cmd = malloc(sizeof(t_cmd));
	cmd->args = malloc(sizeof(char *) * (wc + 1));
	cmd->path =	NULL;
	cmd->rd = NULL;
	cmd->i_fd =	-1;
	cmd->o_fd = -1;
	cmd->pid = -1;
	cmd->builtin = (t_builtin)NULL;
	cmd->next = NULL;
	return (cmd);
}

void	parse(t_shell *shell, t_token *token)
{
	int		i;
	t_cmd	*cmd;

	if (!token || token->type != WORD)
		return ;
	cmd = init_cmd(shell, token);
	cmd->cmd = ft_strdup(token->s);
	cmd->args[0] = ft_strdup(token->s);
	i = 1;
	token = token->next;
	while (token && token->type != T_EOF)
	{
		if(token->type == WORD)
		{
			if (token->quotes == 1)
				cmd->args[i] = ft_strtrim(token->s, "'");
			else if (token->quotes == 2)
				cmd->args[i] = ft_strtrim(token->s, "\"");
			else
				cmd->args[i] = ft_strdup(token->s);
			i++;
			token = token->next;
		}
		else if (token->type != PIPE)
		{
			fill_r(token, cmd);
			token = token->next;
			if (token && token->type == WORD)
				token = token->next;
		}
		else
		{
			cmd->args[i] = NULL;
			add_cmd(shell, cmd);
			token = token->next;
			cmd = cmd->next;
			cmd = init_cmd(shell, token);
			cmd->cmd = ft_strdup(token->s);
			cmd->args[0] = ft_strdup(token->s);
			i = 1;
			token = token->next;
		}
	}
	cmd->args[i] = NULL;
	add_cmd(shell, cmd);
	// if (token && token->type == PIPE)
	// {
	// 	token = token->next;
	// 	parse(shell, token);
	// }
	
}

// FIXED: This function now processes redirections for the CURRENT command only

// void	parse(t_shell *shell, t_token *token)
// {
// 	int		i;
// 	t_cmd	*cmd;

// 	if (!token || token->type != WORD)
// 		return ;
		
// 	cmd = init_cmd(shell, token);
// 	if (!cmd)
// 		return;
		
// 	cmd->cmd = ft_strdup(token->s);
// 	cmd->args[0] = ft_strdup(token->s);
// 	i = 1;
// 	token = token->next;
	
// 	// FIXED: Process tokens for THIS command only (until PIPE or EOF)
// 	while (token && token->type != T_EOF && token->type != PIPE)
// 	{
// 		if (token->type == WORD)
// 		{
// 			if (token->quotes == 1)
// 				cmd->args[i] = ft_strtrim(token->s, "'");
// 			else if (token->quotes == 2)
// 				cmd->args[i] = ft_strtrim(token->s, "\"");
// 			else
// 				cmd->args[i] = ft_strdup(token->s);
// 			i++;
// 			token = token->next;
// 		}
// 		else if (token->type == IN || token->type == OUT || 
// 				 token->type == APPEND || token->type == HEREDOC)
// 		{
// 			// FIXED: Store redirection token and get filename token
// 			t_token *redir_token = token;
// 			token = token->next; // Move to filename token
			
// 			if (token && token->type == WORD)
// 			{
// 				// Add redirection with both tokens
// 				fill_r_for_cmd(redir_token, token, cmd);
// 				token = token->next; // Skip filename token
// 			}
// 			else
// 			{
// 				// Invalid syntax - redirection without filename
// 				// Still need to advance token to avoid infinite loop
// 				if (token)
// 					token = token->next;
// 			}
// 		}
// 		else
// 		{
// 			token = token->next;
// 		}
// 	}
	
// 	cmd->args[i] = NULL;
// 	add_cmd(shell, cmd);
	
// 	// FIXED: If we hit a PIPE, recursively parse the next command
// 	if (token && token->type == PIPE)
// 	{
// 		token = token->next; // Skip the PIPE token
// 		parse(shell, token);  // Parse next command after pipe
// 	}
// }

//extra token.next so it skips filename

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