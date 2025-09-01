/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:10:17 by nour              #+#    #+#             */
/*   Updated: 2025/08/31 13:44:24 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSING_H
# define PARSING_H

# include "../minishell.h"

int	is_cmd(char	*a, int i);
int	is_op(char	*a, int i);
int	is_var(char	*a, int i);
int	skip_spaces(char *a, int i);
int	skipable_space(char a);

int	split_q(char *a, int i, t_token * t);
int	split_cmd(char *a, int i, t_token * t);
int	split_op(char *a, int i, t_token * t);
int	split_var(char *a, int i, t_token * t);
int	split_word(char *a, int i, t_token * t);
#endif

//nour work on it week 1 
//nour should define struct:t_token, t_cmd, t_redir, t_env, t_shell.