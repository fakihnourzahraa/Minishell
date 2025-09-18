/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buitl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:32:24 by miwehbe           #+#    #+#             */
/*   Updated: 2025/08/29 14:32:24 by miwehbe          ###   ########.fr       */
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

int execute_builtin(t_cmd *cmd, t_shell *shell)
{
  int status;

  if (!cmd || !cmd->args || !cmd->args[0])
    return (0);
  if (cmd->builtin == BUILTIN_EXIT)
  {
    builtin_exit(cmd, shell);
    return (1);
  }
  if (cmd->builtin == BUILTIN_CD)
  {
    builtin_cd(cmd, shell);
    return (1);
  }
  if (cmd->builtin == BUILTIN_EXPORT)
  {
    builtin_export(cmd, shell);
    return (1);
  }
  if (cmd->builtin == BUILTIN_UNSET)
  {
    builtin_unset(cmd, shell);
    return (1);
  }
  if (cmd->rd)
  {
    pid_t pid = fork();
    if (pid < 0)
    {
      perror("fork");
      return (1);
    }
    else if (pid == 0)
    {
      if (apply_redirections(cmd, shell) == -1)
        exit(1);
      if (cmd->builtin == BUILTIN_ECHO)
        builtin_echo(cmd, shell);
      else if (cmd->builtin == BUILTIN_PWD)
        builtin_pwd(cmd, shell);
      else if (cmd->builtin == BUILTIN_ENV)
        builtin_env(cmd, shell);
      exit(shell->exit_status);
    }
    else // Parent
    {
      waitpid(pid, &status, 0);
      if (WIFEXITED(status))
        shell->exit_status = WEXITSTATUS(status);
      else
        shell->exit_status = 1;
    }
    return (1);
  }
  if (cmd->builtin == BUILTIN_ECHO)
    builtin_echo(cmd, shell);
  else if (cmd->builtin == BUILTIN_PWD)
    builtin_pwd(cmd, shell);
  else if (cmd->builtin == BUILTIN_ENV)
    builtin_env(cmd, shell);
  return (1);
}
