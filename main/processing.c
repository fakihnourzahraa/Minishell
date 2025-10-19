/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:18:57 by nfakih            #+#    #+#             */
/*   Updated: 2025/10/19 13:09:57 by nour             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	nour_parsing(t_shell *shell)
{
	int	tokenize_result;

	tokenize_result = tokenize_line(shell);
	if (tokenize_result == -1)
		return (-1);
	if (check_tkns(shell, shell->tkns) == -1)
		return (-1);
	parse(shell, shell->tkns);
	iterate_expansion(shell);
	return (0);
}

void	mira_execution(t_shell *shell)
{
	t_cmd	*cmd_chain;
	t_cmd	*current;

	cmd_chain = shell->cmds;
	if (!cmd_chain)
		return ;
	current = cmd_chain;
	while (current)
	{
		if (current->cmd)
			current->builtin = is_builtin(current->cmd);
		else
			current->builtin = NOT_BUILTIN;
		current = current->next;
	}
	if (cmd_chain->next)
		execute_pipeline(shell, cmd_chain);
	else
	{
		if (is_redirect_only_command(cmd_chain))
			execute_redirect_only(cmd_chain, shell);
		else
			execute_single(shell, cmd_chain);
	}
}

int	process_input(t_shell *shell, char *input)
{
	shell->in = ft_strdup(input);
	if (!shell->in)
		return (-1);
	if (nour_parsing(shell) == -1)
	{
		cleanup_t(shell);
		cleanup_p(shell);
		if (shell->in)
		{
			free(shell->in);
			shell->in = NULL;
		}
		return (-1);
	}
	mira_execution(shell);
	cleanup_t(shell);
	cleanup_p(shell);
	if (shell->in)
	{
		free(shell->in);
		shell->in = NULL;
	}
	return (0);
}
