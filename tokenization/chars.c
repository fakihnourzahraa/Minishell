/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chars.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 22:12:18 by nfakih            #+#    #+#             */
/*   Updated: 2025/10/04 16:58:33 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

int	word_count_p(t_token *token)
{
	int		i;

	i = 0;
	while (token && token->type != T_EOF && token->type != PIPE)
	{
		if (token->type == WORD)
		{
			i++;
			token = token->next;
		}
		else if (token->type == EMPTY)
		{
			i++;
			token = token->next;
		}
		else
		{
			token = token->next;
		}
	}
	return (i);
}
//i still have an issue here where its taking per tokens not per args

int	word_len_cmds(char *a, int i)
{
	int		j;
	char	b;

	j = 0;
	b = '\0';
	while (a[i] && ((!skipable_space(a[i])) || b != '\0') && 
		   a[i] != '|' && a[i] != '<' && a[i] != '>')
	{
		if (a[i] == '\'' || a[i] == '"')
		{
			if (b == '\0')
				b = a[i];
			else if (b == a[i])
				b = '\0';
		}
		// if (a[i] == '$')
		// {
		// 	i += env_length(a, i);
		// 	j += env_length(a, i);
		// }
		// else
		// {
			i++;
			j++;
		// }
	}
	return (j);
}
int	word_len(char *a, int i)
{
	int		j;
	//char	b;

	j = 0;
	j = 0;
	while (a[i] && ((!skipable_space(a[i]))) && 
		   a[i] != '|' && a[i] != '<' && a[i] != '>')
	{
		// if (a[i] == '\'' || a[i] == '"')
		// {
		// 	if (b == '\0')
		// 		b = a[i];
		// 	else if (b == a[i])
		// 		b = '\0';
		// }
		// else
			j++;
		i++;
	}
	return (j);
}
