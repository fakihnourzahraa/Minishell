/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:32:30 by miwehbe           #+#    #+#             */
/*   Updated: 2025/08/29 14:32:30 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
#define EXEC_H
#include "../minishell.h"
#include "../libft/libft.h"
#include "../builtins/builtin.h"

int is_builtin(char *cmd);
int	execute_builtin(t_cmd *cmd, t_shell *shell);
#endif