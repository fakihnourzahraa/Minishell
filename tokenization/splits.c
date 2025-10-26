/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 13:23:45 by nfakih            #+#    #+#             */
/*   Updated: 2025/10/26 09:51:30 by nour             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

int	split_word(char *a, int i, t_shell *shell, t_token **t)
{
	char	*b;
	int		j;
	int		len;

	j = 0;
	if (a[i] && a[i] == '\0')
		return (i);
	i = skip_spaces(a, i);
	len = word_len(a, i);
	if (len == 0)
		return (i);
	b = malloc(sizeof(char) * (len + 1));
	while (len > j)
	{
		if (a[i + j] == '$')
			(*t)->expand = true;
		b[j] = a[i + j];
		j++;
	}
	if (a[i + j] && !skipable_space(a[i + j]))
		(*t)->space = 0;
	b[j] = '\0';
	(*t)->s = b;
	(*t)->type = 0;
	return (add_token(shell, *t), i + j);
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
	if (a[i] == '\'')
		ft_putstr_fd("minishell: syntax error unclosed quote '\n", 2);
	else if (a[i] == '"')
		ft_putstr_fd("minishell: syntax error near unclosed quote \"\n", 2);
	shell->exit_status = 2;
	return (-1);
}

void	fill_t(t_token **t, char *b, char n)
{
	(*t)->s = b;
	(*t)->type = WORD;
	if (n == '\'')
		(*t)->quotes = 1;
	else
		(*t)->quotes = 2;
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
		len++;
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
	fill_t(&t, b, n);
	return (add_token(shell, t), i + len + 1);
}
