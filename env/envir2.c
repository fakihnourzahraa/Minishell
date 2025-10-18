/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 20:45:04 by miwehbe           #+#    #+#             */
/*   Updated: 2025/09/11 20:45:04 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static t_env	*create_env_node(const char *name,
		const char *value, bool available)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->name = ft_strdup(name);
	if (value)
		node->val = ft_strdup(value);
	else
		node->val = NULL; 
	if (!node->name )
	{
		free(node->name);
		free(node->val);
		free(node);
		return (NULL);
	}
	node->avail = available;
	node->next = NULL;
	return (node);
}

static int	update_existing_env(t_env *node, const char *value, bool available)
{
	char	*val;

	free(node->val);
	if (value)
		val = ft_strdup(value);
	else
		val = NULL;
	node->val = val;
	node->avail = available;
	return (0);
}

int	set_env_var(t_env **env, const char *name,
		const char *value, bool available)
{
	t_env	*node;

	if (!env || !name)
		return (1);
	node = find_env_var(*env, name);
	if (node)
		return (update_existing_env(node, value, available));
	node = create_env_node(name, value, available);
	if (!node)
		return (1);
	node->next = *env;
	*env = node;
	return (0);
}
