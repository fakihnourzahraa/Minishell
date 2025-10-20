/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 23:35:55 by miwehbe           #+#    #+#             */
/*   Updated: 2025/10/20 23:35:55 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	handle_file_error(char *filename)
{
	perror(filename);
	exit(1);
}

static int	handle_redir_in(t_redir *redir, int input_fd)
{
	int	temp_fd;
	int	new_fd;

	temp_fd = input_fd;
	new_fd = open(redir->s, O_RDONLY);
	if (new_fd < 0)
		handle_file_error(redir->s);
	if (temp_fd != STDIN_FILENO && temp_fd > 2)
		close(temp_fd);
	return (new_fd);
}

static int	handle_redir_heredoc(t_redir *redir, int input_fd, t_shell *shell)
{
	int	temp_fd;
	int	new_fd;

	temp_fd = input_fd;
	new_fd = run_heredoc(redir->s, shell);
	if (new_fd < 0)
		exit(130);
	if (temp_fd != STDIN_FILENO && temp_fd > 2)
		close(temp_fd);
	return (new_fd);
}

int	handle_input_redirections(t_cmd *cmd, t_shell *shell)
{
	t_redir	*redir;
	int		input_fd;

	(void)shell;
	if (cmd->i_fd > 0)
		return (cmd->i_fd);
	input_fd = STDIN_FILENO;
	redir = cmd->rd;
	while (redir)
	{
		if (redir->type == R_IN)
			input_fd = handle_redir_in(redir, input_fd);
		else if (redir->type == R_HEREDOC)
			input_fd = handle_redir_heredoc(redir, input_fd, shell);
		redir = redir->next;
	}
	return (input_fd);
}
