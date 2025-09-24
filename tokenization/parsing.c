/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 22:53:52 by nour              #+#    #+#             */
/*   Updated: 2025/09/25 00:26:25 by nour             ###   ########.fr       */
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
		{
			if (token->type == WORD && token->space == 0)
			{
				while (token && token->space == 0)
					token = token->next;
			}
			else
				token = token->next;
			i++;
		}
		else
			token = token->next;
	}
	return (i);
}
int	parse_word(t_token **t, t_cmd *cmd, int i)
{
	char	*a;
	char	*b;

	if ((*t)->quotes == 1)
		cmd->args[i] =  ft_strtrim((*t)->s, "'");
	else if ((*t)->quotes == 2)
		cmd->args[i] = ft_strtrim((*t)->s, "\"");
	else
		cmd->args[i] = ft_strdup((*t)->s);
	while ((*t)->space == 0 && (*t)->type == WORD && (*t)->next && (*t)->next->type == WORD)
	{
		(*t) = (*t)->next;
		if ((*t)->quotes == 1)
			a =  ft_strtrim((*t)->s, "'");
		else if ((*t)->quotes == 2)
			a = ft_strtrim((*t)->s, "\"");
		else
			a = ft_strdup((*t)->s);
		b = cmd->args[i];
		cmd->args[i] = ft_strjoin(b, a);
		free(a);
		free(b);
	}
	/*if (i == 0)
		cmd->cmd = ft_strdup(cmd->args[0]);
	return (i + 1);*/
	if (i == 0 && cmd->args[0])
	{
		if (cmd->cmd)
			free(cmd->cmd);
		cmd->cmd = ft_strdup(cmd->args[0]);
	}
	return (i + 1);
}

t_token *iterate_token(t_shell *shell, t_token *token, t_cmd **cmd, int *i)
{
	if (!token || !cmd || !*cmd)
		return (token);
	if (token->type == WORD)
		*i = parse_word(&token, *cmd, *i);
	else if (token->type != PIPE)
	{
		fill_r(token, *cmd);
		if (token->next && token->next->type == WORD)
			token = token->next;
	}
	else
	{
		(*cmd)->args[*i] = NULL;
		add_cmd(shell, *cmd);
		token = token->next;
		*cmd = init_cmd(token);
		*i = 0;
		return (token);
	}
	if (token)
		token = token->next;
	return (token);
}

int	parse(t_shell *shell, t_token *token)
{
	//printf("DEBUG: FIRST LINE OF PARSE() REACHED\n");
	int		i;
	t_cmd	*cmd;

	// if (!token || token->type == PIPE || token->type != T_EOF)
	// 	return ;
	if (!token || token->type == PIPE)
		return (-1);
	cmd = init_cmd(token);
	i = 0;
	while (token && token->type != T_EOF)
	{
		token = iterate_token(shell, token, &cmd, &i);
		if (!token && cmd)
			break ;
	}
	// cmd->spaces[i] = 0;
	if(cmd)
	{
		cmd->args[i] = NULL;
		add_cmd(shell, cmd);
	}
	return (1);
}

// FIXED: This function now processes redirections for the CURRENT command only

// void	parse(t_shell *shell, t_token *token)
// {
// 	int		i;
// 	t_cmd	*cmd;

// 	if (!token || token->type != WORD)
// 		return ;
		
// 	cmd = init_cmd(token);
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