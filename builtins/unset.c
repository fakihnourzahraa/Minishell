/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:18:40 by miwehbe           #+#    #+#             */
/*   Updated: 2025/09/13 17:18:40 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	unset_env_var(t_env **env, const char *name)
{
	t_env	*current;

	if (!env || !name || !*env)
		return (1);
	if (ft_strcmp((*env)->name, name) == 0)
	{
		remove_head(env);
		return (0);
	}
	current = *env;
	while (current->next)
	{
		if (ft_strcmp(current->next->name, name) == 0)
		{
			remove_next_node(current);
			return (0);
		}
		current = current->next;
	}
	return (0);
}

static void	handle_unset_arg(t_shell *shell, char *arg)
{
	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("unset: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		shell->exit_status = 1;
		return ;
	}
	unset_env_var(&shell->env, arg);
}

void	builtin_unset(t_cmd *cmd, t_shell *shell)
{
	int	i;

	if (!cmd->args[1])
	{
		shell->exit_status = 0;
		return ;
	}
	i = 1;
	while (cmd->args[i])
	{
		handle_unset_arg(shell, cmd->args[i]);
		i++;
	}
	if (shell->exit_status != 1)
		shell->exit_status = 0;
}
