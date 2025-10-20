/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:34:12 by miwehbe           #+#    #+#             */
/*   Updated: 2025/10/18 15:35:38 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	setup_input_fd(int input_fd)
{
	if (input_fd != STDIN_FILENO)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 input");
			if (input_fd > 2)
				close(input_fd);
			exit(1);
		}
		if (input_fd > 2)
			close(input_fd);
	}
}

static void	setup_output_fd(int output_fd)
{
	if (output_fd != STDOUT_FILENO)
	{
		if (dup2(output_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 output");
			if (output_fd > 2)
				close(output_fd);
			exit(1);
		}
		if (output_fd > 2)
			close(output_fd);
	}
}

void	setup_cmd_fds(t_cmd *cmd, t_pipe_info *info, t_shell *shell)
{
	int	input_fd;
	int	output_fd;

	input_fd = handle_input_redirections(cmd, shell);
	output_fd = handle_output_redirections(cmd);
	if (info)
		connect_pipes(&input_fd, &output_fd, info);
	setup_input_fd(input_fd);
	setup_output_fd(output_fd);
	if (info)
		close_unused_pipes(info->pipes, info->cmd_count - 1, info->cmd_index);
}

void	exec_external_with_env(t_shell *shell, t_cmd *cmd, char *path)
{
	char	**envp_array;

	envp_array = env_to_envp(shell->env);
	if (!envp_array)
	{
		free(path);
		cleanup_pipeline_child(shell);
		exit(1);
	}
	execve(path, cmd->args, envp_array);
	perror("execve");
	free_envp(envp_array);
	free(path);
	cleanup_pipeline_child(shell);
	exit(127);
}
