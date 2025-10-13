/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:10:26 by nour              #+#    #+#             */
/*   Updated: 2025/10/13 11:15:46 by nour             ###   ########.fr       */
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

void	add_redir(t_cmd *cmds, t_redir *c)
{
	t_redir	*r;

	if (!cmds)
		return ;
	if (!cmds->rd)
		cmds->rd = c;
	else
	{
		r = cmds->rd;
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
	return (r);
}

// void	fill_r(t_token *t, t_cmd *cmd)
// {
// 	t_redir *r;
// 	t_token *current;
// 	char	*a;
// 	char	*b;

// 	r = init_redir();
// 	if (t->type == IN)
// 		r->type = R_IN;
// 	else if (t->type == OUT)
// 		r->type = R_OUT;
// 	else if (t->type == APPEND)
// 		r->type = R_APPEND;
// 	else if (t->type == HEREDOC)
// 		r->type = R_HEREDOC;
// 	// if (t->next && t->next->s)
// 	// 	r->s = ft_strdup(t->next->s);
// 	// else
// 	// 	r->s = NULL;
// 	if (t->next && (t->next->type == WORD || t->next->type == EMPTY))
// 	{
// 		current = t->next;
// 		if (current->quotes == 1)
// 			r->s = ft_strtrim(current->s, "'");
// 		else if (current->quotes == 2)
// 			r->s = ft_strtrim(current->s, "\"");
// 		else
// 			r->s = ft_strdup(current->s);
// 		while (current->space == 0 && current->type == WORD && current->next && current->next->type == WORD)
// 		{
// 			current = current->next;
// 			if (current->quotes == 1)
// 				a = ft_strtrim(current->s, "'");
// 			else if (current->quotes == 2)
// 				a = ft_strtrim(current->s, "\"");
// 			else
// 				a = ft_strdup(current->s);
// 			b = r->s;
// 			r->s = ft_strjoin(b, a);
// 			free(a);
// 			free(b);
// 		}
// 	}
// 	else
// 		r->s = NULL;
// 	add_redir(cmd, r);
// }

t_redir	*init_for_r(t_redir *r, t_token *t)
{
	r = init_redir();
	if (t->type == IN)
		r->type = R_IN;
	else if (t->type == OUT)
		r->type = R_OUT;
	else if (t->type == APPEND)
		r->type = R_APPEND;
	else if (t->type == HEREDOC)
		r->type = R_HEREDOC;
	return (r);
}
void	fill_r(t_token *t, t_cmd *cmd)
{
	t_redir *r;
	t_token *current;
	char	*a;
	char	*b;

	r = NULL;
	r = init_for_r(r, t);
	if (!t->next || (t->next->type != WORD && t->next->type != EMPTY))
	{
		r->s = NULL;
		add_redir(cmd, r);
		return;
	}
	current = t->next;
	if (current->type == EMPTY)
		r->s = ft_strdup("");
	else if (current->quotes == 1)
		r->s = ft_strtrim(current->s, "'");
	else if (current->quotes == 2)
		r->s = ft_strtrim(current->s, "\"");
	else
		r->s = ft_strdup(current->s);
	while (current && current->space == 0 && current->next && 
	       (current->next->type == WORD || current->next->type == EMPTY))
	{
		current = current->next;
		if (!current)
			break;
		if (current->type == EMPTY)
			a = ft_strdup("");
		else if (current->quotes == 1)
			a = ft_strtrim(current->s, "'");
		else if (current->quotes == 2)
			a = ft_strtrim(current->s, "\"");
		else
			a = ft_strdup(current->s);
		b = r->s;
		r->s = ft_strjoin(b, a);
		free(a);
		free(b);
	}
	add_redir(cmd, r);
}
