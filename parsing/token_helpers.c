/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 13:23:45 by nfakih            #+#    #+#             */
/*   Updated: 2025/08/31 15:30:57 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing.h"

bool	skipable_space(char a)
{
	if (a == 32 || a == 9 || a == 11 || a == 12)
		return (true);
	return (false);
}
void	cleanup_token(t_shell *shell)
{
	if (shell->tkns)
		free_tokens(shell->tkns);
}
// only the skipable ones
// Space (32) and Tab (9) are your main token separators
// Newline (10) typically ends a command line
// Carriage Return (13) might appear in files created on Windows systems
