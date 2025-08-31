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

	(void)cmd; // avoid unused parameter warning
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		shell->exit_status = 1;//failure
		return ;
	}
	ft_putstr_fd(cwd, 1);//write the current direct
	ft_putchar_fd('\n', 1);
	free(cwd);
	shell->exit_status = 0;
}

//we use t_shell to know the state of shell
//getcwd returns the current working directory as an absolute path string.
