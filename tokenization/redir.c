/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:10:26 by nour              #+#    #+#             */
/*   Updated: 2025/09/11 21:28:55 by nfakih           ###   ########.fr       */
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

void	add_token(t_shell *shell, t_redir *c)
{
	t_redir	*r;

	if (!shell->cmds->rd)
		shell->tkns = c;
	else
	{
		r = shell->cmds->rd;
		while (r->next)
			r = r->next;
		r->next = c;
	}
}

void	fill_r(t_token *t, t_shell *shell)
{
	t_redir *r;

	if (t->type == T_EOF)
		return ;
	if (t->type == IN)
		r->type = R_IN;
	if (t->type = OUT)
		r->type = R_OUT;
	if (t->type = APPEND)
		r->type = R_APPEND;
	if (t->type == HEREDOC)
		r->type = HEREDOC;
	r->s = ft_strdup(t->s);
	add_token(shell, r);
}