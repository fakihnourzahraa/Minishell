/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envir3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 20:45:28 by miwehbe           #+#    #+#             */
/*   Updated: 2025/09/11 20:45:28 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int	count_available_vars(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		if (env->avail)
			count++;
		env = env->next;
	}
	return (count);
}

static char	*create_env_string(t_env *node)
{
	char	*str;
	int		total_len;

	if (!node->val)
		return (NULL);
	total_len = ft_strlen(node->name) + ft_strlen(node->val) + 2;
	str = malloc(total_len);
	if (!str)
		return (NULL);
	ft_strcpy(str, node->name);
	ft_strcat(str, "=");
	ft_strcat(str, node->val);
	return (str);
}

static int	fill_envp_array(char **envp, t_env *env)
{
	t_env	*current;
	int		i;

	current = env;
	i = 0;
	while (current)
	{
		if (current->avail && current->val)
		{
			envp[i] = create_env_string(current);
			if (!envp[i])
			{
				free_envp_partial(envp, i);
				return (-1);
			}
			i++;
		}
		current = current->next;
	}
	envp[i] = NULL;
	return (0);
}

char	**env_to_envp(t_env *env)
{
	char	**envp;
	int		count;

	count = count_available_vars(env);
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	if (fill_envp_array(envp, env) == -1)
	{
		free(envp);
		return (NULL);
	}
	return (envp);
}
