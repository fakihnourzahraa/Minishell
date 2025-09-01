/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 09:02:13 by miwehbe           #+#    #+#             */
/*   Updated: 2025/09/01 09:02:13 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int execute_single(t_shell *shell, t_cmd *cmd)
{
  pid_t pid;
  int status;
  char *path;

  if (!cmd || !cmd->args || !cmd->args[0] || !shell)
    return (0);
  if (cmd->builtin != NOT_BUILTIN)
  {
    execute_builtin(cmd, shell);
    return 1;// if it is # not builting(builting) call 
  }
    // Get the full path for external commands
  path = get_cmd_path(cmd->args[0], shell);
  if (!path)
  {
    printf("minishell: %s: command not found\n", cmd->args[0]);
    shell->exit_status = 127;
    return 1;
  }

  pid = fork();
  if (pid < 0)
  {
    perror("fork");
    free(path);
    return 1;
  }
  else if (pid == 0)
  {
    execve(path, cmd->args, shell->envp);
    perror("execve");
    free(path); // in case execve fails
    exit(1);
  }
  else
  {
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
      shell->exit_status = WEXITSTATUS(status);
    else
      shell->exit_status = 1;
    free(path);
  }
  return 1;
}

