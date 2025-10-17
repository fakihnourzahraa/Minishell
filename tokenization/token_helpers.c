/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 22:14:32 by nfakih            #+#    #+#             */
/*   Updated: 2025/10/17 13:19:38 by nour             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

int	skipforvar(char *a, int i)
{
	while (a[i] && (ft_isalnum(a[i]) || skipable_space(a[i])))
		i++;
	return (i);
}

bool	skipable_space(char a)
{
	if (a == 32 || a == 9 || a == 11 || a == 12)
		return (true);
	return (false);
}
// void	cleanup_token(t_shell *shell)
// {
// 	if (shell->tkns)
// 		free_tokens(shell->tkns);
// }

int	skip_spaces(char *a, int i)
{
	while (i > -1 && a[i] && skipable_space(a[i]))
		i++;
	return (i);
}

// only the skipable ones
// Space (32) and Tab (9) are your main token separators
// Newline (10) typically ends a command line
// Carriage Return (13) might appear in files created on Windows systems
