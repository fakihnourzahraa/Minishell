/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 14:22:48 by miwehbe           #+#    #+#             */
/*   Updated: 2025/10/23 19:35:03 by nour             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

extern int	g_signal;

static int	handle_fork_error(int *fd, t_shell *shell)
{
	close(fd[0]);
	close(fd[1]);
	shell->in_h = 0;
	return (-1);
}

static int	handle_signal_status(int status, int *fd, t_shell *shell)
{
	if (WTERMSIG(status) == SIGINT)
		shell->exit_status = 130;
	else
		shell->exit_status = 128 + WTERMSIG(status);
	close(fd[0]);
	return (-1);
}

static int	handle_exit_status(int status, int *fd, t_shell *shell)
{
	shell->exit_status = WEXITSTATUS(status);
	if (g_signal == -1)
	{
		close(fd[0]);
		return (-1);
	}
	if (shell->exit_status == 0)
		return (fd[0]);
	close(fd[0]);
	return (-1);
}

static int	wait_and_check(pid_t pid, int *fd, t_shell *shell)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	shell->in_h = 0;
	signals_prompt();
	if (WIFSIGNALED(status))
		return (handle_signal_status(status, fd, shell));
	else if (WIFEXITED(status))
		return (handle_exit_status(status, fd, shell));
	close(fd[0]);
	return (-1);
}

int	run_heredoc_internal(char **delims, int count, t_shell *shell)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (-1);
	shell->in_h = 1;
	pid = fork();
	if (pid < 0)
		return (handle_fork_error(fd, shell));
	else if (pid == 0)
	{
		close(fd[0]);
		heredoc_child(fd[1], delims, count, shell);
		exit(1);
	}
	close(fd[1]);
	return (wait_and_check(pid, fd, shell));
}
