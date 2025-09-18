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

/*static int	handle_heredoc_redir(t_redir *redir, t_shell *shell)
{
	int	fd;

	fd = run_heredoc(redir->s, shell);
	if (fd == -1)
		return (-1);
	redirect_fd(fd, STDIN_FILENO);
	return (0);
}*/

/*int	apply_redirections(t_cmd *cmd, t_shell *shell)
{
	t_redir	*current;
	t_redir *heredoc_to_use;

	if (!cmd || !cmd->rd)
		return (0);
	heredoc_to_use = find_last_heredoc(cmd);
	current = cmd->rd;
	while (current)
	{
		if (current->type == R_IN && handle_in_redir(shell, current) == -1)
			return (-1);
		else if (current->type == R_OUT && handle_out_redir(current) == -1)
			return (-1);
		else if (current->type == R_APPEND && handle_append_redir(current) == -1)
			return (-1);
		else if (current->type == R_HEREDOC)
    {
      if (current == heredoc_to_use && handle_heredoc_redir(current, shell) == -1)
        return (-1);
    }
		current = current->next;
	}
	return (0);
}*/

int apply_redirections(t_cmd *cmd, t_shell *shell)
{
    t_redir *current;
    char *heredoc_delimiters[100];
    int heredoc_count = 0;
    int final_input_fd = STDIN_FILENO;
    
    if (!cmd || !cmd->rd)
      return (0);
    current = cmd->rd;
    while (current)
    {
      if (current->type == R_HEREDOC)
      {
        heredoc_delimiters[heredoc_count] = current->s;
        heredoc_count++;
      }
      current = current->next;
    }
    current = cmd->rd;
    while (current)
    {
      if (current->type == R_IN && handle_in_redir(shell, current) == -1)
        return (-1);
      else if (current->type == R_OUT && handle_out_redir(current) == -1)
        return (-1);
      else if (current->type == R_APPEND && handle_append_redir(current) == -1)
        return (-1);
      current = current->next;
    }

    if (heredoc_count > 0)
    {
        final_input_fd = run_multiple_heredocs(heredoc_delimiters, heredoc_count, shell);
        if (final_input_fd == -1)
            return (-1);
        if (dup2(final_input_fd, STDIN_FILENO) == -1)
        {
            close(final_input_fd);
            return (-1);
        }
        close(final_input_fd);
    }
    
    return (0);
}