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

extern int g_signal;

static void heredoc_child(int write_fd, char **delims, int count,t_shell *shell)
{
    char *line;
    int idx;

    //printf("DEBUG: heredoc_child started\n");
    idx = 0;
    signals_child_heredoc();
    while (1)
    {
        line = readline("> ");
        //printf("DEBUG: heredoc_child read line: '%s'\n", line ? line : "(null)");
        if (!line)
        {
            //printf("DEBUG: heredoc_child got EOF\n");
            g_signal = -1;
            close(write_fd);
            exit(0);
        }
        if (ft_strcmp(line, delims[idx]) == 0)
        {
            //printf("DEBUG: heredoc_child found delimiter: '%s'\n", delims[idx]);
            idx++;
            free(line);
            if (idx >= count)
            {
                //printf("DEBUG: heredoc_child all delimiters found\n");
                cleanup_child_process(shell);
                close(write_fd);
                exit(0);
            }
            continue;
        }
        if (idx == count - 1)
        {
            //printf("DEBUG: heredoc_child writing line to pipe\n");
            write(write_fd, line, ft_strlen(line));
            write(write_fd, "\n", 1);
        }
        free(line);
    }
}

/*static int run_heredoc_internal(char **delims, int count, t_shell *shell)
{
    int fd[2];
    pid_t pid;
    int status;

    if (pipe(fd) == -1)
        return (-1);
    shell->in_h = 1;
    pid = fork();
    if (pid < 0)
    {
        close(fd[0]);
        close(fd[1]);
        shell->in_h = 0;
        return (-1);
    }
    else if (pid == 0)
    {
        close(fd[0]);
        heredoc_child(fd[1], delims, count);
        exit(1);
    }
    close(fd[1]);
    signal(SIGINT, SIG_IGN);
    waitpid(pid, &status, 0);
    shell->in_h = 0;
    //signals_prompt();

    if (WIFSIGNALED(status))
    {
        if (WTERMSIG(status) == SIGINT)
            shell->exit_status = 130;
        else
            shell->exit_status = 128 + WTERMSIG(status);
        close(fd[0]);
        return (-1);
    }
    else if (WIFEXITED(status))
    {
        shell->exit_status = WEXITSTATUS(status);

        if (g_signal == -1)
        {
            close(fd[0]);
            return (-1);
        }
        if (shell->exit_status == 0)
            return fd[0];
    }

    close(fd[0]);
    return (-1);
}*/
static int run_heredoc_internal(char **delims, int count, t_shell *shell)
{
    int fd[2];
    pid_t pid;
    int status;

    //printf("DEBUG: run_heredoc_internal called\n");
    
    if (pipe(fd) == -1)
        return (-1);
    shell->in_h = 1;
    
    pid = fork();
    if (pid < 0)
    {
        close(fd[0]);
        close(fd[1]);
        shell->in_h = 0;
        return (-1);
    }
    else if (pid == 0)
    {
        close(fd[0]);
        heredoc_child(fd[1], delims, count,shell);
        exit(1);
    }
    
    close(fd[1]);
    signal(SIGINT, SIG_IGN);
    waitpid(pid, &status, 0);
    shell->in_h = 0;
    signals_prompt();

    //printf("DEBUG: heredoc child exited with status: %d\n", status);
    
    if (WIFSIGNALED(status))
    {
        if (WTERMSIG(status) == SIGINT)
            shell->exit_status = 130;
        else
            shell->exit_status = 128 + WTERMSIG(status);
        close(fd[0]);
        //printf("DEBUG: heredoc was signaled, closing fd\n");
        return (-1);
    }
    else if (WIFEXITED(status))
    {
        shell->exit_status = WEXITSTATUS(status);

        if (g_signal == -1)
        {
            close(fd[0]);
            //printf("DEBUG: g_signal == -1, closing fd\n");
            return (-1);
        }
        if (shell->exit_status == 0)
        {
            //printf("DEBUG: heredoc successful, returning fd[0]: %d\n", fd[0]);
            return fd[0];
        }
    }

    //printf("DEBUG: heredoc failed, closing fd\n");
    close(fd[0]);
    return (-1);
}


int run_heredoc(char *delimiter, t_shell *shell)
{
    char *delims[2] = { delimiter, NULL };
    return run_heredoc_internal(delims, 1, shell);
}

int run_multiple_heredocs(char **delimiters, int count, t_shell *shell)
{
    return run_heredoc_internal(delimiters, count, shell);
}
*/