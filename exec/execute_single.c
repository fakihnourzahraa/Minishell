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

/*void cleanup_child_process(t_shell *shell)
{
    //printf("DEBUG: cleanup_child_process called in PID %d\n", getpid()); // ← Add this
    
    if (shell->env)
    {
        //printf("DEBUG: freeing environment variables\n"); // ← Add this
        free_env_list(shell->env);
        shell->env = NULL;
    }
    cleanup_t(shell);
    cleanup_p(shell);

    if (shell->in)
    {
        free(shell->in);
        shell->in = NULL;
    }
    //printf("DEBUG: cleanup_child_process finished\n"); // ← Add this
}*/

static void wait_child(t_shell *shell, int status)
{
    if (WIFEXITED(status))
        shell->exit_status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        shell->exit_status = 128 + WTERMSIG(status);
    else
        shell->exit_status = 1;
}

/*static void exec_external_child(t_shell *shell, t_cmd *cmd, char *path)
{
    char **envp_array;

    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    
    if (apply_redirections(cmd, shell) == -1)
    {
        cleanup_child_process(shell);
        free(path);
        exit(1);
    }
    envp_array = env_to_envp(shell->env);
    if (!envp_array)
    {
        cleanup_child_process(shell);
        free(path);
        exit(1);
    }
    execve(cmd->path, cmd->args, envp_array);
    printf("DEBUG: execve failed\n");

    cleanup_child_process(shell);  
    free_envp(envp_array);
    free(path);
    exit(127);
}*/
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

/*static int execute_external_command(t_shell *shell, t_cmd *cmd)
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
    cmd->path = ft_strdup(path);  // Make a copy for cmd
    if (!cmd->path)
    {
        free(path);
        return (1);
    }
    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        free(path);
        return (1);
    }
    if (pid == 0)
        exec_external_child(shell, cmd, path);
    free(path);
    free(cmd->path);
    cmd->path = NULL;
    waitpid(pid, &status, 0);
    wait_child(shell, status);
    return (1);
}*/
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
        exec_external_child(shell, cmd);  // Don't pass path parameter
    
    // Parent cleans up
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
            //exit(1);
    
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
