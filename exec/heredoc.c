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

/*static void	child_heredoc_loop(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			close(fd);
			exit(0);
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}


static void	child_heredoc(int fd[2], char *delimiter)
{
	signals_child_heredoc();
	close(fd[0]);
	child_heredoc_loop(fd[1], delimiter);
}

static int	parent_heredoc(t_shell *shell, int fd[2], pid_t pid)
{
	int	status;

	close(fd[1]);
	waitpid(pid, &status, 0);
	shell->in_h = 0;
	if (WIFSIGNALED(status))
		return (close(fd[0]), shell->exit_status = 130, -1);
	if (WIFEXITED(status))
		return (shell->exit_status = WEXITSTATUS(status), fd[0]);
	close(fd[0]);
	shell->exit_status = 1;
	return (-1);
}


int	run_heredoc(char *delimiter, t_shell *shell)
{
	int		fd[2];
	pid_t	pid;

	if (!delimiter || !shell)
		return (-1);
	if (pipe(fd) == -1)
		return (perror("pipe"), -1);
	shell->in_h = 1;
	pid = fork();
	if (pid < 0)
		return (perror("fork"), close(fd[0]), close(fd[1]), shell->in_h = 0, -1);
	if (pid == 0)
		child_heredoc(fd, delimiter);
	return (parent_heredoc(shell, fd, pid));
}*/


//when i said write(1,..,..)== write to stdout(terminal)
//but when i said write(fd[1],...,...)== write to the write of pipe 
//signal(SIGINT, SIG_DFL);SIG_DFL :default behave :terminate process
//SIGINT = is sign nbr =2 it is for ctrl+c

/*int run_heredoc(char *delimiter, t_shell *shell)
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
*/


// FIXED: exec/heredoc.c
/*#include "exec.h"

// Child process heredoc handler - handles Ctrl+C properly
static void heredoc_child_process(int write_fd, char *delimiter)
{
    char *line;
    
    // CRITICAL: Set up signals for heredoc child
    signal(SIGINT, SIG_DFL);   // Default Ctrl+C behavior (terminate)
    signal(SIGQUIT, SIG_IGN);  // Ignore Ctrl+\ in heredoc
    
    while (1)
    {
        line = readline("> ");
        
        // Handle Ctrl+D (EOF)
        if (!line)
        {
            close(write_fd);
            exit(0);
        }
        
        // Check for delimiter
        if (ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            close(write_fd);
            exit(0);
        }
        
        // Write line to pipe
        write(write_fd, line, ft_strlen(line));
        write(write_fd, "\n", 1);
        free(line);
    }
}

// FIXED: Main heredoc function with proper signal handling
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

    // Mark that we're in heredoc mode
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
        close(fd[0]);  // Child only writes
        heredoc_child_process(fd[1], delimiter);
        // Should never reach here
        exit(1);
    }
    else  // Parent process
    {
        close(fd[1]);  // Parent only reads
        
        // CRITICAL: Parent ignores Ctrl+C while waiting for heredoc
        signal(SIGINT, SIG_IGN);
        
        waitpid(pid, &status, 0);
        
        // FIXED: Reset shell state
        shell->in_h = 0;
        
        // CRITICAL: Restore normal signal handling IMMEDIATELY
        signals_prompt();
        
        // Handle child exit status
        if (WIFSIGNALED(status))
        {
            // Child was killed by signal (Ctrl+C)
            if (WTERMSIG(status) == SIGINT)
            {
                // Bash prints newline after ^C in heredoc
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
                return (fd[0]);  // Return read end for successful heredoc
        }
        
        close(fd[0]);
        return (-1);
    }
}*/

