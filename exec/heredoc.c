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

static void heredoc_child_multiple_delimiters(int write_fd, char **delimiters, int delimiter_count)
{
    char *line;
    int current_delimiter_index = 0;
    
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_IGN);
    
    while (1)
    {
        line = readline("> ");
        
        if (!line)
        {
            ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", 2);
            ft_putstr_fd(delimiters[delimiter_count - 1], 2);
            ft_putstr_fd("')\n", 2);
            close(write_fd);
            exit(42);
        }
        if (ft_strcmp(line, delimiters[current_delimiter_index]) == 0)
        {
            current_delimiter_index++;
            free(line);
            if (current_delimiter_index >= delimiter_count)
            {
                close(write_fd);
                exit(0);
            }
            continue;
        }
        if (current_delimiter_index == delimiter_count - 1)
        {
            write(write_fd, line, ft_strlen(line));
            write(write_fd, "\n", 1);
        }
        
        free(line);
    }
}

int run_multiple_heredocs(char **delimiters, int delimiter_count, t_shell *shell)
{
    int fd[2];
    pid_t pid;
    int status;
    
    if (pipe(fd) == -1)
    {
        perror("pipe");
        return (-1);
    }

    shell->in_h = 1;
    
    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        close(fd[0]);
        close(fd[1]);
        shell->in_h = 0;
        return (-1);
    }
    else if (pid == 0)  // Child process
    {
        close(fd[0]);
        heredoc_child_multiple_delimiters(fd[1], delimiters, delimiter_count);
        exit(1);
    }
    else  // Parent process
    {
        close(fd[1]);
        
        signal(SIGINT, SIG_IGN);
        waitpid(pid, &status, 0);
        
        shell->in_h = 0;
        signals_prompt();
        
        if (WIFSIGNALED(status))
        {
            if (WTERMSIG(status) == SIGINT)
            {
                printf("\n");
                shell->exit_status = 130;
            }
            else
            {
                shell->exit_status = 128 + WTERMSIG(status);
            }
            close(fd[0]);
            return (-1);
        }
        else if (WIFEXITED(status))
        {
            shell->exit_status = WEXITSTATUS(status);
            if (shell->exit_status == 0)
                return (fd[0]);
            else if (shell->exit_status == 42)  // EOF case
            {
                close(fd[0]);
                return (-1);
            }
        }
        
        close(fd[0]);
        return (-1);
    }
}

static void heredoc_child_process(int write_fd, char *delimiter)
{
    char *line;
    
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_IGN);
    
    while (1)
    {
        line = readline("> ");
        
        if (!line)
        {
            ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", 2);
            ft_putstr_fd(delimiter, 2);
            ft_putstr_fd("')\n", 2);
            close(write_fd);
            exit(42);
        }
        
        if (ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            close(write_fd);
            exit(0);
        }
        write(write_fd, line, ft_strlen(line));
        write(write_fd, "\n", 1);
        free(line);
    }
}

int run_heredoc(char *delimiter, t_shell *shell)
{
    int fd[2];
    pid_t pid;
    int status;

    if (!delimiter || !shell)
        return (-1);
        
    if (pipe(fd) == -1)
    {
        perror("pipe");
        return (-1);
    }

    shell->in_h = 1;
    
    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        close(fd[0]);
        close(fd[1]);
        shell->in_h = 0;
        return (-1);
    }
    else if (pid == 0)  // Child process
    {
        close(fd[0]);
        heredoc_child_process(fd[1], delimiter);
        exit(1);
    }
    else  // Parent process
    {
        close(fd[1]);
        
        signal(SIGINT, SIG_IGN);
        waitpid(pid, &status, 0);
        
        shell->in_h = 0;
        signals_prompt();
        
        if (WIFSIGNALED(status))
        {
            if (WTERMSIG(status) == SIGINT)
            {
                printf("\n");
                shell->exit_status = 130;
            }
            else
            {
                shell->exit_status = 128 + WTERMSIG(status);
            }
            close(fd[0]);
            return (-1);
        }
        else if (WIFEXITED(status))
        {
            shell->exit_status = WEXITSTATUS(status);
            if (shell->exit_status == 0)
                return (fd[0]);
            else if (shell->exit_status == 42)
            {
                close(fd[0]);
                return (-1);
            }
        }
        
        close(fd[0]);
        return (-1);
    }
}
