/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:32:56 by miwehbe           #+#    #+#             */
/*   Updated: 2025/10/18 15:38:21 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	apply_output_redirections(t_cmd *cmd)
{
	t_redir	*current;

	current = cmd->rd;
	while (current)
	{
		if (current->type == R_OUT && handle_out_redir(current) == -1)
			return (-1);
		else if (current->type == R_APPEND
			&& handle_append_redir(current) == -1)
			return (-1);
		current = current->next;
	}
	return (0);
}

int	apply_redirections(t_cmd *cmd, t_shell *shell)
{
	t_redir	*current;

	if (!cmd)
		return (0);
	if (apply_output_redirections(cmd) == -1)
		return (-1);
	current = cmd->rd;
	while (current)
	{
		if (current->type == R_IN && handle_in_redir(shell, current) == -1)
			return (-1);
		current = current->next;
	}
	if (cmd->i_fd > 0)
	{
		if (redirect_fd(cmd->i_fd, STDIN_FILENO) == -1)
			return (-1);
		cmd->i_fd = -1;
	}
	return (0);
}

int	save_std_fds(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdin == -1 || *saved_stdout == -1)
	{
		if (*saved_stdin != -1)
			close(*saved_stdin);
		if (*saved_stdout != -1)
			close(*saved_stdout);
		return (-1);
	}
	return (0);
}

int	execute_redirect_only(t_cmd *cmd, t_shell *shell)
{
	int	saved_stdin;
	int	saved_stdout;
	int	result;

	if (!cmd || !cmd->rd)
		return (0);
	if (process_heredocs(cmd, shell) == -1)
		return (1);
	if (save_std_fds(&saved_stdin, &saved_stdout) == -1)
		return (-1);
	result = apply_redirections(cmd, shell);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (result);
}
