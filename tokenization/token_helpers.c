/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 13:23:45 by nfakih            #+#    #+#             */
/*   Updated: 2025/09/25 00:32:38 by nour             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "tokenization.h"

int		skipforvar(char *a, int i)
{ 
	while (a[i] && (ft_isalnum(a[i]) || skipable_space(a[i])))
	{
		i++;
	}
	return (i);
}
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
	int		j;
	char	b;

	j = 0;
	b = '\0';
	while (a[i] && ((!skipable_space(a[i])) || b != '\0') && 
		   a[i] != '|' && a[i] != '<' && a[i] != '>')
	{
		if (a[i] == '\'' || a[i] == '"')
		{
			if (b == '\0')
				b = a[i];
			else if (b == a[i])
				b = '\0';
		}
		// if (a[i] == '$')
		// {
		// 	i += env_length(a, i);
		// 	j += env_length(a, i);
		// }
		// else
		// {
			i++;
			j++;
		// }
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
int	split_word(char *a, int i, t_shell *shell, t_token *n)
{
	char	*b;
	int		j;
	t_token	*t;
	int		len;
	
	j = 0;
	if (a[i] && a[i] == '\0')
		return (i);
	t = n;
	i = skip_spaces(a, i);
	len = word_len(a, i);
	printf("word len is %d", len);
	if (len == 0)
		return (i);
	b = malloc(sizeof(char) * (len + 1));
	while (len > j)
	{
		// if (a[i + j] == '$')
		// {
		// 	j = concat(a, b, j, i);
		// 	i = var_length(a, i + j);
		// }
		// else
			b[j] = a[i + j];
		j++;
	}
	if (a[i + j] && a[i + j] != 32)
		t->space = 0;
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
	int		len;
	t_token	*t;

	i++;
	len = 0;
	while (a[i + len] && a[i + len] != n)
	{
		// if (n == '"' && a[i + len] == '$')
		// 	len = env_length(a, i + len);
		// else
			len++;
	}
	b = malloc(sizeof(char) * (len + 3));
	b[0] = n;
	j = -1;
	while (++j < len)
	{
		// if (a[i + j] == '$')
		// {
		// 	j = concat(a, b, j, i);
		// 	i = var_length(a, i + j);
		// }
		// else
			b[j + 1] = a[i + j];
	}
	t = init_token();
	if (a[j + 1 + i] && !skipable_space(a[j + 1 + i]))
		t->space = false;
	b[len + 1] = n;
	b[len + 2] = '\0';
	t->s = b;
	t->type = WORD;
	t->quotes = (n == '\'') ? 1 : 2;
	add_token(shell, t);
	return (i + len + 1);
}
