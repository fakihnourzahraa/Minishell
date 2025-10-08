/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:32:43 by miwehbe           #+#    #+#             */
/*   Updated: 2025/09/13 12:32:43 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void print_exported_vars(t_shell *shell)
{
	t_env	*vars[1024];
	int		count;
	int		i;

	count = collect_exported_vars(shell, vars);
	sort_exported_vars(vars, count);
	i = 0;
	while (i < count)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(vars[i]->name, 1);
		if (vars[i]->val)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(vars[i]->val, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putchar_fd('\n', 1);
		i++;
	}
}

static void	handle_export_with_value(
				t_shell *shell, char *arg, char *equal_pos)
{
	char	*name;
	char	*value;

	name = ft_substr(arg, 0, equal_pos - arg);
	if (!is_valid_identifier(name))
	{
		ft_putstr_fd("export: not a valid identifier: ", 2);
		ft_putendl_fd(arg, 2);
		shell->exit_status = 1;
		free(name);
		return ;
	}
	value = ft_strdup(equal_pos + 1);
	set_env_var(&shell->env, name, value, true);
	free(name);
	free(value);
}

static void	handle_export_without_value(t_shell *shell, char *arg)
{
	t_env	*var;

	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("export: not a valid identifier: ", 2);
		ft_putendl_fd(arg, 2);
		shell->exit_status = 1;
		return ;
	}
	var = find_env_var(shell->env, arg);
	if (var)
		var->avail = true;
	else
		set_env_var(&shell->env, arg, "", true);
}

void	builtin_export(t_cmd *cmd, t_shell *shell)
{
	int		i;
	char	*equal_pos;

	if (!cmd->args[1])
	{
		print_exported_vars(shell);
		shell->exit_status = 0;
		return ;
	}
	i = 1;
	while (cmd->args[i])
	{
		equal_pos = ft_strchr(cmd->args[i], '=');
		if (equal_pos)
			handle_export_with_value(shell, cmd->args[i], equal_pos);
		else
			handle_export_without_value(shell, cmd->args[i]);
		i++;
	}
	if (shell->exit_status != 1)
		shell->exit_status = 0;
}
