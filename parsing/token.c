/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 11:16:46 by nfakih            #+#    #+#             */
/*   Updated: 2025/08/31 13:43:03 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cleanup(t_shell *shell)
{
	if (shell->tkns)
		free_tokens(shell->tkns);
}

int	tokenize(t_shell *shell)
{
	char	*a;

	a = read_line(0);
	while (a)
	{
		if (!running(shell, a))
			cleanup(shell);
		a = get_next_line(0);
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
		if (i > -1 && is_cmd(a, i))
			i = split_cmd(a, i, t);
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