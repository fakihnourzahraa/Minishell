/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 22:53:52 by nour              #+#    #+#             */
/*   Updated: 2025/10/17 13:53:33 by nour             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

int	parse_word(t_token **t, t_cmd *cmd, int i)
{
	char	*a;
	char	*b;
	bool	final;

	cmd->args[i] = ft_strdup((*t)->s);
	final = (*t)->space;
	while ((*t)->space == 0 && (*t)->next && ((*t)->next->type == WORD
			|| (*t)->next->type == EMPTY))
	{
		(*t) = (*t)->next;
		a = ft_strdup((*t)->s);
		b = cmd->args[i];
		cmd->args[i] = ft_strjoin(b, a);
		free(a);
		free(b);
		final = (*t)->space;
	}
	cmd->space[i] = final;
	if (i == 0 && cmd->args[0])
		cmd->cmd = ft_strdup(cmd->args[0]);
	return (i + 1);
}

void	help_iterate(t_token **start, t_token **token, t_cmd **cmd)
{
	(*start) = (*token)->next;
	fill_r((*token), *cmd);
	if ((*start) && ((*start)->type == WORD || (*start)->type == EMPTY))
	{
		(*token) = (*start);
		while ((*token) && (*token)->space == 0 && (*token)->next
			&& ((*token)->next->type == WORD || (*token)->next->type == EMPTY))
			(*token) = (*token)->next;
	}
}

t_token	*iterate_token(t_shell *shell, t_token *token, t_cmd **cmd, int *i)
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
	else if (token->type != PIPE && token->type != EMPTY)
		help_iterate(&start, &token, cmd);
	if (token)
		token = token->next;
	return (token);
}

int	parse(t_shell *shell, t_token *token)
{
	int		i;
	t_cmd	*cmd;

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
	if (cmd && cmd->args)
	{
		cmd->args[i] = NULL;
		add_cmd(shell, cmd);
	}
	return (1);
}
