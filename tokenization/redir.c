/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 11:24:09 by nfakih            #+#    #+#             */
/*   Updated: 2025/10/24 13:36:33 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

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
	r->quotes = false;
	return (r);
}

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
	r->quotes = false;
	return (r);
}

void	help(t_token **current, char **a, char **b, t_redir **r)
{
	while ((*current) && (*current)->space == 0 && (*current)->next
		&& ((*current)->next->type == WORD || (*current)->next->type == EMPTY))
	{
		(*current) = (*current)->next;
		if (!(*current))
			break ;
		if ((*current)->type == EMPTY)
			*a = ft_strdup("");
		else if ((*current)->quotes == 1 || (*current)->quotes == 2)
		{
			*a = ft_strdup((*current)->s);
			(*r)->quotes = true;
		}
		else
			*a = ft_strdup((*current)->s);
		*b = (*r)->s;
		(*r)->s = ft_strjoin(*b, *a);
		free(*a);
		free(*b);
	}
}

void	fill_r(t_token *t, t_cmd *cmd)
{
	t_redir	*r;
	t_token	*current;
	char	*a;
	char	*b;

	r = NULL;
	r = init_for_r(r, t);
	if (!t->next || (t->next->type != WORD && t->next->type != EMPTY))
	{
		r->s = NULL;
		add_redir(cmd, r);
		return ;
	}
	current = t->next;
	if (current->type == EMPTY)
		r->s = ft_strdup("");
	else if (current->quotes == 1 || current->quotes == 2)
	{
		r->s = ft_strdup(current->s);
		r->quotes = true;
	}
	else
		r->s = ft_strdup(current->s);
	help(&current, &a, &b, &r);
	add_redir(cmd, r);
}
