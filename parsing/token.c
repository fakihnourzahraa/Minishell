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

#include "../minishell.h"

int	tokenize_line(t_shell *shell)
{
	char	*a;
	int		i;

	i = 0;
	a = shell->in[i];
	shell->tkns = malloc(sizeof(t_token) + 1);
	


	if (a)
		free(a);
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
void	set_double(int n, char a, t_token *t, int i)
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
int	set_tokens(t_shell *shell, char *a)
{
		if (a[i] == 34 || a[i] == 39)
			i = split_q(a, i, shell->tkns);
		else if (a[i] == '|')
			set_single(1, '|', shell->tkns);
		else if (a[i] == '>' && a[i + 1] == '>' && i++)
			i = set_double(4, '>', shell->tkns);
		else if (a[i] == '<' && a[i + 1] == '<' && i++)
			i = set_double(5, '<', shell->tkns);
		else if (a[i] == '<')
			set_single(2, '<', shell->tkns);
		else if (a[i] == '>')
			set_single(3, '>', shell->tkns);
		else
			i = split_word(a, i, shell->tkns);
		shell->tkns = shell->tkns->next;

	if (i != -2)
		shell->tkns->type = 6;
}
//in quotations we can have new lines etc
//skip spaces at the end of each split
//we can also check for the validity of i in is_functions


//escape sequences