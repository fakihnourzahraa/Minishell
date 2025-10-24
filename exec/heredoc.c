/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:33:35 by miwehbe           #+#    #+#             */
/*   Updated: 2025/10/24 13:32:11 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

extern int	g_signal;

int	run_heredoc(char *delimiter, t_shell *shell)
{
	char	*delims[2];

	delims[0] = delimiter;
	delims[1] = NULL;
	return (run_heredoc_internal(delims, 1, shell));
}

int	run_multiple_heredocs(char **delimiters, int count, t_shell *shell)
{
	return (run_heredoc_internal(delimiters, count, shell));
}

static int	collect_heredoc_delimiters(t_cmd *cmd, char **heredoc_delimiters,
	t_shell *shell)
{
	t_redir	*redir;
	int		heredoc_count;
	bool	*quotes;

	quotes = malloc(sizeof(bool) * 101);
	heredoc_count = 0;
	redir = cmd->rd;
	while (redir && heredoc_count < 100)
	{
		if (redir->type == R_HEREDOC)
		{
			if (!redir->s || ft_strlen(redir->s) == 0)
			{
				free(quotes);
				shell->quotes = NULL;
				return (-1);
			}
			heredoc_delimiters[heredoc_count] = redir->s;
			quotes[heredoc_count] = redir->quotes;
			heredoc_count++;
		}
		redir = redir->next;
	}
	shell->quotes = quotes;
	return (heredoc_count);
}

int	process_heredocs(t_cmd *cmd, t_shell *shell)
{
	char	*heredoc_delimiters[100];
	int		heredoc_count;
	int		heredoc_fd;

	heredoc_count = collect_heredoc_delimiters(cmd, heredoc_delimiters, shell);
	if (heredoc_count == -1)
		return (-1);
	if (heredoc_count > 0)
	{
		heredoc_fd = run_multiple_heredocs(heredoc_delimiters,
				heredoc_count, shell);
		if (heredoc_fd == -1)
		{
			free(shell->quotes);
			shell->quotes = NULL;
			return (-1);
		}
		cmd->i_fd = heredoc_fd;
	}
	free(shell->quotes);
	shell->quotes = NULL;
	return (0);
}
