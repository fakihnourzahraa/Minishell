/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 22:53:52 by nour              #+#    #+#             */
/*   Updated: 2025/10/04 20:34:17 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "tokenization.h"

int	parse_word(t_token **t, t_cmd *cmd, int i)
{
	char	*a;
	char	*b;
	bool	final;

	if ((*t)->quotes == 1)
		cmd->args[i] =  ft_strtrim((*t)->s, "'");
	else if ((*t)->quotes == 2)
		cmd->args[i] = ft_strtrim((*t)->s, "\"");
	else
		cmd->args[i] = ft_strdup((*t)->s);
	final = (*t)->space;
	while ((*t)->space == 0 && (*t)->next && ((*t)->next->type == WORD || (*t)->next->type == EMPTY))
	{
		(*t) = (*t)->next;
		if ((*t)->quotes == 1)
			a = ft_strtrim((*t)->s, "'");
		else if ((*t)->quotes == 2)
			a = ft_strtrim((*t)->s, "\"");
		else
			a = ft_strdup((*t)->s);
		b = cmd->args[i];
		cmd->args[i] = ft_strjoin(b, a);
		free(a);
		free(b);
		final = (*t)->space;
	}
	cmd->space[i] = final;
	if (i == 0 && cmd->args[0])
	{
		// if (cmd->cmd)
		// 	free(cmd->cmd);
		cmd->cmd = ft_strdup(cmd->args[0]);
	}
	return (i + 1);
}

t_token *iterate_token(t_shell *shell, t_token *token, t_cmd **cmd, int *i)
{
	t_token	*start;

	if (!token || !cmd || !*cmd)
		return (token);
	
	if (token->type == WORD || token->type == EMPTY)
		*i = parse_word(&token, *cmd, *i);
	else if (token->type == PIPE)
	{
		(*cmd)->args[*i] = NULL;
		add_cmd(shell, *cmd);
		token = token->next;
		*cmd = init_cmd(token);
		*i = 0;
		return (token);
	}
	else if (token->type != PIPE && token->type != EMPTY)  // Redirections
	{
		start = token->next;
		fill_r(token, *cmd);
		if (start && (start->type == WORD || start->type == EMPTY))
		{
			token = start;
			while (token && token->space == 0 && token->next && 
				(token->next->type == WORD || token->next->type == EMPTY))
				token = token->next;
		}
	}
	
	if (token)
		token = token->next;
	return (token);
}

// t_token *iterate_token(t_shell *shell, t_token *token, t_cmd **cmd, int *i)
// {
// 	t_token	*start;

// 	if (!token || !cmd || !*cmd)
// 		return (token);
// 	if (token->type == WORD || token->type == EMPTY)
// 		*i = parse_word(&token, *cmd, *i);
// 	// else if (token->type == EMPTY)
// 	// {
// 	// 	(*cmd)->args[*i] = ft_strdup("");
// 	// 	(*cmd)->space[*i] = token->space;
// 	// 	if (*i == 0)
// 	// 		(*cmd)->cmd = ft_strdup("");
// 	// 	(*i)++;
// 	// }
// 	else if (token->type != PIPE && token->type != EMPTY)
// 	{
// 		// fill_r(token, *cmd);
// 		// if (token->next && token->next->type == WORD)
// 		// 	token = token->next;
// 		start = token->next;
// 		fill_r(token, *cmd);
// 		// if (start && start->type == WORD)
// 		// {
// 		// 	token = start;
// 		// 	while (token->space == 0 && token->type == WORD && token->next && token->next->type == WORD)
// 		// 		token = token->next;
// 		// }
// 		if (start && (start->type == WORD || start->type == EMPTY))
// 		{
// 			token = start;
// 			while (token && token->space == 0 && token->next && 
// 				(token->next->type == WORD || token->next->type == EMPTY))
// 				token = token->next;
// 		}
// 	}
// 	// else if (token->type == EMPTY)
// 	// {
// 	// 	(*cmd)->args[*i] = NULL;
// 	// 	add_cmd(shell, *cmd);
// 	// 	token = token->next;
// 	// 	*cmd = init_cmd(token);
// 	// 	*i = 0;
// 	// 	return (token);
// 	// }
// 	if (token)
// 		token = token->next;
// 	return (token);
// }

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
	if(cmd && cmd->args)
	{
		cmd->args[i] = NULL;
		add_cmd(shell, cmd);
	}
	return (1);
}
