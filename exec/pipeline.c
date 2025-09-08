/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 12:58:24 by miwehbe           #+#    #+#             */
/*   Updated: 2025/09/07 12:58:24 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int count_commands(t_cmd *cmds);//1
{
  int i;

  i =0;
  while(cmds)
  {
    i++;
    cmds= cmds->next;
  }
  return (i);
}// this fct to only count cmnd 

int **setup_pipes(int cmd_count)
{
  int **pipes;
  int pipe_count;
  int i;

  if (cmd_count < 2)
    return (NULL);//bcz no need to pipe
  pipe_count = cmd_count - 1;//last one dont need |
  pipes = malloc(sizeof(int *) * pipe_count);
  if (!pipes)
    return (NULL);
  i = 0;
  while (i < pipe_count)
  {
    if (create_single_pipe(pipes, i) == -1)
    {
      cleanup_pipes(pipes, i);
      return (NULL);
    }
    i++;
  }
  return (pipes);
}//this fct is only to allocate and initial the pipe

void close_all_pipes(int **pipes, int pipe_count);//4
{
  int i;

  i = 0;
  if(!pipes)
    return ;
  while(i < pipe_count)
  {
    if(pipes[i] != NULL)
    {
      close(pipes[i][0]);//close read
      close(pipes[i][1]);//close write
    }
    i++;
  }
}

void wait_for_children(t_cmd *cmds,t_Shell *shell);//7
{
  int last_status;
  t_cmd *current ;

  last_status =0;
  current = cmds;
  while(current)
  {
    if(current->pid > 0)
      waitpid(current->pid,&last_status,0);
    current = current->next;
  }
  if(WIFEXITED(last_status))
    shell->exit_status=WEXITSTATUS(status);//normal exit
  else if(WIFSIGNALED(last_status))
    shell->exit_status=128+WTERMSIG(status);// in bash when we kill by a signal we add 128 to signal nbr
}

/*int execute_pipeline(t_shell *shell, t_cmd *cmds);//9
{

}*/