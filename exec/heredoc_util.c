/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 09:38:17 by miwehbe           #+#    #+#             */
/*   Updated: 2025/10/18 09:38:17 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	check_delimiter(char *line, char **delims, int idx, int count)
{
	if (ft_strcmp(line, delims[idx]) == 0)
	{
		idx++;
		if (idx >= count)
			return (-1);
		return (idx);
	}
	return (idx);
}

static void	write_expanded_line(int write_fd, char *line, t_shell *shell)
{
	char	*b;
	char	*expanded;

	b = ft_strdup(line);
	expanded = expand(shell, b, true);
	write(write_fd, expanded, ft_strlen(expanded));
	write(write_fd, "\n", 1);
	free(expanded);
}

static int	handle_eof(char **delims, int idx, int count)
{
	ft_putstr_fd("bash: warning: here-document at line 1 delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delims[idx], 2);
	ft_putstr_fd("')\n", 2);
	idx++;
	if (idx >= count)
	{
		g_signal = -1;
		return (-1);
	}
	return (idx);
}

static void	handle_delimiter_match(char *line, int write_fd, t_shell *shell)
{
	free(line);
	cleanup_child_process(shell);
	close(write_fd);
	exit(0);
}

void	heredoc_child(int write_fd, char **delims, int count, t_shell *shell)
{
	char	*line;
	int		idx;
	int		new_idx;

	idx = 0;
	signals_child_heredoc();
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			new_idx = handle_eof(delims, idx, count);
			if (new_idx == -1)
			{
				close(write_fd);
				exit(0);
			}
			idx = new_idx;
			continue;
		}
		new_idx = check_delimiter(line, delims, idx, count);
		if (new_idx == -1)
			handle_delimiter_match(line, write_fd, shell);
		if (new_idx == idx && idx == count - 1)
			write_expanded_line(write_fd, line, shell);
		idx = new_idx;
		free(line);
	}
}
