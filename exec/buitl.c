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
  /*if (ft_strcmp(cmd, "env") == 0)
    return (BUILTIN_ENV);*/
  return (0);
}

/*int	execute_builtin(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		builtin_echo(cmd, shell);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		builtin_pwd(cmd, shell);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		builtin_exit(cmd, shell);
	else
		return (0);
	return (1);
}*/
int execute_builtin(t_cmd *cmd, t_shell *shell)
{
  if (!cmd || !cmd->args || !cmd->args[0])
    return (0);
    // Handle builtins with redirections
	 if (ft_strcmp(cmd->args[0], "exit") == 0)
    {
        builtin_exit(cmd, shell);  // Always run exit in parent
        return (1);
    }
  if (cmd->rd)
  {
		//printf("DEBUG: About to fork for builtin redirection\n");
    pid_t pid = fork();
    if (pid < 0)
    {
      perror("fork");
      return (1);
    }
    else if (pid == 0)  // Child process
    {
			//printf("DEBUG: In child process\n");
      if (apply_redirections(cmd, shell) == -1)
        exit(1);
      if (ft_strcmp(cmd->args[0], "echo") == 0)
        builtin_echo(cmd, shell);
      else if (ft_strcmp(cmd->args[0], "pwd") == 0)
        builtin_pwd(cmd, shell);
      else if (ft_strcmp(cmd->args[0], "exit") == 0)
        builtin_exit(cmd, shell);
      else if (ft_strcmp(cmd->args[0], "cd") == 0)
        builtin_cd(cmd, shell);
      /*else if (ft_strcmp(cmd->args[0], "env") == 0)
        builtin_env(cmd, shell);*/
      //printf("DEBUG: Child about to exit\n");
      exit(shell->exit_status);
    }
    else  // Parent process
    {
			//printf("DEBUG: In parent, waiting for child\n");
      int status;
      waitpid(pid, &status, 0);
			//printf("DEBUG: Parent finished waiting\n");
      if (WIFEXITED(status))
        shell->exit_status = WEXITSTATUS(status);
      else
        shell->exit_status = 1;
    }
    return (1);
    }

    // No redirections - execute builtin directly
    if (ft_strcmp(cmd->args[0], "echo") == 0)
      builtin_echo(cmd, shell);
    else if (ft_strcmp(cmd->args[0], "pwd") == 0)
      builtin_pwd(cmd, shell);
    else if (ft_strcmp(cmd->args[0], "exit") == 0)
      builtin_exit(cmd, shell);
    else if (ft_strcmp(cmd->args[0], "cd") == 0)
      builtin_cd(cmd, shell);
    /*else if (ft_strcmp(cmd->args[0], "env") == 0)
      builtin_env(cmd, shell);*/
    else
      return (0);
    return (1);
}