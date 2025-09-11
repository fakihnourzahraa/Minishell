/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:10:26 by nour              #+#    #+#             */
/*   Updated: 2025/09/11 20:00:28 by nour             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

// typedef enum e_r_type
// {
//   R_IN,
//   R_OUT,
//   R_APPEND,
//   R_HEREDOC
// } t_r_type;
// typedef struct s_redir
// {
// 	t_r_type	type;
// 	char		*s;
// 	int			fd;
// 	t_redir		*next;
// }				t_redir;

void	fill_r(t_token *t, t_shell *shell)
{
	t_redir *r;

	if (t->type == T_EOF)
		return ;
	if (t->type == IN)
	{
		shell->cmds->rd
	}
}