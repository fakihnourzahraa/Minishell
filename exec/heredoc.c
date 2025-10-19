/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:33:35 by miwehbe           #+#    #+#             */
/*   Updated: 2025/10/18 16:10:16 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

extern int	g_signal;

// char	*expand_variables(char *line, t_shell *shell)
// {
// 	expand()
// }

/*static void heredoc_child(int write_fd, char **delims, int count,t_shell *shell)
{
    char *line;
    int idx;
	char	*expanded;

    idx = 0;
    signals_child_heredoc();
    while (1)
    {
        line = readline("> ");
        if (!line)
        {
            g_signal = -1;
            close(write_fd);
            exit(0);
        }
        if (ft_strcmp(line, delims[idx]) == 0)
        {
           
            idx++;
            free(line);
            if (idx >= count)
            {
                cleanup_child_process(shell);
                close(write_fd);
                exit(0);
            }
            continue;
        }
        if (idx == count - 1)
        {
			char	*b = ft_strdup(line);
			expanded = expand(shell, b, true);
			write(write_fd, expanded, ft_strlen(expanded));
			write(write_fd, "\n", 1);
			free(expanded);
            // write(write_fd, line, ft_strlen(line));
            // write(write_fd, "\n", 1);
        }
        free(line);
    }
}

static int run_heredoc_internal(char **delims, int count, t_shell *shell)
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
        heredoc_child(fd[1], delims, count,shell);
        exit(1);
    }
    
    close(fd[1]);
    signal(SIGINT, SIG_IGN);
    waitpid(pid, &status, 0);
    shell->in_h = 0;
    signals_prompt();

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
        {
            return fd[0];
        }
    }
    close(fd[0]);
    return (-1);
}
*/
int	run_heredoc(char *delimiter, t_shell *shell)
{
    char *delims[2] = { delimiter, NULL };

    return (run_heredoc_internal(delims, 1, shell));
}

int	run_multiple_heredocs(char **delimiters, int count, t_shell *shell)
{
    return (run_heredoc_internal(delimiters, count, shell));
}
