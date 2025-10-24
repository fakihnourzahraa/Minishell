/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 23:35:55 by miwehbe           #+#    #+#             */
/*   Updated: 2025/10/24 13:38:13 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	handle_file_error(char *filename)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
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

/*static int	handle_redir_heredoc(t_redir *redir, int input_fd, t_shell *shell)
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
}*/

/*int	handle_input_redirections(t_cmd *cmd, t_shell *shell)
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
*/
int	handle_input_redirections(t_cmd *cmd, t_shell *shell)
{
	t_redir	*redir;
	int		input_fd;

	(void)shell;
	if (cmd->i_fd > 0)
		input_fd = cmd->i_fd;
	else
		input_fd = STDIN_FILENO;
	redir = cmd->rd;
	while (redir)
	{
		if (redir->type == R_IN)
		{
			if (input_fd != STDIN_FILENO && input_fd > 2)
				close(input_fd);
			input_fd = handle_redir_in(redir, input_fd);
		}
		redir = redir->next;
	}
	return (input_fd);
}
