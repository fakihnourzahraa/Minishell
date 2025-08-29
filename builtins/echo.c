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

	(void)shell; // not used inside print, just to match prototype

	i = 0;
	start = 1;
	newline = true;
	while (cmd->args[i])
		i++;
	if (i > 1 && ft_strcmp(cmd->args[1], "-n") == 0)
	{
		start = 2;
		newline = false;
	}
	if (i == 1)
		ft_putchar_fd('\n', 1);
	else
		print_echo(cmd->args, start, newline);
	shell->exit_status = 0; // set success exit status
}
