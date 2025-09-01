/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 11:16:46 by nfakih            #+#    #+#             */
/*   Updated: 2025/08/31 19:10:18 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	tokenize(t_shell *shell)
{
	char	*a;
	int		i;

	i = 0;
	a = shell->in[i];
	while (a)
	{
		if (!running(shell, a))
			cleanup(shell);
		i++;
	}
	if (a)
		free(a);
}
int	running(t_shell *shell, char *a)
{
	int		i;
	t_token	*t;

	t = malloc(sizeof(t_token) + 1);
	i = 0;
	while (i > -1 && a[i])
	{
		if (a[i] == 34 || a[i] == 39)
			i = split_q(a, i, t);
		if (i > -1 && is_op(a, i))
			i = split_op(a, i, t);
		if (i > -1 && is_var(a, i))
			i = split_var(a, i, t);
		else
			i = split_word(a, i, t);
		i++;
	}
	shell->tkns = t;
}
 
//in quotations we can have new lines etc
//skip spaces at the end of each split
//we can also check for the validity of i in is_functions
