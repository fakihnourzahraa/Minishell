/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 23:38:42 by miwehbe           #+#    #+#             */
/*   Updated: 2025/10/20 23:38:42 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	handle_redir_out(t_redir *redir, int output_fd)
{
	int	temp_fd;
	int	new_fd;

	temp_fd = output_fd;
	new_fd = open(redir->s, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (new_fd < 0)
	{
		perror(redir->s);
		exit(1);
	}
	if (temp_fd != STDOUT_FILENO && temp_fd > 2)
		close(temp_fd);
	return (new_fd);
}

static int	handle_redir_append(t_redir *redir, int output_fd)
{
	int	temp_fd;
	int	new_fd;

	temp_fd = output_fd;
	new_fd = open(redir->s, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (new_fd < 0)
	{
		perror(redir->s);
		exit(1);
	}
	if (temp_fd != STDOUT_FILENO && temp_fd > 2)
		close(temp_fd);
	return (new_fd);
}

int	handle_output_redirections(t_cmd *cmd)
{
	t_redir	*redir;
	int		output_fd;

	output_fd = STDOUT_FILENO;
	redir = cmd->rd;
	while (redir)
	{
		if (redir->type == R_OUT)
			output_fd = handle_redir_out(redir, output_fd);
		else if (redir->type == R_APPEND)
			output_fd = handle_redir_append(redir, output_fd);
		redir = redir->next;
	}
	return (output_fd);
}
