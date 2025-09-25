/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:35:17 by nfakih            #+#    #+#             */
/*   Updated: 2025/09/25 22:16:13 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

int	is_r(t_token *a)
{
	if (a->type == IN || a->type == OUT || a->type == APPEND || a->type == HEREDOC)
		return (1);
	return (0);
}

int	check_tkns(t_token *tkn)
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
