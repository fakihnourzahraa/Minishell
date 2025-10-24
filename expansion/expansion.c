/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 20:08:42 by nfakih            #+#    #+#             */
/*   Updated: 2025/10/25 00:50:08 by nour             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

int	var_length(char	*a, int i)
{
	int	j;

	j = i;
	if (a[i] && a[i + 1] && (a[i] == '\'' || a[i] == '"') && a[i] == a[i + 1])
		return (-2);
	if (a[i] && (a[i] == '?' || (a[i] >= '0' && a[i] <= '9')))
		return (1);
	while (a[i] && (ft_isalpha(a[i]) || a[i] == '_'))
		i++;
	if (i == j)
		return (i);
	return (i - j);
}

char	*expand(t_shell *shell, char *s, bool h)
{
	char			q;
	t_expand_data	data;
	char			*old_result;

	data.i = 0;
	q = '\0';
	data.result = s;
	data.i = expand_at(s, data.i, &q, h);
	if (data.i == -1)
		return (s);
	while (data.i != -1)
	{
		data.old_len = var_length(data.result, data.i + 1);
		old_result = data.result;
		handle_expansion(shell, &data);
		free(old_result);
		free(data.new_var);
		data.i = expand_at(data.result, data.i, &q, h);
	}
	return (data.result);
}

void	remove_quotes(t_cmd *current)
{
	int		i;
	t_redir	*redir;

	i = 0;
	if (current->cmd && (ft_strcmp(current->cmd, "") == 0))
		current->cmd = trim(current->cmd);
	while (current->args && current->args[i])
	{
		current->args[i] = trim(current->args[i]);
		i++;
	}
	redir = current->rd;
	while (redir)
	{
		if (redir->s)
			redir->s = trim(redir->s);
		redir = redir->next;
	}
}
void	free_old_args(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
	{
		free(args[i]);
		args[i] = NULL;
		i++;
	}
	if (args)
	{
		free(args);
		args=NULL;
	}
}

int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args && args[count])
		count++;
	return (count);
}

int	has_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

int	has_unquoted_space(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
	while (str[i])
	{
		if (quote == '\0' && (str[i] == '\'' || str[i] == '"'))
			quote = str[i];
		else if (quote != '\0' && str[i] == quote)
			quote = '\0';
		else if (quote == '\0' && str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

static int	copy_args_segments(char **new_args, char **old_args,
								char **split, int i)
{
	int	c;
	int	org;
	int	spl;

	c = 0;
	org = 0;
	while (c < i)
	{
		new_args[c] = ft_strdup(old_args[org]);
		free(old_args[org]);
		c++;
		org++;
	}
	spl = 0;
	while (split && split[spl])
	{
		new_args[c] = ft_strdup(split[spl]);
		free(split[spl]);
		spl++;
		c++;
	}
	org = i + 1;
	while (old_args[org])
	{
		new_args[c] = ft_strdup(old_args[org]);
		free(old_args[org]);
		c++;
		org++;
	}
	new_args[c] = NULL;
	return (c);
}

int	split_argss(t_shell *shell, t_cmd **current, int i)
{
	char	*expanded;
	int		org;
	int		spl;
	char	**old_args;
	char	**split;
	char	**new_args;
	char	*b;

	expanded = expand(shell, (*current)->args[i], false);
	if (!has_unquoted_space(expanded))
	{
		(*current)->args[i] = expanded;
		return (1);
	}
	split = ft_split(expanded, ' ');
	free(expanded);
	if (!split)
		return (1);
	spl = count_args(split);
	org = count_args((*current)->args);
	new_args = malloc(sizeof(char *) * (org + spl));
	old_args = (*current)->args;
	copy_args_segments(new_args, old_args, split, i);
	if (split)
		free(split);
	if (old_args)
		free(old_args);
	(*current)->args = new_args;
	return (spl);
}

void	iterate_expansion(t_shell *shell)
{
	int		i;
	t_cmd	*current;
	t_redir	*redir;

	current = shell->cmds;
	while (current)
	{
		i = 0;
		if (current->cmd)
			current->cmd = expand(shell, current->cmd, false);
		while (current->args && current->args[i])
		{
			i +=  split_argss(shell, &current, i);
		}
		redir = current->rd;
		while (redir)
		{
			if (redir->s && redir->type != R_HEREDOC)
				redir->s = expand(shell, redir->s, false);
			redir = redir->next;
		}
		remove_quotes(current);
		current = current->next;
	}
}
