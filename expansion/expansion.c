/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 20:08:42 by nfakih            #+#    #+#             */
/*   Updated: 2025/10/04 20:51:17 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

int	var_length(char	*a, int i)
{
	while (a[i] && a[i] != '$' && a[i] != '"' && !skipable_space(a[i]))
			i++;
	return (i);
}

char	*expand(t_shell *shell, char *s)
{
	int	i;

	if (!expandable(s))
		return (s);
		
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