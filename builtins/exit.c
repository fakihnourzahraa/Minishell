/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 17:33:30 by miwehbe           #+#    #+#             */
/*   Updated: 2025/08/29 17:33:30 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	builtin_exit(t_cmd *cmd, t_shell *shell)
{
	int	status;

	ft_putendl_fd("exit", 1);
	if (!cmd->args[1])
		status = 0;
	else
		status = ft_atoi(cmd->args[1]);
	shell->exit_status = status;
	// free_shell(shell); // if you have a cleanup function
	exit(shell->exit_status);
}
