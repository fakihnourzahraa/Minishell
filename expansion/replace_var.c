/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 17:51:32 by miwehbe           #+#    #+#             */
/*   Updated: 2025/10/27 10:32:23 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void	quoted(char *a, char *b, int *i, int *j)
{
	char	n;

	n = a[*i];
	(*i)++;
	while (n != '\0' && a[*i])
	{
		if (a[*i] != n)
			b[(*j)++] = a[*i];
		else
			n = '\0';
		(*i)++;
	}
}

void	unquoted(char *a, char *b, int *i, int *j)
{
	while (a[*i] && a[*i] != '\'' && a[*i] != '"')
	{
		b[(*j)++] = a[*i];
		(*i)++;
	}
}

int	h_false(char *s, int i, char *q)
{
	char	a;

	a = *q;
	while (s && s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			a = set_a(a, s[i]);
		else if (s[i] == '$' && a != '\'' && s[i + 1] != '\0'
			&& (isalnum(s[i + 1]) || s[i + 1] == '_' || s[i + 1] == '?'))
		{
			*q = a;
			return (i);
		}
		else if (s[i] == '$' && a == '\0' && s[i + 1] != '\0'
			&& s[i + 2] != '\0' && (s[i + 1] == '\'' || s[i + 1] == '"')
			&& s[i + 1] == s[i + 2])
		{
			*q = a;
			return (i);
		}
		i++;
	}
	*q = a;
	return (-1);
}

int	h_true(char *s, int i)
{
	while (s && s[i])
	{
		if (s[i] == '$' && s[i + 1] != '\0'
			&& (isalnum(s[i + 1]) || s[i + 1] == '_' || s[i + 1] == '?'))
			return (i);
		else if (s[i] == '$' && s[i + 1] != '\0'
			&& s[i + 2] != '\0' && (s[i + 1] == '\'' || s[i + 1] == '"')
			&& s[i + 1] == s[i + 2])
			return (i);
		i++;
	}
	return (-1);
}

int	expand_at(char *s, int i, char *q, bool h)
{
	if (h)
		return (h_true(s, i));
	return (h_false(s, i, q));
}
//returns s[i] = $