/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:10:17 by nour              #+#    #+#             */
/*   Updated: 2025/09/04 16:11:31 by nour             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# include "../minishell.h"

int	    skip_spaces(char *a, int i);
bool	skipable_space(char a);
int	    split_word(char *a, int i, t_shell *shell, bool in_q);
int	    split_q(char *a, t_shell *shell, int i);

#endif
