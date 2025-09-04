/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 13:41:44 by nfakih            #+#    #+#             */
/*   Updated: 2025/09/04 13:36:11 by nour             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "tokenization.h"

int	word_len(char *a, int i)
{
	int	j;

	j = 0;
	while (a[i] && skipable_space(a[i]))
	{
		i++;
		j++;
	}
	return (j);
}
int	split_word(char *a, int i, t_shell *shell)
{
	char	*b;
	int		j;
	
	j = 0;
	skip_spaces(a, i);
	b = malloc(sizeof(char) * (word_len(a, i) + 1));
	while (!skipable_space(a[i]))
	{
		b[j] = a[i];
		i++;
		j++;
	}
	b[j] = '\0';
	shell->tkns->s = b;
	shell->tkns->type = 0;
	return (i);
}
