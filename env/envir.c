/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 20:42:11 by miwehbe           #+#    #+#             */
/*   Updated: 2025/09/11 20:42:11 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int	parse_and_set_env_fields(t_env *node, char *str)
{
	char	*equal_sign;
	int		name_len;

	equal_sign = ft_strchr(str, '=');
	if (equal_sign)
	{
		name_len = equal_sign - str;
		node->name = ft_strndup(str, name_len);
		node->val = ft_strdup(equal_sign + 1);
	}
	else
	{
		node->name = ft_strdup(str);
		node->val = ft_strdup("");
	}
	if (!node->name || !node->val)
		return (1);
	return (0);
}

static t_env	*create_env_node_from_str(char *str)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	if (parse_and_set_env_fields(node, str))
	{
		free(node->name);
		free(node->val);
		free(node);
		return (NULL);
	}
	node->avail = true;
	node->next = NULL;
	return (node);
}

t_env	*init_env_from_envp(char **envp)
{
	t_env	*head;
	t_env	*current;
	t_env	*newnode;
	int		i;

	head = NULL;
	current = NULL;
	i = 0;
	while (envp[i])
	{
		newnode = create_env_node_from_str(envp[i]);
		if (!newnode)
		{
			free_env_list(head);
			return (NULL);
		}
		if (!head)
			head = newnode;
		else
			current->next = newnode;
		current = newnode;
		i++;
	}
	return (head);
}

t_env	*find_env_var(t_env *env, const char *name)
{
	t_env	*current;

	if (!env || !name)
		return (NULL);
	current = env;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

char	*get_env_value(t_env *env, const char *name)
{
	t_env	*node;

	node = find_env_var(env, name);
	if (!node || node->avail == false)
		return (NULL);
	return (node->val);
}
