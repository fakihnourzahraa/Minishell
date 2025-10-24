/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 09:38:17 by miwehbe           #+#    #+#             */
/*   Updated: 2025/10/24 12:33:30 by nfakih           ###   ########.fr       */
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

static int	process_line_or_eof(char *line, char **delims, int idx, int count)
{
	int	new_idx;

	if (!line)
	{
		ft_putstr_fd("minishell: warning: here-document", 2);
		ft_putstr_fd(" at line 1 delimited by end-of-file (wanted `", 2);
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
	new_idx = check_delimiter(line, delims, idx, count);
	return (new_idx);
}

static void	handle_valid_line(char *line, int write_fd,
		t_heredoc_data *data, t_shell *shell)
{
	int	new_idx;

	new_idx = process_line_or_eof(line, data->delims, *(data->idx),
			data->count);
	if (new_idx == -1)
	{
		free(line);
		cleanup_child_process(shell);
		close(write_fd);
		exit(0);
	}
	if (new_idx == *(data->idx) && *(data->idx) == data->count - 1)
	{
		if (shell->quotes && !shell->quotes[*data->idx])
			write_expanded_line(write_fd, line, shell);
		else
		{
			write(write_fd, line, ft_strlen(line));
			write(write_fd, "\n", 1);
		}
	}
	*(data->idx) = new_idx;
}

static void	process_heredoc_line(char *line, int write_fd,
		t_heredoc_data *data, t_shell *shell)
{
	int	new_idx;

	new_idx = process_line_or_eof(line, data->delims, *(data->idx),
			data->count);
	if (new_idx == -1 && !line)
	{
		close(write_fd);
		exit(0);
	}
	if (!line)
	{
		*(data->idx) = new_idx;
		return ;
	}
	handle_valid_line(line, write_fd, data, shell);
	free(line);
}

void	heredoc_child(int write_fd, char **delims, int count, t_shell *shell)
{
	char			*line;
	int				idx;
	t_heredoc_data	data;

	idx = 0;
	data.delims = delims;
	data.count = count;
	data.idx = &idx;
	signals_child_heredoc();
	while (1)
	{
		line = readline("> ");
		process_heredoc_line(line, write_fd, &data, shell);
	}
}

/*void	heredoc_child(int write_fd, char **delims, int count, t_shell *shell)
{
	char	*line;
	int		idx;
	int		new_idx;
	t_heredoc_data	data;

	idx = 0;
	data.delims = delims;
	data.count = count;
	data.idx = &idx;
	signals_child_heredoc();
	while (1)
	{
		line = readline("> ");
		new_idx = process_line_or_eof(line, delims, idx, count);
		if (new_idx == -1 && !line)
		{
			close(write_fd);
			exit(0);
		}
		if (!line)
		{
			idx = new_idx;
			continue;
		}
		handle_valid_line(line, write_fd, &data, shell);
		free(line);
	}
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
}*/