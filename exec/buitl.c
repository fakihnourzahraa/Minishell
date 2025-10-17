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

int	needs_parent_execution(int builtin)
{
	return (builtin == BUILTIN_CD
		|| builtin == BUILTIN_EXPORT
		|| builtin == BUILTIN_UNSET
		|| builtin == BUILTIN_EXIT);
}

void	execute_builtin_dispatch(t_cmd *cmd, t_shell *shell)
{
	if (cmd->builtin == BUILTIN_ECHO)
		builtin_echo(cmd, shell);
	else if (cmd->builtin == BUILTIN_PWD)
		builtin_pwd(cmd, shell);
	else if (cmd->builtin == BUILTIN_ENV)
		builtin_env(cmd, shell);
	else if (cmd->builtin == BUILTIN_EXIT)
		builtin_exit(cmd, shell);
	else if (cmd->builtin == BUILTIN_CD)
		builtin_cd(cmd, shell);
	else if (cmd->builtin == BUILTIN_EXPORT)
		builtin_export(cmd, shell);
	else if (cmd->builtin == BUILTIN_UNSET)
		builtin_unset(cmd, shell);
}

int	save_and_redirect(t_cmd *cmd, t_shell *shell
				, int *stdin_fd, int *stdout_fd)
{
	*stdin_fd = dup(STDIN_FILENO);
	*stdout_fd = dup(STDOUT_FILENO);
	if (*stdin_fd == -1 || *stdout_fd == -1)
	{
		if (*stdin_fd != -1)
			close(*stdin_fd);
		if (*stdout_fd != -1)
			close(*stdout_fd);
		return (-1);
	}
	if (apply_redirections(cmd, shell) == -1)
	{
		dup2(*stdin_fd, STDIN_FILENO);
		dup2(*stdout_fd, STDOUT_FILENO);
		close(*stdin_fd);
		close(*stdout_fd);
		return (-1);
	}
	return (0);
}

int	execute_with_redirect_parent(t_cmd *cmd, t_shell *shell)
{
	int	saved_stdin;
	int	saved_stdout;

	if (save_and_redirect(cmd, shell, &saved_stdin, &saved_stdout) == -1)
		return (1);
	execute_builtin_dispatch(cmd, shell);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (1);
}

int	execute_with_redirect_child(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (apply_redirections(cmd, shell) == -1)
			exit(1);
		execute_builtin_dispatch(cmd, shell);
		exit(shell->exit_status);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
	return (1);
}