/*#include "exec.h"

// Child process heredoc handler - handles Ctrl+C properly
static void heredoc_child_process(int write_fd, char *delimiter)
{
    char *line;
    
    // CRITICAL: Set up signals for heredoc child
    signal(SIGINT, SIG_DFL);   // Default Ctrl+C behavior (terminate)
    signal(SIGQUIT, SIG_IGN);  // Ignore Ctrl+\ in heredoc
    
    printf("DEBUG: Child started, delimiter='%s'\n", delimiter);  // DEBUG
    
    while (1)
    {
        printf("DEBUG: Child calling readline...\n");  // DEBUG
        line = readline("> ");
        
        // Handle Ctrl+D (EOF)
        if (!line)
				{
    			printf("DEBUG: Child got NULL (Ctrl+D), exiting with 0\n");  // KEEP DEBUG
    
    			// ADD WARNING MESSAGE:
    			ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", 2);
    			ft_putstr_fd(delimiter, 2);
    			ft_putstr_fd("')\n", 2);
    
    			close(write_fd);
    			exit(42);  // CHANGE: Exit with 42 instead of 0
				}
        
        printf("DEBUG: Child got line='%s'\n", line);  // DEBUG
        
        // Check for delimiter
        if (ft_strcmp(line, delimiter) == 0)
        {
            printf("DEBUG: Found delimiter, exiting\n");  // DEBUG
            free(line);
            close(write_fd);
            exit(0);
        }
        
        // Write line to pipe
        write(write_fd, line, ft_strlen(line));
        write(write_fd, "\n", 1);
        free(line);
    }
}

// FIXED: Main heredoc function with proper signal handling
int run_heredoc(char *delimiter, t_shell *shell)
{
    int fd[2];
    pid_t pid;
    int status;

    printf("DEBUG: Starting heredoc with delimiter='%s'\n", delimiter);  // DEBUG

    if (!delimiter || !shell)
        return (-1);
        
    if (pipe(fd) == -1)
    {
        perror("pipe");
        return (-1);
    }

    // Mark that we're in heredoc mode
    shell->in_h = 1;
    printf("DEBUG: Set shell->in_h = 1\n");  // DEBUG
    
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
        close(fd[0]);  // Child only writes
        heredoc_child_process(fd[1], delimiter);
        // Should never reach here
        exit(1);
    }
    else  // Parent process
    {
        close(fd[1]);  // Parent only reads
        
        printf("DEBUG: Parent waiting for child pid %d\n", pid);  // DEBUG
        
        // CRITICAL: Parent ignores Ctrl+C while waiting for heredoc
        signal(SIGINT, SIG_IGN);
        
        waitpid(pid, &status, 0);
        
        printf("DEBUG: Child finished with status %d\n", status);  // DEBUG
        
        // FIXED: Reset shell state
        shell->in_h = 0;
        printf("DEBUG: Set shell->in_h = 0\n");  // DEBUG
        
        // CRITICAL: Restore normal signal handling IMMEDIATELY
        signals_prompt();
        
        // Handle child exit status
        if (WIFSIGNALED(status))
        {
            printf("DEBUG: Child was killed by signal %d\n", WTERMSIG(status));  // DEBUG
            // Child was killed by signal (Ctrl+C)
            if (WTERMSIG(status) == SIGINT)
            {
                // Bash prints newline after ^C in heredoc
                printf("\n");
                shell->exit_status = 130;
            }
            else
            {
                shell->exit_status = 128 + WTERMSIG(status);
            }
            close(fd[0]);
            printf("DEBUG: Returning -1 (signal)\n");  // DEBUG
            return (-1);
        }
        else if (WIFEXITED(status))
        {
            int exit_code = WEXITSTATUS(status);
            printf("DEBUG: Child exited with code %d\n", exit_code);  // DEBUG
            
            shell->exit_status = exit_code;
            if (shell->exit_status == 0)
            {
                printf("DEBUG: Returning fd[0]=%d (success)\n", fd[0]);  // DEBUG
                return (fd[0]);  // Return read end for successful heredoc
            }
						else if (shell->exit_status == 42)  // EOF case
						{
    					printf("DEBUG: EOF case, returning -1\n");
    					close(fd[0]);
    					return (-1);  // Don't execute command
						}
        }
        
        printf("DEBUG: Returning -1 (error)\n");  // DEBUG
        close(fd[0]);
        return (-1);
    }
}*/


#include "exec.h"

static void heredoc_child_process(int write_fd, char *delimiter)
{
    char *line;
    
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_IGN);
    
    while (1)
    {
        line = readline("> ");
        
        // Handle Ctrl+D (EOF)
        if (!line)
        {
            ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", 2);
            ft_putstr_fd(delimiter, 2);
            ft_putstr_fd("')\n", 2);
            close(write_fd);
            exit(42);  // Special exit code for EOF
        }
        
        // Check for delimiter
        if (ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            close(write_fd);
            exit(0);
        }
        
        // Write line to pipe
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
            else if (shell->exit_status == 42)  // EOF case
            {
                close(fd[0]);
                return (-1);  // Don't execute command
            }
        }
        
        close(fd[0]);
        return (-1);
    }
}
