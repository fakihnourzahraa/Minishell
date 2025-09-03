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

#include "parsing.h"

int	tokenize_line(t_shell *shell)
{
	char	*a;
	int		i;

	i = 0;
	a = shell->in[i];
	i = skip_spaces(a, i);
	while (a[i])
	{
		shell->tkns = malloc(sizeof(t_token) + 1);
		set_tokens(shell, a, i, false);
		i = skip_spaces(a, i);
		i++;
	}
}
void	set_single(int n, char a, t_token *t)
{
	char	*b;

	b = malloc (sizeof(char) * 2);
	b[0] = a;
	b[1] = '\0';
	t->type = n;
	t->s = b;
	t->quotes = 0;
}
int	set_double(int n, char a, t_token *t, int i)
{
	char	*b;

	b = malloc (sizeof(char) * 3);
	b[0] = a;
	b[1] = a;
	b[2] = '\0';
	t->type = n;
	t->s = b;
	t->quotes = 0;
	return (i + 1);
}

int	set_tokens(t_shell *shell, char *a, int i, bool in_q)
{
	shell->tkns->type = in_q;
	if (!in_q && (a[i] == 34 || a[i] == 39))
		i = split_q(a, shell->tkns, i);
	else if (a[i] == '|')
		set_single(1, '|', shell->tkns);
	else if (a[i] == '>' && a[i + 1] == '>' && i++)
		i = set_double(4, '>', shell->tkns, i);
	else if (a[i] == '<' && a[i + 1] == '<' && i++)
		i = set_double(5, '<', shell->tkns, i);
	else if (a[i] == '<')
		set_single(2, '<', shell->tkns);
	else if (a[i] == '>')
		set_single(3, '>', shell->tkns);
	else
		i = split_word(a, i, shell->tkns);
	shell->tkns = shell->tkns->next;
}
//in quotations we can have new lines etc
//skip spaces at the end of each split
//we can also check for the validity of i in is_functions