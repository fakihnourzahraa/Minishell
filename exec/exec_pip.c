/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 22:51:45 by miwehbe           #+#    #+#             */
/*   Updated: 2025/10/24 13:41:19 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	handle_command_not_found(t_shell *s, t_cmd *cmd, t_pipe_info *info)
{
	pid_t	pid;

	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
	{
		signals_child();
		setup_cmd_fds(cmd, info, s);
		cleanup_pipeline_child(s);
		exit(127);
	}
	else
	{
		cmd->pid = pid;
		return (pid);
	}
}

static int	fork_and_execute(t_shell *shell, t_cmd *cmd, t_pipe_info *info)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		if (cmd->path)
		{
			free(cmd->path);
			cmd->path = NULL;
		}
		return (-1);
	}
	else if (pid == 0)
	{
		executes_child_process(shell, cmd, info);
		exit(1);
	}
	else
	{
		cmd->pid = pid;
		return (pid);
	}
}

int	execute_cmd_in_pipeline(t_shell *shell, t_cmd *cmd, t_pipe_info *info)
{
	if (cmd->builtin == NOT_BUILTIN && cmd->args[0]
		&& !ft_strchr(cmd->args[0], '/'))
	{
		cmd->path = get_cmd_path(cmd->args[0], shell);
		if (!cmd->path)
			return (handle_command_not_found(shell, cmd, info));
	}
	return (fork_and_execute(shell, cmd, info));
}

void	connect_pipes(int *input_fd, int *output_fd, t_pipe_info *info)
{
	if (*input_fd == STDIN_FILENO && info->cmd_index > 0)
		*input_fd = info->pipes[info->cmd_index - 1][0];
	if (*output_fd == STDOUT_FILENO && info->cmd_index < info->cmd_count - 1)
		*output_fd = info->pipes[info->cmd_index][1];
}
