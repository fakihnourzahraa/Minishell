/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:14:58 by miwehbe           #+#    #+#             */
/*   Updated: 2025/10/18 15:36:56 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	open_infile(char *filename)
{
	int	fd;

	if (!filename)
		return (-1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		perror("minishell");
	return (fd);
}

int	open_outfile(char *filename, int append)
{
	int	fd;

	if (!filename)
		return (-1);
	if (append)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		perror("minishell");
	return (fd);
}

int	redirect_fd(int fd, int target_fd)
{
	if (fd == -1)
		return (-1);
	if (dup2(fd, target_fd) == -1)
	{
		perror("minishell");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
