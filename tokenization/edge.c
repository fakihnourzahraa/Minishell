/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:35:17 by nfakih            #+#    #+#             */
/*   Updated: 2025/10/13 10:59:31 by nour             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

int	is_r(t_token *a)
{
	if (a->type == IN || a->type == OUT || a->type == APPEND || a->type == HEREDOC)
		return (1);
	return (0);
}

/*int	check_tkns(t_token *tkn)
{
	// if (tkn->type != WORD || tkn->type != T_EOF)
	// 	return (-1);
	while (tkn)
	{
		if ((is_r(tkn) || tkn->type == PIPE) && tkn->next && (is_r(tkn->next) || tkn->next->type == PIPE))
			return (-1);
		if (tkn->next && tkn->next->type == T_EOF && (tkn->type == PIPE || is_r(tkn)))
			return (-1);
		tkn = tkn->next;
	}
	return (1);
}
*/

int	elses(t_token *tkn)
{
	if (tkn->type == PIPE)
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	else if (tkn->type == IN)
		ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 2);
	else if (tkn->type == OUT)
		ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
	else if (tkn->type == APPEND)
		ft_putstr_fd("minishell: syntax error near unexpected token `>>'\n", 2);
	else if (tkn->type == HEREDOC)
		ft_putstr_fd("minishell: syntax error near unexpected token `<<'\n", 2);
	else
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
	return (-1);
}

int	check_tkns(t_token *tkn)
{
	while (tkn)
	{
		if ((is_r(tkn) || tkn->type == PIPE) && tkn->next && (is_r(tkn->next) || tkn->next->type == PIPE))
		{
			if (tkn->next->type == PIPE)
				ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
			else if (tkn->next->type == IN)
				ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 2);
			else if (tkn->next->type == OUT)
				ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
			else if (tkn->next->type == APPEND)
				ft_putstr_fd("minishell: syntax error near unexpected token `>>'\n", 2);
			else if (tkn->next->type == HEREDOC)
				ft_putstr_fd("minishell: syntax error near unexpected token `<<'\n", 2);
			return (-1);
		}
		if (tkn->next && tkn->next->type == T_EOF && (tkn->type == PIPE || is_r(tkn)))
			return (elses(tkn));
		tkn = tkn->next;
	}
	return (1);
}
