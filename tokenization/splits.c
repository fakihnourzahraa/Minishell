/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 13:23:45 by nfakih            #+#    #+#             */
/*   Updated: 2025/10/02 20:31:55 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "tokenization.h"

int	split_word(char *a, int i, t_shell *shell, t_token *n)
{
	char	*b;
	int		j;
	t_token	*t;
	int		len;
	
	j = 0;
	if (a[i] && a[i] == '\0')
		return (i);
	t = n;
	i = skip_spaces(a, i);
	len = word_len(a, i);
	if (len == 0)
		return (i);
	b = malloc(sizeof(char) * (len + 1));
	while (len > j)
	{
		if (a[i + j] == '$')
			t->expand = true;
		b[j] = a[i + j];
		j++;
	}
	if (a[i + j] && a[i + j] != 32)
		t->space = 0;
	b[j] = '\0';
	t->s = b;
	t->type = 0;
	add_token(shell, t);
	return (i + j);
}

int	split_q(char *a, t_shell *shell, int i)
{
	int	j;

	j = i + 1;
	while (a[j])
	{
		if (a[j] == a[i])
		{
			if (j == i + 1)
				return (empty_token(a, shell, i), i + 2);
			return (split_quote(a, i, shell, a[i]));
		}
		j++;
	}
	return (-1);
}
int	split_quote(char *a, int i, t_shell *shell, char n)
{
	char	*b;
	int		j;
	int		len;
	t_token	*t;

	i++;
	len = 0;
	while (a[i + len] && a[i + len] != n)
	{
		// if (n == '"' && a[i + len] == '$')
		// 	len = env_length(a, i + len);
		// else
		len++;
	}
	b = malloc(sizeof(char) * (len + 3));
	b[0] = n;
	j = -1;
	t = init_token();
	while (++j < len)
	{
		if (n == '"' && a[i + j] == '$')
			t->expand = true;
		b[j + 1] = a[i + j];
	}
	if (a[j + 1 + i] && !skipable_space(a[j + 1 + i]))
		t->space = false;
	b[len + 1] = n;
	b[len + 2] = '\0';
	t->s = b;
	t->type = WORD;
	t->quotes = (n == '\'') ? 1 : 2;
	add_token(shell, t);
	return (i + len + 1);
}

