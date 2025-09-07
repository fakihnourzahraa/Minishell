/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:17:03 by miwehbe           #+#    #+#             */
/*   Updated: 2025/08/29 13:17:03 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	is_n_flag(char *arg)
{
	int	i;

	if (arg[0] != '-')
		return (false);
	i = 1;
	if (arg[i] == '\0')
		return (false);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

static void	print_echo(char **args, int start, bool newline)
{
	int	i;

	i = start;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
}

void	builtin_echo(t_cmd *cmd, t_shell *shell)
{
	int		i;
	int		start;
	bool	newline;

	(void)shell; // to match prototype
	newline = true;
	start = 1;
	i = 1;
	while (cmd->args[i] && is_n_flag(cmd->args[i]))
	{
		newline = false;
		i++;
	}
	start = i;
	if (!cmd->args[start])
	{
		if (newline)
			ft_putchar_fd('\n', 1);
	}
	else
		print_echo(cmd->args, start, newline);
	shell->exit_status = 0;
}
