/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 20:08:42 by nfakih            #+#    #+#             */
/*   Updated: 2025/10/04 21:22:44 by nour             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

int	var_length(char	*a, int i)
{
	while (a[i] && a[i] != '$' && (!skipable_space(a[i])) && 
		   a[i] != '|' && a[i] != '<' && a[i] != '>')
			i++;
	return (i);
}
int	expandable(char *s, int	i, char	*q)
{
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			if (q == '\0')
				q = s[i];
			else if (q == s[i])
				q = '\0';
		}
		if (s[i] == '$' && (q == '"' || q == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

char	*expand(t_shell *shell, char *s)
{
	int		i;
	char	*q;
	char	*var;
	char	*news;
	int		j;
	int		z;

	i = 0;
	q = malloc(sizeof(char));
	q = "\0";
	i = expandable(s, i, q);
	if (i == -1)
		return (free(q), s);
	while (i != -1)
	{
		z = 0;
		j = var_length(s, i + 1);
		var = malloc(sizeof(char) * (j + 1));
		while (z < j)
		{
			var[z] = s[i];
			z++;
		}
		var[z] = '\0';
		news = expand_variable(shell, var);
		s
		free(var);
		i = expandable(s, i, q);
	}
	free(q);
}

void	iterate_expansion(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->cmds)
	{
		shell->cmds->cmd = expand(shell, shell->cmds->cmd);
		while (shell->cmds->args[i])
		{
			i++;
			
		}
	}
	
}