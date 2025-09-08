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
	return (i + 2);
}

int	split_q(char *a, t_shell *shell, int i)
{
	int	j;

	j = i + 1;
	while (a[j])
	{
		if (a[j] == a[i])
			return (split_quote(a, i, shell, a[i]));
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
	t_token	*n;

	n = init_token();
	i = skip_spaces(a, i);
	if ((a[i] == 34 || a[i] == 39))
		return (free(n), split_q(a, shell, i));
	else if (a[i] == '|')
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
		return (split_word(a, i, shell));
	add_token(shell, n);
	// b = malloc(sizeof(t_token));
	// shell->tkns->next = b;
	// shell->tkns = shell->tkns->next;
	return (i);
}

//in quotations we can have new lines etc
//skip spaces at the end of each split

t_token	*init_token(void)
{
	t_token	*n;

	n = malloc(sizeof(t_token));
	n->type = EMPTY;
	n->s = NULL;
	n->quotes = 0;
	n->next = NULL;
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
			return (-1);
		if (a[i] == '\0' || j == i)
			break ;
	}
	t = init_token();
	t->type = T_EOF;	
	add_token(shell, t);
	return (1);
}