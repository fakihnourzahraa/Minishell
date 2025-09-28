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

  if (!pipes)
    return;
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

void close_and_free_pipes(int **pipes, int pipe_count)
{
  int i;

	if (!pipes)
    return;    
  i = 0;
  while (i < pipe_count)
  {
    if (pipes[i] != NULL)
    {
      close(pipes[i][0]); // close read
      close(pipes[i][1]); // close write
      free(pipes[i]);     // free the pipe array
      pipes[i] = NULL;
    }
    i++;
  }
  free(pipes); // Free the array of pointers
}

int create_single_pipe(int **pipes, int index)
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
	close_and_free_pipes(info->pipes, info->cmd_count - 1);
	info->pipes = NULL;
	wait_for_children(cmds, shell);
	signals_prompt();
}

/*int	execute_multiple_cmds(t_shell *shell, t_cmd *cmds, int cmd_count)
{
	t_pipe_info	info;

	printf("DEBUG: execute_multiple_cmds called with cmd_count=%d\n", cmd_count);
	info.pipes = setup_pipes(cmd_count);
	if (!info.pipes)
		return (1);
	info.cmd_count = cmd_count;
	signals_parent();
	printf("DEBUG: About to call execute_all_commands\n");
	if (execute_all_commands(shell, cmds, &info) == -1)
	{
		close_and_free_pipes(info.pipes, cmd_count - 1);
		info.pipes = NULL;
		//close_all_pipes(info.pipes, cmd_count - 1);
		//free_pipes(info.pipes, cmd_count - 1);
		//cleanup_pipes(info.pipes, cmd_count - 1);
		signals_prompt();
		return (1);
	}
	cleanup_and_wait(shell, cmds, &info);
	return (shell->exit_status);
}*/

int execute_multiple_cmds(t_shell *shell, t_cmd *cmds, int cmd_count)
{
  t_pipe_info info;
  t_cmd *current;
	int heredoc_fd;

  current = cmds;
  while (current)
	{
    if (current->rd && current->rd->type == R_HEREDOC)
    {
      heredoc_fd = run_heredoc(current->rd->s, shell);
      if (heredoc_fd == -1)
        return (1);
      current->i_fd = heredoc_fd;
    }
    current = current->next;
  }
    info.pipes = setup_pipes(cmd_count);
    if (!info.pipes)
        return (1);
    info.cmd_count = cmd_count;
    signals_parent();
    if (execute_all_commands(shell, cmds, &info) == -1)
    {
        close_and_free_pipes(info.pipes, cmd_count - 1);
        info.pipes = NULL;
        signals_prompt();
        return (1);
    }
    cleanup_and_wait(shell, cmds, &info);
    return (shell->exit_status);
}