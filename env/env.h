/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 20:38:17 by miwehbe           #+#    #+#             */
/*   Updated: 2025/09/11 20:38:17 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../minishell.h"
# include "../libft/libft.h"

t_env   *init_env_from_envp(char **envp);
t_env	*find_env_var(t_env *env, const char *name);
char	*get_env_value(t_env *env, const char *name);
int		set_env_var(t_env **env, const char *name,
				const char *value, bool available);
char	**env_to_envp(t_env *env);
void	free_env_list(t_env *env);
void	free_envp(char **envp);
void	free_envp_partial(char **envp, int count);
void	remove_head(t_env **env);
void	remove_next_node(t_env *current);

#endif
