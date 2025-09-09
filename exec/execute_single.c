/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 09:02:13 by miwehbe           #+#    #+#             */
/*   Updated: 2025/09/01 09:02:13 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/*int execute_single(t_shell *shell, t_cmd *cmd)
{
    pid_t pid;
    int status;
    char *path;

    if (!cmd || !cmd->args || !cmd->args[0] || !shell)
        return (0);

    if (cmd->builtin != NOT_BUILTIN)
    {
        if (apply_redirections(cmd, shell) == -1)
            return (1);
        execute_builtin(cmd, shell);
        return 1;
    }

    path = get_cmd_path(cmd->args[0], shell);
    if (!path)
    {
        printf("minishell: %s: command not found\n", cmd->args[0]);
        shell->exit_status = 127;
        return 1;
    }

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        free(path);
        return 1;
    }
    else if (pid == 0)
    {
        if (apply_redirections(cmd,shell) == -1)
            exit(1); // Redirection error already printed in apply_redirections
        execve(path, cmd->args, shell->envp);
        perror("execve");
        free(path);
        exit(1);
    }
    else
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            shell->exit_status = WEXITSTATUS(status);
        else
            shell->exit_status = 1;
        free(path);
    }
    return 1;
}
*/


int execute_single(t_shell *shell, t_cmd *cmd)
{
    pid_t pid;
    int status;
    char *path;

    if (!cmd || !cmd->args || !cmd->args[0] || !shell)
        return (0);

    if (cmd->builtin != NOT_BUILTIN)
    {
        // If builtin has redirections, we MUST fork to avoid messing up shell's stdin/stdout
        if (cmd->rd)
        {
            pid = fork();
            if (pid < 0)
            {
                perror("fork");
                return (1);
            }
            else if (pid == 0)  // Child process
            {
                // Apply redirections in child
                if (apply_redirections(cmd, shell) == -1)
                    exit(1);
                
                // Execute builtin in child
                execute_builtin(cmd, shell);
                exit(shell->exit_status);
            }
            else  // Parent process
            {
                // Wait for child and get exit status
                waitpid(pid, &status, 0);
                if (WIFEXITED(status))
                    shell->exit_status = WEXITSTATUS(status);
                else
                    shell->exit_status = 1;
            }
        }
        else
        {
            // No redirections, execute builtin directly in parent
            execute_builtin(cmd, shell);
        }
        return (1);
    }

    // Handle external commands (unchanged)
    path = get_cmd_path(cmd->args[0], shell);
    if (!path)
    {
        printf("minishell: %s: command not found\n", cmd->args[0]);
        shell->exit_status = 127;
        return (1);
    }

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        free(path);
        return (1);
    }
    else if (pid == 0)  // Child process
    {
        if (apply_redirections(cmd, shell) == -1)
            exit(1);
            
        execve(path, cmd->args, shell->envp);
        perror("execve");
        free(path);
        exit(127);
    }
    else  // Parent process
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            shell->exit_status = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            shell->exit_status = 128 + WTERMSIG(status);
        else
            shell->exit_status = 1;
        free(path);
    }
    return (1);
}