/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 13:23:45 by nfakih            #+#    #+#             */
/*   Updated: 2025/09/12 15:21:03 by nour             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "tokenization.h"

bool	skipable_space(char a)
{
	if (a == 32 || a == 9 || a == 11 || a == 12)
		return (true);
	return (false);
}
// void	cleanup_token(t_shell *shell)
// {
// 	if (shell->tkns)
// 		free_tokens(shell->tkns);
// }
int	skip_spaces(char *a, int i)
{
	while (i > -1 && a[i] && skipable_space(a[i]))
		i++;
	return (i);
}
// only the skipable ones
// Space (32) and Tab (9) are your main token separators
// Newline (10) typically ends a command line
// Carriage Return (13) might appear in files created on Windows systems

int	word_len(char *a, int i)
{
	int	j;

	j = 0;
	while (a[i] && !skipable_space(a[i]) && 
		   a[i] != '|' && a[i] != '<' && a[i] != '>' && 
		   a[i] != '\'' && a[i] != '"')
	{
		i++;
		j++;
	}
	return (j);
}
// int	split_quote(char *a, int i, t_shell *shell, char n)
// {
// 	char	*b;
// 	int		j;
// 	int		z;
// 	t_token	*t;
	
// 	z = 0;
// 	i++;
// 	while (a[z + i] != n)
// 		z++;
// 	//these are the chars between each quotation mark
// 	b = malloc(sizeof(char) * (z + 2));
// 	j = 1;
// 	b[0] = n;
// 	while ((a[i + j]) != n)
// 	{
// 		b[j] = a[i + j];
// 		j++;
// 	}
// 	b[z] = n;
// 	b[z + 1] = '\0';
// 	t = init_token();
// 	t->s = b;
// 	t->type = WORD;
// 	t->quotes = n % 3 + 1;
// 	add_token(shell, t);
// 	return (z + i);
// }
//takes pos of first " returns pos of last "
// i++ cause i is gonna be " at first
//
int	split_word(char *a, int i, t_shell *shell)
{
	char	*b;
	int		j;
	t_token	*t;
	int		len;
	
	j = 0;
	if (a[i] && a[i] == '\0')
		return (i);
	t = init_token();
	i = skip_spaces(a, i);
	len = word_len(a, i);
	if (len == 0)
		return (i);
	b = malloc(sizeof(char) * (len + 1));
	while (len > j)
	{
		b[j] = a[i + j];
		j++;
	}
	b[j] = '\0';
	t->s = b;
	t->type = 0;
	add_token(shell, t);
	return (i + j);
}

int	split_quote(char *a, int i, t_shell *shell, char n)
{
	char	*b;
	int		j;
	int		start;
	int		len;
	t_token	*t;
	
	start = i;
	i++;
	len = 0;
	while (a[i + len] && a[i + len] != n)
		len++;	
	b = malloc(sizeof(char) * (len + 3));
	b[0] = n;
	j = 0;
	while (j < len)
	{
		b[j + 1] = a[i + j];
		j++;
	}
	b[len + 1] = n;
	b[len + 2] = '\0';
	t = init_token();
	t->s = b;
	t->type = WORD;
	if (n == '\'')
		t->quotes = 1;
	else
		t->quotes = 2;
	//t->quotes = (n == '\'') ? 1 : 2;  // 1 for single, 2 for double
	add_token(shell, t);
	
	// Return position after closing quote
	return (i + len + 1);
}