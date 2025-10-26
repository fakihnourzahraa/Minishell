/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segments.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:46:51 by nour              #+#    #+#             */
/*   Updated: 2025/10/26 14:50:04 by nour             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static void	copy_before_split(char **new_args, char **old_args, int i)
{
	int	c;

	c = 0;
	while (c < i)
	{
		new_args[c] = ft_strdup(old_args[c]);
		free(old_args[c]);
		c++;
	}
}

static int	copy_split_args(char **new_args, char **split, int start)
{
	int	spl;
	int	c;

	spl = 0;
	c = start;
	while (split && split[spl])
	{
		new_args[c] = ft_strdup(split[spl]);
		free(split[spl]);
		spl++;
		c++;
	}
	return (c);
}

static int	copy_after_split(char **new_args, char **old_args, int i, int c)
{
	int	org;

	org = i + 1;
	while (old_args[org])
	{
		new_args[c] = ft_strdup(old_args[org]);
		free(old_args[org]);
		c++;
		org++;
	}
	return (c);
}

int	copy_args_segments(char **new_args, char **old_args,
								char **split, int i)
{
	int	c;

	copy_before_split(new_args, old_args, i);
	c = copy_split_args(new_args, split, i);
	c = copy_after_split(new_args, old_args, i, c);
	new_args[c] = NULL;
	return (c);
}

int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args && args[count])
		count++;
	return (count);
}
