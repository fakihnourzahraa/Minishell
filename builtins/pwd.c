/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:17:35 by miwehbe           #+#    #+#             */
/*   Updated: 2025/08/29 13:17:35 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	builtin_pwd(t_cmd *cmd, t_shell *shell)
{
	char	*cwd;

	(void)cmd;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		shell->exit_status = 1;
		return ;
	}
	ft_putstr_fd(cwd, 1);
	ft_putchar_fd('\n', 1);
	free(cwd);
	shell->exit_status = 0;
}
