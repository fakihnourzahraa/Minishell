/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:10:17 by nour              #+#    #+#             */
/*   Updated: 2025/09/04 13:36:41 by nour             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# include "../minishell.h"

int	skip_spaces(char *a, int i);
int	skipable_space(char a);
int	split_word(char *a, int i, t_token * t);
int	split_q(char *a, t_shell *shell, int i);

#endif

//nour work on it week 1 
//nour should define struct:t_token, t_cmd, t_redir, t_env, t_shell.