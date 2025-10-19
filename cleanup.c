/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:46:40 by nfakih            #+#    #+#             */
/*   Updated: 2025/10/18 16:05:39 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_t(t_shell *shell)
{
	t_token	*t;

	if (!shell)
		return ;
	while (shell->tkns)
	{
		if (shell->tkns->s)
		{
			free(shell->tkns->s);
			shell->tkns->s = NULL;
		}
		t = shell->tkns;
		shell->tkns = shell->tkns->next;
		free(t);
	}
	shell->tkns = NULL;
}

static void	cleanup_redirs(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		if (redir->s)
		{
			free(redir->s);
			redir->s = NULL;
		}
		tmp = redir;
		redir = redir->next;
		free(tmp);
	}
}

void	cleanup_p_two(t_cmd *current)
{
	int	i;

	if (current->cmd)
	{
		free(current->cmd);
		current->cmd = NULL;
	}
	if (current->path)
	{
		free(current->path);
		current->path = NULL;
	}
	if (current->args)
	{
		i = 0;
		while (current->args[i])
		{
			free(current->args[i]);
			current->args[i] = NULL;
			i++;
		}
		free(current->args);
		current->args = NULL;
	}
}

void	cleanup_p(t_shell *shell)
{
	t_cmd	*current;
	t_cmd	*tmp;

	if (!shell)
		return ;
	current = shell->cmds;
	while (current)
	{
		cleanup_p_two(current);
		if (current->rd)
		{
			cleanup_redirs(current->rd);
			current->rd = NULL;
		}
		if (current->space)
			free(current->space);
		tmp = current;
		current = current->next;
		free(tmp);
	}
	shell->cmds = NULL;
}

void	cleanup_env(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->env)
	{
		free_env_list(shell->env);
		shell->env = NULL;
	}
	if (shell->envp)
	{
		free_envp(shell->envp);
		shell->envp = NULL;
	}
}
