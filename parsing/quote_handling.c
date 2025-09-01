/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 13:17:20 by nfakih            #+#    #+#             */
/*   Updated: 2025/08/31 13:25:18 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing.h"

int	check_quotes(char *a)
{
	int	i;
	int	j;
	int	c;

	j = ft_strlen(a) - 1;
	while (a[i])
	{
		if (a[i] == 34 || a[i] == 39)
		{
			c = 0;
			while (j > i)
			{
				if (a[j] == a[i])
				{
					c = 1;
					break ;
				}
				j--;
			}
			if (!c)
				return (0);
		}
		i++;
	}
	return (1);
}
//34 is " 39 is '