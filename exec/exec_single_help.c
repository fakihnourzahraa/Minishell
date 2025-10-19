/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_help.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 09:36:27 by miwehbe           #+#    #+#             */
/*   Updated: 2025/10/18 09:36:27 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <sys/stat.h>

void	wait_child(t_shell *shell, int status)
{
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
	else
		shell->exit_status = 1;
}

char	**prepare_child_execution(t_shell *shell, t_cmd *cmd)
{
	char	**envp_array;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (apply_redirections(cmd, shell) == -1)
	{
		cleanup_child_process(shell);
		exit(1);
	}
	envp_array = env_to_envp(shell->env);
	if (!envp_array)
	{
		cleanup_child_process(shell);
		exit(1);
	}
	return (envp_array);
}

void	exec_external_child(t_shell *shell, t_cmd *cmd)
{
	char	**envp_array;

	envp_array = prepare_child_execution(shell, cmd);
	execve(cmd->path, cmd->args, envp_array);
	if (errno == EACCES)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putendl_fd(": Permission denied", 2);
		cleanup_child_process(shell);
		free_envp(envp_array);
		exit(126);
	}
	cleanup_child_process(shell);
	free_envp(envp_array);
	exit(127);
}

int	check_command_access(const char *cmd)
{
	struct stat	st;

	if (stat(cmd, &st) == -1)
	{
		if (errno == ENOENT)
			return (127);
		return (126);
	}
	if (S_ISDIR(st.st_mode))
	{
		errno = EISDIR;
		return (126);
	}
	if (access(cmd, X_OK) == -1)
	{
		if (errno == EACCES)
			return (126);
		return (127);
	}
	return (0);
}
