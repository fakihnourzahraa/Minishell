/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_help2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 09:37:12 by miwehbe           #+#    #+#             */
/*   Updated: 2025/10/18 09:37:12 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	handle_absolute_path(t_shell *shell, t_cmd *cmd)
{
	int	access_result;

	if (!ft_strchr(cmd->args[0], '/'))
		return (0);
	access_result = check_command_access(cmd->args[0]);
	if (access_result == 126)
	{
		if (errno == EISDIR)
			printf("minishell: %s: Is a directory\n", cmd->args[0]);
		else
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
	return (0);
}

int	handle_command_path(t_shell *shell, t_cmd *cmd, char **path)
{
	char	*path_env;

	if (handle_absolute_path(shell, cmd))
		return (1);
	path_env = get_env_value(shell->env, "PATH");
	*path = get_cmd_path(cmd->args[0], shell);
	if (!*path)
	{
		if (!path_env)
			printf("minishell: %s: No such file or directory\n", cmd->args[0]);
		else
			printf("minishell: %s: command not found\n", cmd->args[0]);
		shell->exit_status = 127;
		return (1);
	}
	return (0);
}

bool	is_valid_var_name(char *str, int len)
{
	int	i;

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

int	handle_variable_assignment(t_shell *shell, t_cmd *cmd)
{
	char	*equal_sign;
	char	*var_name;
	char	*var_value;

	equal_sign = ft_strchr(cmd->args[0], '=');
	if (!equal_sign)
		return (0);
	if (!is_valid_var_name(cmd->args[0], equal_sign - cmd->args[0]))
		return (0);
	var_name = ft_strndup(cmd->args[0], equal_sign - cmd->args[0]);
	var_value = ft_strdup(equal_sign + 1);
	set_env_var(&shell->env, var_name, var_value, true);
	free(var_name);
	free(var_value);
	return (1);
}

/*int	handle_command_path(t_shell *shell, t_cmd *cmd, char **path)
{
	if (handle_absolute_path(shell, cmd))
		return (1);
	*path = get_cmd_path(cmd->args[0], shell);
	if (!*path)
	{
		printf("minishell: %s: command not found\n", cmd->args[0]);
		shell->exit_status = 127;
		return (1);
	}
	return (0);
}*/