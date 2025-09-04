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

# include "tokenization.h"

int	tokenize_line(t_shell *shell)
{
	char	*a;
	int		i;

	i = 0;
	a = shell->in[i];
	i = skip_spaces(a, i);
	while (a[i])
	{
		shell->tkns = malloc(sizeof(t_token));
		shell->tkns->type = 0;
		i = set_token(shell, a, i);
	}
}
int	set_single(int n,int i, char a, t_token *t)
{
	char	*b;

	b = malloc (sizeof(char) * 2);
	b[0] = a;
	b[1] = '\0';
	t->type = n;
	t->s = b;
	return (i + 1);
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
	return (i + 1);
}

int	set_token(t_shell *shell, char *a, int i)
{
	t_token	*b;

	if ((a[i] == 34 || a[i] == 39))
		i = split_q(a, shell->tkns, i);
	else if (a[i] == '|')
		i = set_single(1, i, '|', shell->tkns);
	else if (a[i] == '>' && a[i + 1] == '>')
		i = set_double(4, '>', shell->tkns, i);
	else if (a[i] == '<' && a[i + 1] == '<')
		i = set_double(5, '<', shell->tkns, i);
	else if (a[i] == '<')
		i = set_single(2, i, '<', shell->tkns);
	else if (a[i] == '>')
		i = set_single(3, i, '>', shell->tkns);
	else
		i = split_word(a, i, shell, 0);
	if (i != -1)
	{
		b = malloc(sizeof(t_token));
		shell->tkns->next = b;
		shell->tkns = shell->tkns->next;
		i = skip_spaces(a, i);
	}
	return (i);
}
//in quotations we can have new lines etc
//skip spaces at the end of each split
//we can also check for the validity of i in is_functions