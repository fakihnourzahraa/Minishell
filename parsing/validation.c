/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 13:17:23 by nfakih            #+#    #+#             */
/*   Updated: 2025/09/01 19:40:19 by nour             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing.h"

// int	is_builtin(char	*a, int	i)
// {
// 	if (!ft_strncmp(a, "echo", 4))
// 		return (i + 4);
// 	else if (!ft_strncmp(a, "cd", 2))
// 		return (i + 2);
// 	else if (!ft_strncmp(a, "pwd", 3))
// 		return (i + 3);
// 	else if (!ft_strncmp(a, "export", 6))
// 		return (i + 6);
// 	else if (!ft_strncmp(a, "unset", 5))
// 		return (i + 5);
// 	else if (!ft_strncmp(a, "env", 3))
// 		return (i + 3);
// 	else if (!ft_strncmp(a, "exit", 4))
// 		return (i + 4);
// 	return (0);
// }

// int	is_cmd(char	*a, int i)
// {
// 	int	i;

// 	i = is_builtin(a, i);
// 	if (i)
// 		return (i);
	
// 	return (i);
// }
//no i = 0 cause is builtin takes care of that

int	is_op(char	*a, int i)
{
	char	*s;

	s[0] = a[i];
	s[0] = a[i++];
	if (a[i] == '<' || a[i] == '>' 
		|| ft_strnstr(a, s, "<<") || ft_strnstr(a, s, ">>"));
	return (i);
}
int	skip_spaces(char *a, int i)
{
	while (i > -1 && a[i] && skipable_space(a[i]))
		i++;
	return (i);
}
