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

static void wait_child(t_shell *shell, int status)
{
    if (WIFEXITED(status))
        shell->exit_status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        shell->exit_status = 128 + WTERMSIG(status);
    else
        shell->exit_status = 1;
}

static void exec_external_child(t_shell *shell, t_cmd *cmd)
{
    char **envp_array;

    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    
    if (apply_redirections(cmd, shell) == -1)
    {
        cleanup_child_process(shell);
        exit(1);
    }
    
    envp_array = env_to_envp(shell->env);
    if (!envp_array)
    {
        cleanup_child_process(shell);
        exit(1);
    }
    
    execve(cmd->path, cmd->args, envp_array);
    
    cleanup_child_process(shell);
    free_envp(envp_array);
    exit(127);
}

static int execute_external_command(t_shell *shell, t_cmd *cmd)
{
    pid_t pid;
    int status;
    char *path;

    path = get_cmd_path(cmd->args[0], shell);
    if (!path)
    {
        printf("minishell: %s: command not found\n", cmd->args[0]);
        shell->exit_status = 127;
        return (1);
    }
    
    cmd->path = path;
    
    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        free(cmd->path);
        cmd->path = NULL;
        return (1);
    }
    if (pid == 0)
        exec_external_child(shell, cmd);
    
    free(cmd->path);
    cmd->path = NULL;
    
    waitpid(pid, &status, 0);
    wait_child(shell, status);
    return (1);
}
static int execute_builtin_with_redirect(t_shell *shell, t_cmd *cmd)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return (1);
    }
    if (pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        if (apply_redirections(cmd, shell) == -1)
        {
            cleanup_child_process(shell);
            exit(1);
        }
        execute_builtin(cmd, shell);
        cleanup_child_process(shell); 
        exit(shell->exit_status);
    }
    waitpid(pid, &status, 0);
    wait_child(shell, status);
    return (1);
}

int execute_single(t_shell *shell, t_cmd *cmd)
{
    if (!cmd || !cmd->args || !cmd->args[0] || !shell)
        return (0);
    if (cmd->builtin != NOT_BUILTIN)
    {
        if (cmd->rd)
            return (execute_builtin_with_redirect(shell, cmd));
        execute_builtin(cmd, shell);
        return (1);
    }
    return (execute_external_command(shell, cmd));
}
