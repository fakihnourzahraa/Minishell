/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 19:01:33 by miwehbe           #+#    #+#             */
/*   Updated: 2025/10/04 22:15:42 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
#define EXPANSION_H
#include "../minishell.h"
#include "../libft/libft.h"
#include "../env/env.h"

char *get_exit_status_string(t_shell *shell);
char *expand_variable(t_shell *shell, const char *var_name);
void	iterate_expansion(t_shell *shell);
//void update_exit_status(t_shell *shell, int status);

#endif