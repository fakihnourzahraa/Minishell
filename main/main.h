/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:36:07 by miwehbe           #+#    #+#             */
/*   Updated: 2025/08/29 13:33:43 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

extern int g_signal;
#include<stdio.h>
#include<stdlib.h>
#include<readline/readline.h>
#include<readline/history.h>
#include<signal.h>
# include "../minishell.h"
# include "../libft/libft.h"
#include "../builtins/builtin.h"
#include "../exec/exec.h"
void	sigint_handler(int signum);
void	signals_prompt(void);
void	signals_child_heredoc(void);
void	signals_child(void);
void	signals_parent(void);
void cleanup_shell(t_shell *shell);
void free_cmd_chain_complete(t_cmd *cmd);
#endif