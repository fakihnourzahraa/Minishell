/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 20:08:42 by nfakih            #+#    #+#             */
/*   Updated: 2025/10/02 21:30:25 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

int	var_length(char	*a, int i)
{
		while (a[i] && a[i] != '$' && a[i] != '"' && !skipable_space(a[i]))
			i++;
	return (i);
}

int	expand(t_token *tkn, int i)
{
	int		j;
	char	*n;

	n = malloc(sizeof(char) * (var_length(tkn->s, i) + ft_strlen(tkn->s)));
}

void	check_expansion(t_shell *shell, t_token *tkns)
{
	int	i;

	i = 0;
	while (tkns->s[i])
	{
		if (tkns->s[i] == '$')
			i = expand(tkns, i);
		i++;
	}
}
void	iterate_expansion(t_shell *shell)
{
	while (shell->tkns)
	{
		if (shell->tkns->expand)
			expand(shell, shell->tkns);
		shell->tkns = shell->tkns->next;
	}
	
}