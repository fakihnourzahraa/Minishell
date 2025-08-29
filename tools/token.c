/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 11:16:46 by nfakih            #+#    #+#             */
/*   Updated: 2025/08/29 13:24:55 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cleanup(t_shell *shell)
{
	if (shell->tkns)
		free_tokens(shell->tkns);
}
int	space(char a)
{
	if (a == 32 || a == 9 || a == 11 || a == 12)
		return (1);
	return (0);
}
// only the skipable ones
// Space (32) and Tab (9) are your main token separators
// Newline (10) typically ends a command line
// Carriage Return (13) might appear in files created on Windows systems

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
int	s_quotes(t_shell *shell, int i)
{
	
}
int	d_quotes(t_shell *shell, int i)
{
	
}
int	start_quotes(t_shell *shell, int i)
{

}

int	running(t_shell *shell, char *a)
{
	int	i;
	t_token	*t;	

	t = malloc(sizeof(t_token) + 1);
	i = 0;
	while (white(a[i]))
		i++;
	
}
//in quotations we can have new lines etc


