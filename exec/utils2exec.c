/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 12:58:43 by miwehbe           #+#    #+#             */
/*   Updated: 2025/10/26 23:45:02 by nour             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	cleanup_pipes(int **pipes, int count)
{
	int	j;

	if (!pipes)
		return ;
	j = 0;
	while (j < count)
	{
		if (pipes[j])
		{
			free(pipes[j]);
			pipes[j] = NULL;
		}
		j++;
	}
	free(pipes);
}

void	close_and_free_pipes(int **pipes, int pipe_count)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < pipe_count)
	{
		if (pipes[i] != NULL)
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
			free(pipes[i]);
			pipes[i] = NULL;
		}
		i++;
	}
	free(pipes);
}

int	create_single_pipe(int **pipes, int index)
{
	pipes[index] = malloc(sizeof(int) * 2);
	if (!pipes[index])
		return (-1);
	if (pipe(pipes[index]) == -1)
	{
		perror("pipe");
		free(pipes[index]);
		pipes[index] = NULL;
		return (-1);
	}
	return (0);
}

int	execute_all_commands(t_shell *shell, t_cmd *cmds, t_pipe_info *info)
{
	t_cmd	*current;
	int		index;

	current = cmds;
	index = 0;
	while (current)
	{
		info->cmd_index = index;
		if (execute_cmd_in_pipeline(shell, current, info) == -1)
			return (-1);
		current = current->next;
		index++;
	}
	return (0);
}

void	cleanup_and_wait(t_shell *shell, t_cmd *cmds, t_pipe_info *info)
{
	close_and_free_pipes(info->pipes, info->cmd_count - 1);
	info->pipes = NULL;
	wait_for_children(cmds, shell);
	signals_prompt();
}
