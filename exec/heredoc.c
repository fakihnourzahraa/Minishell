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
    int fd[2];      // array for pipe
    pid_t pid;      // for fork
    char *line;     // for hold readline
    int status;     // for wait()

    if(pipe(fd) == -1)  // pipe return -1 on failure, 0 success
    {
        perror("pipe");
        return(-1);  // Don't exit, just return error
    }

    shell->in_h = 1;  // Mark that we're in heredoc
    
    pid = fork();
    if(pid < 0)
    {
        perror("fork");
        close(fd[0]);
        close(fd[1]);
        return(-1);  // Don't exit, just return error
    }
    else if(pid == 0)  // Child process
    {
        signals_child_heredoc();  // Set proper signals for heredoc child
        close(fd[0]);  // Child doesn't read from pipe
        
        while(1)
        {
            line = readline("> ");  // Heredoc prompt
            if(!line)  // Ctrl+D pressed
            {
                close(fd[1]);
                exit(0);
            }
            if(ft_strcmp(line, delimiter) == 0)  // Found delimiter
            {
                free(line);
                close(fd[1]);
                exit(0);
            }
            write(fd[1], line, ft_strlen(line));  // Write to pipe
            write(fd[1], "\n", 1);
            free(line);
        }
    }
    else  // Parent process
    {
        close(fd[1]);  // Parent doesn't write to pipe
        waitpid(pid, &status, 0);  // Wait for child
        shell->in_h = 0;  // No longer in heredoc
        //signals_prompt();  // Reset signals to normal prompt mode
        
        if (WIFSIGNALED(status))  // Child killed by signal (Ctrl+C)
        {
            close(fd[0]);
            shell->exit_status = 130;  // 130 for Ctrl+C
            return(-1);
        }
        else if(WIFEXITED(status))  // Child exited normally
        {
            shell->exit_status = WEXITSTATUS(status);
            return(fd[0]);  // Return read end of pipe
        }
    }
    
    close(fd[0]);
    return(-1);
}

//when i said write(1,..,..)== write to stdout(terminal)
//but when i said write(fd[1],...,...)== write to the write of pipe 
//signal(SIGINT, SIG_DFL);SIG_DFL :default behave :terminate process
//SIGINT = is sign nbr =2 it is for ctrl+c