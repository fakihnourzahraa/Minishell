/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 20:08:42 by nfakih            #+#    #+#             */
/*   Updated: 2025/10/27 09:30:51 by nfakih           ###   ########.fr       */
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

void	iterate_expansion(t_shell *shell)
{
	int		i;
	t_cmd	*current;
	t_redir	*redir;

	current = shell->cmds;
	while (current)
	{
		i = 0;
		current->cmd = expand(shell, current->cmd, false);
		while (current->args && current->args[i])
		{
			i += split_argss(shell, &current, i);
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
