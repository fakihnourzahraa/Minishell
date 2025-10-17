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
	node->val = ft_strdup(value);
	if (!node->name || !node->val)
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
		val = ft_strdup("");
	if (!val)
		return (1);
	node->val = val;
	node->avail = available;
	return (0);
}

int	set_env_var(t_env **env, const char *name,
		const char *value, bool available)
{
	t_env	*node;
	char	*val;

	if (!env || !name)
		return (1);
	node = find_env_var(*env, name);
	if (node)
		return (update_existing_env(node, value, available));
	if (value)
		val = ft_strdup(value);
	else
		val = ft_strdup("");
	node = create_env_node(name, val, available);
	free(val);
	if (!node)
		return (1);
	node->next = *env;
	*env = node;
	return (0);
}
