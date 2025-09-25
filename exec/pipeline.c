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

/*int count_commands(t_cmd *cmds)
{
  int i;

  i =0;
  while(cmds)
  {
    i++;
    cmds= cmds->next;
  }
  return (i);
}
// this fct to only count cmnd 

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
  }//
  return (pipes);
}
int **setup_pipes(int cmd_count)
{
    int **pipes;
    int pipe_count;
    int i;

    if (cmd_count < 2)
        return (NULL);
        
    pipe_count = cmd_count - 1;
    pipes = malloc(sizeof(int *) * pipe_count);
    if (!pipes)
        return (NULL);
    i = 0;
    while (i < pipe_count)
    {
        pipes[i] = NULL;
        i++;
    }
    i = 0;
    while (i < pipe_count)
    {
        pipes[i] = malloc(sizeof(int) * 2);
        if (!pipes[i])
        {
            cleanup_pipes(pipes, i);
            return (NULL);
        }
        
        if (pipe(pipes[i]) == -1)
        {
            perror("pipe");
            free(pipes[i]);
            cleanup_pipes(pipes, i);
            return (NULL);
        }
        i++;
    }
    
    return (pipes);
}

void close_all_pipes(int **pipes, int pipe_count)
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

void wait_for_children(t_cmd *cmds,t_shell *shell)
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
    shell->exit_status=WEXITSTATUS(last_status);//normal exit
  else if(WIFSIGNALED(last_status))
    shell->exit_status=128+WTERMSIG(last_status);// in bash when we kill by a signal we add 128 to signal nbr
}

int execute_pipeline(t_shell *shell, t_cmd *cmds)
{
  int cmd_count;

  cmd_count = count_commands(cmds);
  if (cmd_count == 1)
  {
    execute_cmd_in_pipeline(shell, cmds, NULL);
    wait_for_children(cmds, shell);
    return (shell->exit_status);
  }  
  return (execute_multiple_cmds(shell, cmds, cmd_count));
}*/


int count_commands(t_cmd *cmds)
{
  int i;

  i =0;
  while(cmds)
  {
    i++;
    cmds= cmds->next;
  }
  return (i);
}

int **setup_pipes(int cmd_count)
{
    int **pipes;
    int pipe_count;
    int i;

    if (cmd_count < 2)
        return (NULL);
        
    pipe_count = cmd_count - 1;
    pipes = malloc(sizeof(int *) * pipe_count);
    if (!pipes)
        return (NULL);
 
    i = 0;
    while (i < pipe_count)
    {
        pipes[i] = NULL;
        i++;
    }

    // Then allocate and create pipes
    i = 0;
    while (i < pipe_count)
    {
        pipes[i] = malloc(sizeof(int) * 2);
        if (!pipes[i])
        {
            cleanup_pipes(pipes, i);  // This will clean up what was allocated so far
            return (NULL);
        }
        
        if (pipe(pipes[i]) == -1)
        {
            perror("pipe");
            free(pipes[i]);
            pipes[i] = NULL;
            cleanup_pipes(pipes, i);
            return (NULL);
        }
        i++;
    }
    return (pipes);
}

void close_all_pipes(int **pipes, int pipe_count)
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

void wait_for_children(t_cmd *cmds,t_shell *shell)
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
    shell->exit_status=WEXITSTATUS(last_status);//normal exit
  else if(WIFSIGNALED(last_status))
    shell->exit_status=128+WTERMSIG(last_status);
}

int execute_pipeline(t_shell *shell, t_cmd *cmds)
{
  int cmd_count;

  cmd_count = count_commands(cmds);
  if (cmd_count == 1)
  {
    execute_cmd_in_pipeline(shell, cmds, NULL);
    wait_for_children(cmds, shell);
    return (shell->exit_status);
  }  
  return (execute_multiple_cmds(shell, cmds, cmd_count));
}