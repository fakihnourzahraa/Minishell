/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 09:02:13 by miwehbe           #+#    #+#             */
/*   Updated: 2025/10/18 15:27:33 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <sys/stat.h>

static void	execute_child_and_wait(t_shell *shell, t_cmd *cmd, pid_t pid)
{
	int	status;

	if (pid == 0)
		exec_external_child(shell, cmd);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	signals_prompt();
	free(cmd->path);
	cmd->path = NULL;
	wait_child(shell, status);
}

static int	execute_external_command(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;
	char	*path;

	if (handle_command_path(shell, cmd, &path))
		return (1);
	cmd->path = path;
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free(cmd->path);
		cmd->path = NULL;
		return (1);
	}
	execute_child_and_wait(shell, cmd, pid);
	return (1);
}

static void	builtin_child_process(t_shell *shell, t_cmd *cmd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (process_heredocs(cmd, shell) == -1)
	{
		cleanup_child_process(shell);
		exit(1);
	}
	if (apply_redirections(cmd, shell) == -1)
	{
		cleanup_child_process(shell);
		exit(1);
	}
	execute_builtin_dispatch(cmd, shell);
	cleanup_child_process(shell);
	exit(shell->exit_status);
}

static int	execute_builtin_with_redirect(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
		builtin_child_process(shell, cmd);
	waitpid(pid, &status, 0);
	wait_child(shell, status);
	return (1);
}

int	execute_single(t_shell *shell, t_cmd *cmd)
{
	if (!cmd || !shell)
		return (0);
	if (!cmd->cmd || cmd->cmd[0] == '\0')
		return (0);
	if (!cmd->args || !cmd->args[0])
		return (0);
	if (handle_variable_assignment(shell, cmd))
		return (1);
	if (cmd->builtin != NOT_BUILTIN)
	{
    	if (cmd->rd)
    	{
        	if (needs_parent_execution(cmd->builtin))
        	{
            	if (process_heredocs(cmd, shell) == -1)
                	return (1);
            	return (execute_with_redirect_parent(cmd, shell));
        	}
        	else
            	return (execute_builtin_with_redirect(shell, cmd));
    	}
    	execute_builtin(cmd, shell);
    	return (1);
	}
	if (cmd->rd && process_heredocs(cmd, shell) == -1)
		return (1);
	return (execute_external_command(shell, cmd));
}


/*if (cmd->builtin != NOT_BUILTIN)
{
	if (cmd->rd)
		return (execute_builtin_with_redirect(shell, cmd));
	execute_builtin(cmd, shell);
	return (1);
}*/
