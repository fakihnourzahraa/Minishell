/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envir.utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 23:07:15 by miwehbe           #+#    #+#             */
/*   Updated: 2025/09/11 23:07:15 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	remove_head(t_env **env)
{
	t_env	*to_remove;

	to_remove = *env;
	*env = (*env)->next;
	free(to_remove->name);
	free(to_remove->val);
	free(to_remove);
}

void	remove_next_node(t_env *current)
{
	t_env	*tmp;

	tmp = current->next;
	current->next = tmp->next;
	free(tmp->name);
	free(tmp->val);
	free(tmp);
}

void	free_env_list(t_env *env)
{
	t_env	*current;
	t_env	*next;

	current = env;
	while (current)
	{
		next = current->next;
		if (current->name)
		{
			free(current->name);
			current->name = NULL;
		}
		if (current->val)
		{
			free(current->val);
			current->val = NULL;
		}
		free(current);
		current = next;
	}
}

void	free_envp(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	free_envp_partial(char **envp, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}
