/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:32:56 by miwehbe           #+#    #+#             */
/*   Updated: 2025/09/03 14:32:56 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/*static int	handle_in_redir(t_shell *shell, t_redir *redir)
{
	int	fd;

	(void)shell;
	fd = open_infile(redir->s);
	if (fd == -1)
		return (-1);
	redirect_fd(fd, STDIN_FILENO);
	return (0);
}

static int	handle_out_redir(t_redir *redir)
{
	int	fd;

	fd = open_outfile(redir->s, 0);
	if (fd == -1)
		return (-1);
	redirect_fd(fd, STDOUT_FILENO);
	return (0);
}

static int	handle_append_redir(t_redir *redir)
{
	int	fd;

	fd = open_outfile(redir->s, 1);
	if (fd == -1)
		return (-1);
	redirect_fd(fd, STDOUT_FILENO);
	return (0);
}

static int	handle_heredoc_redir(t_redir *redir, t_shell *shell)
{
	int	fd;

	fd = run_heredoc(redir->s, shell);
	if (fd == -1)
		return (-1);
	redirect_fd(fd, STDIN_FILENO);
	return (0);
}

int	apply_redirections(t_cmd *cmd, t_shell *shell)
{
	t_redir	*current;

	if (!cmd || !cmd->rd)
		return (0);
	current = cmd->rd;
	while (current)
	{
		if (current->type == R_IN && handle_in_redir(shell, current) == -1)
			return (-1);
		else if (current->type == R_OUT && handle_out_redir(current) == -1)
			return (-1);
		else if (current->type == R_APPEND && handle_append_redir(current) == -1)
			return (-1);
		else if (current->type == R_HEREDOC && handle_heredoc_redir(current, shell) == -1)
			return (-1);
		current = current->next;
	}
	return (0);
}
*/

static int	handle_in_redir(t_shell *shell, t_redir *redir)
{
	int	fd;

	(void)shell;
	fd = open_infile(redir->s);
	if (fd == -1)
		return (-1);
	redirect_fd(fd, STDIN_FILENO);
	return (0);
}

static int	handle_out_redir(t_redir *redir)
{
	int	fd;

	fd = open_outfile(redir->s, 0);
	if (fd == -1)
		return (-1);
	redirect_fd(fd, STDOUT_FILENO);
	return (0);
}

static int	handle_append_redir(t_redir *redir)
{
	int	fd;

	fd = open_outfile(redir->s, 1);
	if (fd == -1)
		return (-1);
	redirect_fd(fd, STDOUT_FILENO);
	return (0);
}

static int	handle_heredoc_redir(t_redir *redir, t_shell *shell)
{
	int	fd;

	fd = run_heredoc(redir->s, shell);
	if (fd == -1)
		return (-1);
	redirect_fd(fd, STDIN_FILENO);
	return (0);
}

int	apply_redirections(t_cmd *cmd, t_shell *shell)
{
	t_redir	*current;
	if (!cmd || !cmd->rd)
		return (0);
	current = cmd->rd;
	while (current)
	{
		if (current->type == R_IN && handle_in_redir(shell, current) == -1)
			return (-1);
		else if (current->type == R_OUT && handle_out_redir(current) == -1)
			return (-1);
		else if (current->type == R_APPEND && handle_append_redir(current) == -1)
			return (-1);
		else if (current->type == R_HEREDOC && handle_heredoc_redir(current, shell) == -1)
			return (-1);
		current = current->next;
	}
	return (0);
}