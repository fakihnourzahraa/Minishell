/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 19:09:19 by miwehbe           #+#    #+#             */
/*   Updated: 2025/09/10 19:09:19 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void update_shlvl_on_start(t_shell *shell)
{
    t_env *shlvl = find_env_var(shell->env, "SHLVL");
    int lvl;

    if (shlvl && shlvl->val)
        lvl = ft_atoi(shlvl->val) + 1;
    else
        lvl = 1;
    if (!shlvl)
    {
        set_env_var(&shell->env, "SHLVL", "1",true);
    }
    else
    {
        free(shlvl->val);
        shlvl->val = ft_itoa(lvl);
    }
}

void update_shlvl_on_exit(t_shell *shell)
{
    t_env *shlvl = find_env_var(shell->env, "SHLVL");
    if (!shlvl)
        return;
    int lvl = ft_atoi(shlvl->val);
    if (lvl > 1)
        lvl--;
    set_env_var(&shell->env, "SHLVL", ft_itoa(lvl), true);
}

static void    print_env_list(t_env *env)
{
  t_env   *current;

  current = env;
  while (current)
  {
    if (current->avail)
    {
      ft_putstr_fd(current->name, 1);
      ft_putchar_fd('=', 1);
      ft_putstr_fd(current->val, 1);
      ft_putchar_fd('\n', 1);
    }
    current = current->next;
  }
}
static void execute_env_command(t_shell *shell, char **cmd_args)
{
    char *path;
    char **envp_array;
    pid_t pid;
    int status;
    path = get_cmd_path(cmd_args[0], shell);
    if (!path)
    {
        ft_putstr_fd("env: ", 2);
        ft_putstr_fd(cmd_args[0], 2);
        ft_putstr_fd(": No such file or directory\n", 2);
        shell->exit_status = 127;
        return;
    }
    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        free(path);
        shell->exit_status = 1;
        return;
    }
    else if (pid == 0)
    {
        envp_array = env_to_envp(shell->env);
        if (!envp_array)
        {
            free(path);
            exit(1);
        }
        execve(path, cmd_args, envp_array);
        perror("execve");
        free_envp(envp_array);
        free(path);
        exit(127);
    }
    else
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
}

void builtin_env(t_cmd *cmd, t_shell *shell)
{
    if (cmd->args[1] == NULL)
    {
        print_env_list(shell->env);
        shell->exit_status = 0;
        return;
    }
    execute_env_command(shell, &cmd->args[1]);
}