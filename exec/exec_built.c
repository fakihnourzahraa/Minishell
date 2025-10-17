/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 18:39:23 by miwehbe           #+#    #+#             */
/*   Updated: 2025/10/17 18:39:23 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int is_builtin(char *cmd)
{
  if (cmd ==NULL)
    return(NOT_BUILTIN);
  if (ft_strcmp(cmd,"echo") == 0)
    return (BUILTIN_ECHO);
  if (ft_strcmp(cmd,"pwd") == 0)
    return (BUILTIN_PWD);
  if(ft_strcmp(cmd,"exit") == 0)
    return (BUILTIN_EXIT);
  if (ft_strcmp(cmd, "cd") == 0)
    return (BUILTIN_CD);
  if (ft_strcmp(cmd, "env") == 0)
    return (BUILTIN_ENV);
  if (ft_strcmp(cmd, "export") == 0)
    return (BUILTIN_EXPORT);
  if (ft_strcmp(cmd, "unset") == 0)
    return (BUILTIN_UNSET);
  return (0);
}

int	execute_builtin(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || !cmd->args || !cmd->args[0] || !shell)
		return (0);
	if (cmd->builtin == NOT_BUILTIN)
		return (0);
	if (cmd->rd)
	{
		if (needs_parent_execution(cmd->builtin))
			return (execute_with_redirect_parent(cmd, shell));
		else
			return (execute_with_redirect_child(cmd, shell));
	}
	execute_builtin_dispatch(cmd, shell);
	return (1);
}