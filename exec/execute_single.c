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
#include <sys/stat.h>

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
    if (errno == EACCES)
    {
        printf("minishell: %s: Permission denied\n", cmd->args[0]);
        cleanup_child_process(shell);
        free_envp(envp_array);
        exit(126);
    }
    cleanup_child_process(shell);
    free_envp(envp_array);
    exit(127);
}

static int check_command_access(const char *cmd)
{
    struct stat st;

    if (stat(cmd, &st) == -1)
    {
        if (errno == ENOENT)
            return (127);
        return (126);
    }
    if (access(cmd, X_OK) == -1)
    {
        if (errno == EACCES)
            return (126);
        return (127);
    }
    return (0);
}

static int execute_external_command(t_shell *shell, t_cmd *cmd)
{
    pid_t pid;
    int status;
    char *path;
    int access_result;
	
    if (ft_strchr(cmd->args[0], '/'))
    {
        access_result = check_command_access(cmd->args[0]);
        if (access_result == 126)
        {
            printf("minishell: %s: Permission denied\n", cmd->args[0]);
            shell->exit_status = 126;
            return (1);
        }
        else if (access_result == 127)
        {
            printf("minishell: %s: No such file or directory\n", cmd->args[0]);
            shell->exit_status = 127;
            return (1);
        }
    }

    path = get_cmd_path(cmd->args[0], shell);
    if (!path)
    {
        // Check if it's a permission issue before saying "not found"
        if (ft_strchr(cmd->args[0], '/'))
        {
            access_result = check_command_access(cmd->args[0]);
            if (access_result == 126)
            {
                printf("minishell: %s: Permission denied\n", cmd->args[0]);
                shell->exit_status = 126;
                return (1);
            }
        }
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
    
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    
    waitpid(pid, &status, 0);
    signals_prompt();
    
    free(cmd->path);
    cmd->path = NULL;
    
    wait_child(shell, status);
    return (1);
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
    
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    
    waitpid(pid, &status, 0);
    signals_prompt();
    
    free(cmd->path);
    cmd->path = NULL;
    
    wait_child(shell, status);
    return (1);
}
*/
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

static bool is_valid_var_name(char *str, int len)
{
    int i;
    
    if (len == 0 || (!ft_isalpha(str[0]) && str[0] != '_'))
        return (false);
    
    i = 1;
    while (i < len)
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (false);
        i++;
    }
    return (true);
}

int	execute_single(t_shell *shell, t_cmd *cmd)
{
    char	*equal_sign;
    char	*var_name;
    char	*var_value;
    
    if (!cmd || !cmd->args || !cmd->args[0] || !shell)
        return (0);
    equal_sign = ft_strchr(cmd->args[0], '=');
    if (equal_sign && is_valid_var_name(cmd->args[0], equal_sign - cmd->args[0]))
    {
        var_name = ft_strndup(cmd->args[0], equal_sign - cmd->args[0]);
        var_value = ft_strdup(equal_sign + 1);
        set_env_var(&shell->env, var_name, var_value, true);    
        free(var_name);
        free(var_value);
        return (1);
    }
    if (cmd->builtin != NOT_BUILTIN)
    {
        if (cmd->rd)
            return (execute_builtin_with_redirect(shell, cmd));
        execute_builtin(cmd, shell);
        return (1);
    }
    return (execute_external_command(shell, cmd));
}
