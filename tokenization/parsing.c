/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 22:53:52 by nour              #+#    #+#             */
/*   Updated: 2025/09/19 14:04:27 by nfakih           ###   ########.fr       */
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
int	parse_word(t_token *token, t_cmd *cmd, int i)
{
	if (token->quotes == 1)
		cmd->args[i] = ft_strtrim(token->s, "'");
	else if (token->quotes == 2)
		cmd->args[i] = ft_strtrim(token->s, "\"");
	else
		cmd->args[i] = ft_strdup(token->s);
	if (token->space)
		cmd->spaces[i] = 1;
	else
		cmd->spaces[i] = 0;
	return (i + 1);
}

void	parse(t_shell *shell, t_token *token)
{
	int		i;
	t_cmd	*cmd;

	// if (!token || token->type == PIPE || token->type != T_EOF)
	// 	return ;
	if (!token || token->type == PIPE)
		return ;
	cmd = init_cmd(shell, token);
	i = 1;
	token = token->next;
	while (token && token->type != T_EOF)
	{
		if(token->type == WORD)
			i = parse_word(token, cmd, i);
		else if (token->type != PIPE)
		{
			fill_r(token, cmd);
			if (token->next && token->next->type == WORD)
				token = token->next;
		}
		else
		{
			cmd->args[i] = NULL;
			cmd->spaces[i] = 0;
			add_cmd(shell, cmd);
			token = token->next;
			//cmd = cmd->next;
			cmd = init_cmd(shell, token);
			i = 1;
		}
		token = token->next;
	}
	cmd->args[i] = NULL;
	cmd->spaces[i] = 0;
	add_cmd(shell, cmd);
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