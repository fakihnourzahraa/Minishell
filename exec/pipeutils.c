/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:36:28 by miwehbe           #+#    #+#             */
/*   Updated: 2025/10/18 15:36:25 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	close_unused_pipes(int **pipes, int pipe_count, int current_cmd)
{
	int	i;

	i = 0;
	if (!pipes)
		return ;
	while (i < pipe_count)
	{
		if (i != current_cmd - 1)
			close(pipes[i][0]);
		if (i != current_cmd)
			close(pipes[i][1]);
		i++;
	}
}

static void	handle_child_command(t_shell *shell, t_cmd *cmd)
{
	if (cmd->builtin != NOT_BUILTIN)
	{
		execute_builtin_dispatch(cmd, shell);
		cleanup_pipeline_child(shell);
		exit(shell->exit_status);
	}
	else
	{
		if (!cmd->path)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->args[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			cleanup_pipeline_child(shell);
			exit(127);
		}
		exec_external_with_env(shell, cmd, cmd->path);
		exit(127);
	}
}

static void	check_path_errors(t_shell *shell, t_cmd *cmd)
{
	struct stat	st;

	if (cmd->builtin == NOT_BUILTIN && !cmd->path)
	{
		if (ft_strchr(cmd->args[0], '/'))
		{
			if (stat(cmd->args[0], &st) == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(cmd->args[0], 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				cleanup_pipeline_child(shell);
				exit(127);
			}
			if (S_ISDIR(st.st_mode))
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(cmd->args[0], 2);
				ft_putstr_fd(": Is a directory\n", 2);
				cleanup_pipeline_child(shell);
				exit(126);
			}
		}
	}
}

void	executes_child_process(t_shell *shell, t_cmd *cmd, t_pipe_info *info)
{
	signals_child();
	check_path_errors(shell, cmd);
	setup_cmd_fds(cmd, info, shell);
	if (is_redirect_only_command(cmd))
	{
		cleanup_pipeline_child(shell);
		exit(0);
	}
	handle_child_command(shell, cmd);
}
