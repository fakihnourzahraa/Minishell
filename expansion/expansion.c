/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 20:08:42 by nfakih            #+#    #+#             */
/*   Updated: 2025/10/10 16:07:15 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

int	var_length(char	*a, int i)
{
	int	j;
	
	j = i;
	if (a[i] && a[i] == '?')
		return (1);
	while (a[i] && (ft_isalnum(a[i]) || a[i]== '_'))
			i++;
	if (i == j)
		return (-1);
	return (i - j);
}
// skips $ and calculates length of rest

int	expandable(char *s, int	i, char	*q)
{
	char	a;

	a = *q;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			if (a == '\0')
				a = s[i];
			else if (a == s[i])
				a = '\0';
		}
		if (s[i] == '$' && (a == '"'|| a == '\0'))
		{
			*q = a;
			return (i);
		}
		i++;
	}
	*q = a;
	return (-1);
}
char	*trim_expand(t_shell *shell, int i, int old_len, char *s)
{
	int		z;
	char	*var;
	char	*new;

	z = 0;
	var = malloc(sizeof(char) * (old_len + 1));
	while (z < old_len)
	{
		var[z] = s[i];
		i++;
		z++;
	}
	var[z] = '\0';
	new = expand_variable(shell, var);
	if (!new)
		new = ft_strdup("");
	free(var);
	return (new);
}
//malloc var name and expand it to new var
char	*trim_vars(char *s, int *i, int old_len, char *new_var)
{
	char	*before;
	char	*temp;
	char	*result;
	int		new_var_len;

	before = ft_substr(s, 0, *i);
	temp = ft_strjoin(before, new_var);
	free(before);
	result = ft_strjoin(temp, s + *i + old_len + 1);
	new_var_len = ft_strlen(new_var);
	*i = *i + new_var_len;
	free(temp);
	return (result);
}
char	*expand(t_shell *shell, char *s)
{
	int		i;
	char	q;
	char	*new_var;
	int		old_len;
	char	*result;
	char	*old_result;

	i = 0;
	q = '\0';
	result = s;
	i = expandable(s, i, &q);
	if (i == -1)
		return (s);
	while (i != -1)
	{
		old_len = var_length(result, i + 1);
		if (old_len == -1)
			i = expandable(s, i + 1, &q);
		else
		{
			new_var = trim_expand(shell, i + 1, old_len, result);
			old_result = result;
			result = trim_vars(result, &i, old_len, new_var);
			// if (old_result != s)
				free(old_result);
			free(new_var);
			i = expandable(result, i, &q);
		}
	}
	return (result);
}

char	*trim_vars_fq(char *s, int i, int j)
{
	char	*before;
	char	*middle;
	char	*after;
	char	*temp;

	if (i == 0)
		before = ft_strdup("");
	else
		before = ft_substr(s, 0, i);
	middle = ft_substr(s, i + 1, j - i - 1);
	after = ft_substr(s, j + 1, ft_strlen(s) - j);
	temp = ft_strjoin(before, middle);
	free(before);
	free(middle);
	before = ft_strjoin(temp, after);
	free(temp);
	free(after);
	return (before);
}

char	*trim(char *a)
{
	int		i;
	int		j;
	char	*b;
	char	n;

	i = 0;
	n = '\0';
	b = ft_calloc(sizeof(char), ft_strlen(a));
	j = 0;
	while (i >= 0 && a[i])
	{
	//	printf("HUH");
	//	printf("j is %d\n", j);
		while (a[i] && n == '\0')
		{
			if (a[i] == '\'' || a[i] == '"')
				n = a[i];
			else
			{
				b[j] = a[i];
				i++;
				j++;
			}
			i++;
		}
		if (!a[i])
			return (free(b), a);
		while (n != '\0')
		{
			if (a[i] != n)
			{
				b[j] = a[i];
				j++;
			}
			else
				n = '\0';
			i++;
		}
	}
	free(a);
	return (b);
}
// char	*trim(char *a)
// {
// 	int		i;
// 	int		j;
// 	char	*r;
// 	char	*n;

// 	i = 0;
// 	while (a[i])
// 	{
// 		j = i + 1;
// 		if (a[i] == '\'' || a[i] == '"')
// 		{
// 			n = malloc(2);
// 			n[0] = a[i];
// 			n[1] = '\0';
// 			if (a[j] == a[i])
// 			{
// 				r = ft_strtrim(a, n);
// 				free(a);
// 				free(n);
// 				return r;
// 			}
// 			j++;
// 			free(n);
// 		}
// 		i++;
// 	}
// 	return (a);
// }
void	remove_quotes(t_cmd *current)
{
	int		i;
	t_redir *redir;
	
	i = 0;
	if (current->cmd)
		current->cmd = trim(current->cmd);
	while (current->args && current->args[i])
	{
		current->args[i] = trim(current->args[i]);
		i++;
	}
	redir = current->rd;
	while (redir)
	{
		if (redir->s)
			redir->s = trim(redir->s);
		redir = redir->next;
	}
}
void	iterate_expansion(t_shell *shell)
{
	int		i;
	t_cmd	*current;
	t_redir	*redir;

	current = shell->cmds;
	while (current)
	{
		i = 0;
		if (current->cmd)
			current->cmd = expand(shell, current->cmd);
		while (current->args && current->args[i])
		{
			current->args[i] = expand(shell, current->args[i]);
			i++;
		}
		redir = current->rd;
		while (redir)
		{
			if (redir->s)
				redir->s = expand(shell, redir->s);
			redir = redir->next;
		}
			remove_quotes(current);
		current = current->next;
	}
}
