/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 19:01:33 by miwehbe           #+#    #+#             */
/*   Updated: 2025/09/20 19:01:33 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
#define EXPANSION_H
#include "../minishell.h"
#include "../libft/libft.h"
#include "../env/env.h"

char *get_exit_status_string(t_shell *shell);
char *expand_variable(t_shell *shell, const char *var_name);
//void update_exit_status(t_shell *shell, int status);

#endif