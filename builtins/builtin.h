/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:27:32 by miwehbe           #+#    #+#             */
/*   Updated: 2025/08/29 14:27:32 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../minishell.h"
# include "../libft/libft.h"
# include "../env/env.h"
# include "../exec/exec.h"

void	builtin_echo(t_cmd *cmd, t_shell *shell);
void	builtin_pwd(t_cmd *cmd, t_shell *shell);
void	builtin_exit(t_cmd *cmd, t_shell *shell);
void	builtin_cd(t_cmd *cmd, t_shell *shell);
void	builtin_env(t_cmd *cmd, t_shell *shell);
void	builtin_export(t_cmd *cmd, t_shell *shell);
void	builtin_unset(t_cmd *cmd, t_shell *shell);

void	sort_exported_vars(t_env **arr, int count);
int		collect_exported_vars(t_shell *shell, t_env **arr);
int		is_valid_identifier(const char *str);
void	swap_env(t_env **a, t_env **b);
void	update_shlvl_on_start(t_shell *shell);
void	update_shlvl_on_exit(t_shell *shell);
int		unset_env_var(t_env **env, const char *name);

#endif
