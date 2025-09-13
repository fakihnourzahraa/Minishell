/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:45:13 by nfakih            #+#    #+#             */
/*   Updated: 2025/09/13 13:51:53 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

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