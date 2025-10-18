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

static void	execute_child_process(t_shell *shell, t_cmd *cmd, t_pipe_info *info)
{
	signals_child();
	setup_cmd_fds(cmd, info, shell);
	if (is_redirect_only_command(cmd))
	{
		cleanup_pipeline_child(shell);
		exit(0);
	}
	if (cmd->builtin != NOT_BUILTIN)
	{
		execute_builtin(cmd, shell);
		cleanup_pipeline_child(shell);
		exit(shell->exit_status);
	}
	else
	{
		cmd->path = get_cmd_path(cmd->args[0], shell);
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

int	execute_cmd_in_pipeline(t_shell *shell, t_cmd *cmd, t_pipe_info *info)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
	{
		execute_child_process(shell, cmd, info);
		exit(1);
	}
	else
	{
		cmd->pid = pid;
		return (pid);
	}
}

void	connect_pipes(int *input_fd, int *output_fd, t_pipe_info *info)
{
	if (*input_fd == STDIN_FILENO && info->cmd_index > 0)
		*input_fd = info->pipes[info->cmd_index - 1][0];
	if (*output_fd == STDOUT_FILENO && info->cmd_index < info->cmd_count - 1)
		*output_fd = info->pipes[info->cmd_index][1];
}
