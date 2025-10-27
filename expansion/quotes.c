/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:29:11 by nfakih            #+#    #+#             */
/*   Updated: 2025/10/27 09:31:13 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static void	trim_cmd(t_cmd *current)
{
	char	*temp;

	if (!current->cmd || ft_strcmp(current->cmd, "") == 0)
		return ;
	if (current->cmd[0] == '\'' || current->cmd[0] == '"')
	{
		temp = current->cmd;
		if (current->cmd[0] == '\'')
			current->cmd = ft_strtrim(current->cmd, "'");
		else
			current->cmd = ft_strtrim(current->cmd, "\"");
		free(temp);
	}
}

static void	trim_args(t_cmd *current)
{
	char	*temp;
	int		i;

	i = 0;
	while (current->args && current->args[i])
	{
		if (current->args[i][0] == '\'' || current->args[i][0] == '"')
		{
			temp = current->args[i];
			if (current->args[i][0] == '\'')
				current->args[i] = ft_strtrim(current->args[i], "'");
			else
				current->args[i] = ft_strtrim(current->args[i], "\"");
			free(temp);
		}
		i++;
	}
}

static void	trim_redir(t_redir *redir)
{
	char	*temp;

	while (redir)
	{
		if (redir->s && (redir->s[0] == '\'' || redir->s[0] == '"'))
		{
			temp = redir->s;
			if (redir->s[0] == '\'')
				redir->s = ft_strtrim(redir->s, "'");
			else
				redir->s = ft_strtrim(redir->s, "\"");
			free(temp);
		}
		redir = redir->next;
	}
}

void	remove_quotes(t_cmd *current)
{
	trim_cmd(current);
	trim_args(current);
	trim_redir(current->rd);
}
