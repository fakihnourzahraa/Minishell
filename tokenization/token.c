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

int	set_single(int n, int i, char a, t_token *t)
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

int	split_q(char *a, t_shell *shell, int i)
{
	int	z;
	int	j;

	z = i;

	j = z + 1;
	while (a[j])
	{
		if (a[j] == a[z])
		{
			j = split_quote(a, j, shell, a[j]);
			return (j);
		}
		j++;
	}
	return (-1);
}
//this goes off of where the last index is, so either the original one if there are quotes
//or tokenizes whats between quotes, or -1 on error
//34 is " 39 is '
//shell->tkns->quotes = (a[z] % 3) + 1; is its single quote it'll be 0 + 1 else 1 + 1

int	set_token(t_shell *shell, char *a, int i)
{
	t_token	*b;

	if ((a[i] == 34 || a[i] == 39))
		i = split_q(a, shell, i);
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
		i = split_word(a, i, shell);
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

int	tokenize_line(t_shell *shell)
{
	char	*a;
	int		i;

	a = shell->in;
	i = skip_spaces(a, 0);
	while (a[i])
	{
		shell->tkns = malloc(sizeof(t_token));
		shell->tkns->type = 0;
		i = set_token(shell, a, i);
	}
}