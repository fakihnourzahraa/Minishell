/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 22:14:32 by nfakih            #+#    #+#             */
/*   Updated: 2025/10/27 10:00:54 by nfakih           ###   ########.fr       */
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
	if (a == 32 || a == 9 || a == 11 || a == 12 || a == 10)
		return (true);
	return (false);
}

int	skip_spaces(char *a, int i)
{
	while (i > -1 && a[i] && skipable_space(a[i]))
		i++;
	return (i);
}

// only the skipable ones
// Space (32) and Tab (9) are the main token separators
// Newline (10) ends a command line
// Carriage Return (13) might appear in files created on Windows systems
