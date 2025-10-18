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

static void	print_env_list(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (current->avail && current->val)
		{
			ft_putstr_fd(current->name, 1);
			ft_putchar_fd('=', 1);
			ft_putstr_fd(current->val, 1);
			ft_putchar_fd('\n', 1);
		}
		current = current->next;
	}
}

static void	execute_child_process(char *path, char **cmd_args, t_shell *shell)
{
	char	**envp_array;

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

static void	handle_parent_process(pid_t pid, t_shell *shell, char *path)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
	else
		shell->exit_status = 1;
	free(path);
}

static void	execute_env_command(t_shell *shell, char **cmd_args)
{
	char	*path;
	pid_t	pid;

	path = get_cmd_path(cmd_args[0], shell);
	if (!path)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(cmd_args[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		shell->exit_status = 127;
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free(path);
		shell->exit_status = 1;
		return ;
	}
	else if (pid == 0)
		execute_child_process(path, cmd_args, shell);
	else
		handle_parent_process(pid, shell, path);
}

void	builtin_env(t_cmd *cmd, t_shell *shell)
{
	if (cmd->args[1] == NULL)
	{
		print_env_list(shell->env);
		shell->exit_status = 0;
		return ;
	}
	execute_env_command(shell, &cmd->args[1]);
}
