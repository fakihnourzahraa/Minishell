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

#ifndef BUILT_H
#define BUILT_H
#include "../minishell.h"
#include "../libft/libft.h"

void builtin_echo(t_cmd *cmd,t_shell *shell);
void	builtin_pwd(t_cmd *cmd, t_shell *shell);
void builtin_exit(t_cmd *cmd, t_shell *shell);

#endif