/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 18:57:15 by miwehbe           #+#    #+#             */
/*   Updated: 2025/10/24 12:26:37 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	*get_exit_status_string(t_shell *shell)
{
	int		status;
	char	*str_status;

	if (!shell)
		return (NULL);
	status = shell->exit_status;
	str_status = ft_itoa(status);
	if (!str_status)
		return (NULL);
	return (str_status);
}

char	*expand_variable(t_shell *shell, const char *var_name)
{
	char	*env_value;
	char	*str_copy;

	if (!shell || !var_name)
		return (NULL);
	if (ft_strcmp(var_name, "?") == 0)
		return (get_exit_status_string(shell));
	env_value = get_env_value(shell->env, var_name);
	if (!env_value)
		return (ft_strdup(""));
	str_copy = ft_strdup(env_value);
	return (str_copy);
}

char	set_a(char a, char s)
{
	if (a == '\0')
		return (s);
	else if (a == s)
		return ('\0');
	return (a);
}

// skips $ and calculates length of rest
void	handle_expansion(t_shell *shell, t_expand_data *data)
{
	char	*before;

	if (data->old_len == -2)
	{
		data->new_var = ft_strdup("");
		before = ft_substr(data->result, 0, data->i);
		data->result = ft_strjoin(before, data->result + data->i + 3);
		free(before);
	}
	else
	{
		data->new_var = trim_expand(shell, data->i + 1,
				data->old_len, data->result);
		data->result = trim_vars(data->result, &data->i,
				data->old_len, data->new_var);
	}
}

void	write_expanded_line(int write_fd, char *line, t_shell *shell)
{
	char	*b;
	char	*expanded;

	b = ft_strdup(line);
	expanded = expand(shell, b, true);
	write(write_fd, expanded, ft_strlen(expanded));
	write(write_fd, "\n", 1);
	free(expanded);
}
