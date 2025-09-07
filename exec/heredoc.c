/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:33:35 by miwehbe           #+#    #+#             */
/*   Updated: 2025/09/03 14:33:35 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int run_heredoc(char *delimiter, t_shell *shell)
{
  int fd[2];//array for pipe
  pid_t pid;//for fork
  char *line;//for hold readline
  int status;//for wait()
  int code;

  if(pipe(fd) == -1)//pipe return -1 on failure ,0 succes
  {
    perror("pipe");
    exit(1);//every nbr #0 it mean fail in exit
  }
  shell->in_h = 1;
  //we do pipe bcz we want a way to store user input temporarily and give it to the command.
  pid = fork();
  if(pid < 0)
  {
    perror("fork");
    exit(1);
  }
  else if(pid== 0)
  {
    signal(SIGINT, SIG_DFL);//to handle ctrl+c
    close(fd[0]);// close it bcz child doesnt want to read from pipe
    while(1)
    {
      line = readline("> ");//prompt >
      if(!line)
        break;
      if(ft_strcmp(line,delimiter) == 0)//we check delimiter
      {
        free(line);
        break;
      }
      write(fd[1],line,ft_strlen(line));//write the line into the pipe write
      write(fd[1],"\n",1);
      free(line);
    }
    close(fd[1]);
    exit(0);
  }
  else//parent
  {
    close(fd[1]);//close it bcz parent doenst write only read
    waitpid(pid,&status,0);//pid is the child pidd we want wait,0 is defalt behv
    shell->in_h = 0;
    signals_prompt();
    if(WIFEXITED(status))//child exit (for existence)
    {
      code = WEXITSTATUS(status);//0
      shell->exit_status=code;
      return fd[0];
    }
    else if (WIFSIGNALED(status))//child killed by the signal(for killing)
    {
      close(fd[0]);//bcz no input 
      shell->exit_status =130; //130 for ctrl+c
      return -1;
    }
  }
  return -1;
}




//when i said write(1,..,..)== write to stdout(terminal)
//but when i said write(fd[1],...,...)== write to the write of pipe 
//signal(SIGINT, SIG_DFL);SIG_DFL :default behave :terminate process
//SIGINT = is sign nbr =2 it is for ctrl+c