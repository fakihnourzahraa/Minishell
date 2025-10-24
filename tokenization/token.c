/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:32:47 by nour              #+#    #+#             */
/*   Updated: 2025/09/02 13:32:47 by nour             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

int	set_token(t_shell *shell, char *a, int i)
{
	t_token	*n;

	i = skip_spaces(a, i);
	if ((a[i] == 34 || a[i] == 39))
		return (split_q(a, shell, i));
	n = init_token();
	if (a[i] == '|')
		i = set_single(1, i, '|', n);
	else if (a[i] == '>' && a[i + 1] == '>')
		i = set_double(4, '>', n, i);
	else if (a[i] == '<' && a[i + 1] == '<')
		i = set_double(5, '<', n, i);
	else if (a[i] == '<')
		i = set_single(2, i, '<', n);
	else if (a[i] == '>')
		i = set_single(3, i, '>', n);
	else
		return (split_word(a, i, shell, &n));
	add_token(shell, n);
	i = skip_spaces(a, i);
	return (i);
}
//in quotations we can have new lines etc
//skip spaces at the end of each split

t_token	*init_token(void)
{
	t_token	*n;

	n = malloc(sizeof(t_token));
	n->type = T_EOF;
	n->s = NULL;
	n->quotes = 0;
	n->next = NULL;
	n->space = 1;
	n->expand = false;
	return (n);
}

void	add_token(t_shell *shell, t_token *n)
{
	t_token	*cur;

	if (!shell->tkns)
		shell->tkns = n;
	else
	{
		cur = shell->tkns;
		while (cur->next)
			cur = cur->next;
		cur->next = n;
	}
}

void	cleanup_token(t_shell *shell)
{
	t_token	*t;

	while (shell->tkns && shell->tkns->s)
	{
		free(shell->tkns->s);
		t = shell->tkns;
		shell->tkns = shell->tkns->next;
		free(t);
	}
}

int	tokenize_line(t_shell *shell)
{
	char	*a;
	int		i;
	int		j;
	t_token	*t;

	a = shell->in;
	i = skip_spaces(a, 0);
	while (a[i])
	{
		j = i;
		i = set_token(shell, a, i);
		if (i == -1)
			return (cleanup_token(shell), -1);
		i = skip_spaces(a, i);
		if (a[i] == '\0' || j == i)
			break ;
	}
	t = init_token();
	add_token(shell, t);
	return (1);
}
//init token intialized it to eof