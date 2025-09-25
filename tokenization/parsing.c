/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 22:53:52 by nour              #+#    #+#             */
/*   Updated: 2025/09/25 22:22:08 by nfakih           ###   ########.fr       */
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
	while ((*t)->space == 0 && (*t)->type == WORD && (*t)->next && (*t)->next->type == WORD)
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
	if (!token || !cmd || !*cmd)
		return (token);
	if (token->type == WORD)
		*i = parse_word(&token, *cmd, *i);
	else if (token->type == EMPTY)
	{
		(*cmd)->args[*i] = ft_strdup("");
		(*cmd)->space[*i] = token->space;
		if (*i == 0)
			(*cmd)->cmd = ft_strdup("");
		(*i)++;
	}
	else if (token->type != PIPE && token->type != EMPTY)
	{
		fill_r(token, *cmd);
		if (token->next && token->next->type == WORD)
			token = token->next;
	}
	else if (token->type != EMPTY)
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
	if(cmd && cmd->args)
	{
		cmd->args[i] = NULL;
		add_cmd(shell, cmd);
	}
	return (1);
}
