/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 13:41:44 by nfakih            #+#    #+#             */
/*   Updated: 2025/09/02 20:28:17 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing.h"
typedef	enum	s_token_type
{
	WORD,
	PIPE,
	IN,
	OUT,
	APPEND,
	HEREDOC,
	T_EOF
}				t_token_type;

int	split_word(char *a, int i, t_shell *shell, bool q_t)
{
	char	*b;
	int		j;
	
	j = 0;
	skip_spaces(a, i);
	b = malloc(sizeof(char) * (word_len(a, i) + 1));
	while (!skipable_space(a[i]))
	{
		b[j] = a[i];
		i++;
		j++;
	}
	shell->tkns->s = b;
	shell->tkns->quotes = q_t;
	shell->tkns->type = 0;
	return (i);
}
