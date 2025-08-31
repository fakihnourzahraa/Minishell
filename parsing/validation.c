/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 13:17:23 by nfakih            #+#    #+#             */
/*   Updated: 2025/08/31 13:53:16 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing.h"
int	is_cmd(char	*a, int i)
{
	if (ft_strncmp(a, ""))
	return (i);
}
int	is_op(char	*a, int i)
{
	return (i);
}
int	is_var(char	*a, int i)
{
	if (a[i] == '$')
	{

	}
	return (i);
}
int	skip_spaces(char *a, int i)
{
	while (i > -1 && a[i] && skipable_space(a[i]))
		i++;
	return (i);
}