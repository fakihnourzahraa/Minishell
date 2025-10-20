/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multcmnd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 22:24:44 by miwehbe           #+#    #+#             */
/*   Updated: 2025/10/19 22:24:44 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	process_heredoc_redir(t_redir *redir, char **heredoc_delimiters,
		int *heredoc_count)
{
	if (redir->type != R_HEREDOC)
		return (0);
	if (!redir->s || ft_strlen(redir->s) == 0)
		return (-1);
	heredoc_delimiters[*heredoc_count] = redir->s;
	(*heredoc_count)++;
	return (0);
}

static int	collect_cmd_heredoc_delimiters(t_cmd *current, 
		char **heredoc_delimiters)
{
	int		heredoc_count;
	t_redir	*redir;

	heredoc_count = 0;
	if (!current->rd)
		return (0);
	redir = current->rd;
	while (redir && heredoc_count < 100)
	{
		if (process_heredoc_redir(redir, heredoc_delimiters,
				&heredoc_count) == -1)
			return (-1);
		redir = redir->next;
	}
	return (heredoc_count);
}

static int	process_cmd_heredocs(t_cmd *current, t_shell *shell)
{
	char	*heredoc_delimiters[100];
	int		heredoc_count;
	int		heredoc_fd;

	heredoc_count = collect_cmd_heredoc_delimiters(current,
			heredoc_delimiters);
	if (heredoc_count == -1)
		return (-1);
	if (heredoc_count > 0)
	{
		heredoc_fd = run_multiple_heredocs(heredoc_delimiters,
				heredoc_count, shell);
		if (heredoc_fd == -1)
			return (-1);
		current->i_fd = heredoc_fd;
	}
	return (0);
}

static int	process_all_heredocs(t_shell *shell, t_cmd *cmds)
{
	t_cmd	*current;

	current = cmds;
	while (current)
	{
		if (process_cmd_heredocs(current, shell) == -1)
			return (1);
		current = current->next;
	}
	return (0);
}

int	execute_multiple_cmds(t_shell *shell, t_cmd *cmds, int cmd_count)
{
	t_pipe_info	info;

	if (process_all_heredocs(shell, cmds))
		return (1);
	info.pipes = setup_pipes(cmd_count);
	if (!info.pipes)
		return (1);
	info.cmd_count = cmd_count;
	signals_parent();
	if (execute_all_commands(shell, cmds, &info) == -1)
	{
		close_and_free_pipes(info.pipes, cmd_count - 1);
		info.pipes = NULL;
		signals_prompt();
		return (1);
	}
	cleanup_and_wait(shell, cmds, &info);
	return (shell->exit_status);
}
