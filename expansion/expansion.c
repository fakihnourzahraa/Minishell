/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 20:08:42 by nfakih            #+#    #+#             */
/*   Updated: 2025/10/14 12:08:07 by nfakih           ###   ########.fr       */
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
//returns s[i] = $

char	*expand_and_trim(t_shell *shell, char *var)
{
	char	*new;
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = expand_variable(shell, var);
	result = malloc(sizeof(char) * ft_strlen(new) + 1);
	while (new[i])
	{
		if (!isspace(new[i]))
		{
			result[j] = new[i];
			j++;
			i++;
		}
		else
		{
			result[j] = new[i];
			j++;
			i++;
			while (isspace(new[i]))
				i++;
		}
	}
	result[j] = '\0';
	free(new);
	return (result);
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
	new = expand_and_trim(shell, var);
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
		{
			new_var = ft_strdup("");
			old_result = result;
			result = trim_vars(result, &i, 0, new_var);
			free(old_result);
			free(new_var);
			i = expandable(result, i, &q);
		}
		else
		{
			new_var = trim_expand(shell, i + 1, old_len, result);
			old_result = result;
			result = trim_vars(result, &i, old_len, new_var);
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
	b = ft_calloc(sizeof(char), ft_strlen(a) + 1);
	j = 0;
	while (i >= 0 && a[i])
	{
		while (a[i] && n == '\0')
		{
			if (a[i] == '\'' || a[i] == '"')
				n = a[i];
			else
			{
				b[j] = a[i];
				j++;
			}
			i++;
		}
	if (!a[i])
	{
		b[j] = '\0';
		free(a);
		return (b);
	}
		while (n != '\0' && a[i])
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
