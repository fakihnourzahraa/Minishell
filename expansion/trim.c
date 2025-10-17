/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:38:06 by nour              #+#    #+#             */
/*   Updated: 2025/10/17 15:59:43 by nour             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

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
			result[j++] = new[i++];
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

	i = 0;
	j = 0;
	b = ft_calloc(sizeof(char), ft_strlen(a) + 1);
	while (a[i])
	{
		if (a[i] == '\'' || a[i] == '"')
			quoted(a, b, &i, &j);
		else
			unquoted(a, b, &i, &j);
	}
	b[j] = '\0';
	free(a);
	return (b);
}
