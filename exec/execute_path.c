/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 09:31:56 by miwehbe           #+#    #+#             */
/*   Updated: 2025/10/18 15:19:02 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*get_path_from_env(t_shell *shell)
{
	char	*path_value;

	if (!shell || !shell->env)
		return (NULL);
	path_value = get_env_value(shell->env, "PATH");
	if (!path_value)
		return (NULL);
	return (ft_strdup(path_value));
}

static char	*join_path_cmd(const char *path, const char *cmd)
{
	char	*tmp;
	char	*full;

	if (!path || !cmd)
		return (NULL);
	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full);
}

static char	*check_cmd_with_slash(const char *cmd)
{
	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	return (NULL);
}
// we check if it has / than it maybe the full path

static char	*search_in_paths(char **paths, const char *cmd)
{
	char	*full;
	int		i;

	if (!paths || !cmd)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full = join_path_cmd(paths[i], cmd);
		if (!full)
			return (NULL);
		if (access(full, X_OK) == 0)
			return (full);
		free(full);
		i++;
	}
	return (NULL);
}
// check for all executable paths

char	*get_cmd_path(const char *cmd, t_shell *shell)
{
	char	*path_env;
	char	**paths;
	char	*res;

	if (!cmd || !shell)
		return (NULL);
	res = check_cmd_with_slash(cmd);
	if (res)
		return (res);
	path_env = get_path_from_env(shell);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	free(path_env);
	if (!paths)
		return (NULL);
	res = search_in_paths(paths, cmd);
	free_paths(paths);
	return (res);
}
