/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:10:26 by nour              #+#    #+#             */
/*   Updated: 2025/09/15 19:40:12 by nour             ###   ########.fr       */
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

void	add_redir(t_shell *shell, t_redir *c)
{
	t_redir	*r;

	if (!shell->cmds)
		return ;
	if (!shell->cmds->rd)
		shell->cmds->rd = c;
	else
	{
		r = shell->cmds->rd;
		while (r->next)
			r = r->next;
		r->next = c;
	}
}
t_redir	*init_redir(void)
{
	t_redir	*r;
	
	r = malloc(sizeof(t_redir));
	r->fd = -1;
	r->s = NULL;
	r->type = R_EMPTY;
	r->next = NULL;
}

void	fill_r(t_token *t, t_shell *shell)
{
	t_redir *r;

	if (t->type == T_EOF)
		return ;
	r = init_redir();
	if (t->type == IN)
		r->type = R_IN;
	else if (t->type == OUT)
		r->type = R_OUT;
	else if (t->type == APPEND)
		r->type = R_APPEND;
	else if (t->type == HEREDOC)
		r->type = R_HEREDOC;
	else
		return ;
	if (t->next && t->next->s)
		r->s = ft_strdup(t->next->s);
	else
		r->s = NULL;
	add_redir(shell, r);
}