/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:24:02 by nour              #+#    #+#             */
/*   Updated: 2025/09/02 14:19:31 by nour             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing.h"

int	

int	check_quotes(char *a)
{
	int	i;
	int	j;
	int	c;

	j = ft_strlen(a) - 1;
	i = 0;
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
//set bool quotes = 1 or 2