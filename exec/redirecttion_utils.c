/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecttion_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 09:41:40 by miwehbe           #+#    #+#             */
/*   Updated: 2025/10/18 09:41:40 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	handle_in_redir(t_shell *shell, t_redir *redir)
{
	int	fd;

	(void)shell;
	if (!redir || !redir->s)
		return (-1);
	fd = open_infile(redir->s);
	return (redirect_fd(fd, STDIN_FILENO));
}

int	handle_out_redir(t_redir *redir)
{
	int	fd;

	if (!redir || !redir->s)
		return (-1);
	fd = open_outfile(redir->s, 0);
	return (redirect_fd(fd, STDOUT_FILENO));
}

int	handle_append_redir(t_redir *redir)
{
	int	fd;

	if (!redir || !redir->s)
		return (-1);
	fd = open_outfile(redir->s, 1);
	return (redirect_fd(fd, STDOUT_FILENO));
}

int	is_redirect_only_command(t_cmd *cmd)
{
	if (!cmd)
		return (0);
	if ((!cmd->cmd || ft_strlen(cmd->cmd) == 0) && cmd->rd)
		return (1);
	return (0);
}
