/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:35:18 by nour              #+#    #+#             */
/*   Updated: 2025/10/26 14:49:59 by nour             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

int	unquoted_space(char *str)
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

char	**split_expanded(char *expanded)
{
	char	**split;

	split = ft_split(expanded, ' ');
	free(expanded);
	return (split);
}

void	finalize_args(t_cmd **current, char **new, char **old, char **spl)
{
	if (spl)
		free(spl);
	if (old)
		free(old);
	(*current)->args = new;
}

char	**create_new_args(char **old, char **spl, int i, int *count)
{
	char	**new_args;
	int		org;
	int		split_count;

	split_count = count_args(spl);
	org = count_args(old);
	new_args = malloc(sizeof(char *) * (org + split_count));
	copy_args_segments(new_args, old, spl, i);
	*count = split_count;
	return (new_args);
}

int	split_argss(t_shell *shell, t_cmd **current, int i)
{
	char	*expanded;
	char	**split;
	char	**new_args;
	char	**old_args;
	int		spl;

	expanded = expand(shell, (*current)->args[i], false);
	if (!unquoted_space(expanded))
	{
		(*current)->args[i] = expanded;
		return (1);
	}
	split = split_expanded(expanded);
	if (!split)
		return (1);
	old_args = (*current)->args;
	new_args = create_new_args(old_args, split, i, &spl);
	finalize_args(current, new_args, old_args, split);
	return (spl);
}
