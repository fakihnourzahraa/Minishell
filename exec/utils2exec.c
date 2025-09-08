/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 12:58:43 by miwehbe           #+#    #+#             */
/*   Updated: 2025/09/07 12:58:43 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void cleanup_pipes(int **pipes, int count)
{
  int j;

  j = 0;
  while (j < count)
  {
    free(pipes[j]);//free the old pipe
    j++;
  }
  free(pipes);//then the array itself
}

int create_single_pipe(int **pipes, int index)
{
  pipes[index] = malloc(sizeof(int) * 2);
  if (!pipes[index])
    return (-1);
  if (pipe(pipes[index]) == -1)//== pipe(pipefd) ie pipes[i][0]=pipefd[0]
  {
    perror("pipe");
    free(pipes[index]);
    return (-1);
  }
  return (0);
}

static int	execute_all_commands(t_shell *shell, t_cmd *cmds, t_pipe_info *info)
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

static void	cleanup_and_wait(t_shell *shell, t_cmd *cmds, t_pipe_info *info)
{
	close_all_pipes(info->pipes, info->cmd_count - 1);
	wait_for_children(cmds, shell);
	free_pipes(info->pipes, info->cmd_count - 1);
	signals_prompt();
}

int	execute_multiple_cmds(t_shell *shell, t_cmd *cmds, int cmd_count)
{
	t_pipe_info	info;

	info.pipes = setup_pipes(cmd_count);
	if (!info.pipes)
		return (1);
	info.cmd_count = cmd_count;
	signals_parent();
	if (execute_all_commands(shell, cmds, &info) == -1)
	{
		close_all_pipes(info.pipes, cmd_count - 1);
		free_pipes(info.pipes, cmd_count - 1);
		signals_prompt();
		return (1);
	}
	cleanup_and_wait(shell, cmds, &info);
	return (shell->exit_status);
}
