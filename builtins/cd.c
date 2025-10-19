/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:29:11 by miwehbe           #+#    #+#             */
/*   Updated: 2025/09/09 12:29:11 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static char	*handle_cd_error(char *var, char *msg, t_shell *shell)
{
	if (!var)
	{
		ft_putendl_fd(msg, 2);
		shell->exit_status = 1;
		return (NULL);
	}
	return (var);
}

static char	*get_target_dir(t_shell *shell, char *arg)
{
	char	*target;

	if (!arg || ft_strcmp(arg, "~") == 0)
	{
		target = get_env_value(shell->env, "HOME");
		target = handle_cd_error(target, "minishell: HOME not set", shell);
	}
	else if (ft_strcmp(arg, "-") == 0)
	{
		target = get_env_value(shell->env, "OLDPWD");
		target = handle_cd_error(target, "minishell: OLDPWD not set", shell);
		if (target)
			ft_putendl_fd(target, 1);
	}
	else
		target = arg;
	return (target);
}

static void	update_pwd(t_shell *shell, const char *old_pwd)
{
	char	*new_pwd;
	char	*current_pwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		perror("minishell: getcwd fail");
		shell->exit_status = 1;
		return ;
	}
	if (old_pwd)
		set_env_var(&shell->env, "OLDPWD", old_pwd, true);
	else
	{
		current_pwd = get_env_value(shell->env, "PWD");
		if (current_pwd)
			set_env_var(&shell->env, "OLDPWD", current_pwd, true);
		else
			unset_env_var(&shell->env, "OLDPWD");
	}
	set_env_var(&shell->env, "PWD", new_pwd, true);
	free(new_pwd);
}

static void	change_directory(t_shell *shell, char *target, const char *old_pwd)
{
	if (chdir(target) < 0)
	{
		perror("minishell");
		shell->exit_status = 1;
		return ;
	}
	update_pwd(shell, old_pwd);
	shell->exit_status = 0;
}

/*void	builtin_cd(t_cmd *cmd, t_shell *shell)
{
	char	*old_pwd;
	char	*target;

	old_pwd = get_env_value(shell->env, "PWD");
	target = get_target_dir(shell, cmd->args[1]);
	if (!target)
		return ;
	change_directory(shell, target, old_pwd);
}
*/

void	builtin_cd(t_cmd *cmd, t_shell *shell)
{
	char	*old_pwd;
	char	*target;
	int		arg_count;

	arg_count = 0;
	while (cmd->args[arg_count])
		arg_count++;
	if (arg_count > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		shell->exit_status = 1;
		return ;
	}
	old_pwd = get_env_value(shell->env, "PWD");
	target = get_target_dir(shell, cmd->args[1]);
	if (!target)
		return ;
	if (target[0] == '\0')
	{
		shell->exit_status = 0;
		return ;
	}
	change_directory(shell, target, old_pwd);
}
