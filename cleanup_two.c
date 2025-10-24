/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:04:29 by nfakih            #+#    #+#             */
/*   Updated: 2025/10/24 13:26:30 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_pipeline_resources(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->in)
	{
		free(shell->in);
		shell->in = NULL;
	}
	if (shell->cwd)
	{
		free(shell->cwd);
		shell->cwd = NULL;
	}
	if (shell->sti)
	{
		free(shell->sti);
		shell->sti = NULL;
	}
	if (shell->sto)
	{
		free(shell->sto);
		shell->sto = NULL;
	}
	if (shell->quotes)
		free(shell->quotes);
	shell->quotes = NULL;
}

void	cleanup_in_shell(t_shell *shell)
{
	if (shell->in)
	{
		free(shell->in);
		shell->in = NULL;
	}
	if (shell->cwd)
	{
		free(shell->cwd);
		shell->cwd = NULL;
	}
	if (shell->sti)
	{
		free(shell->sti);
		shell->sti = NULL;
	}
	if (shell->sto)
	{
		free(shell->sto);
		shell->sto = NULL;
	}
}

void	cleanup_shell(t_shell *shell)
{
	if (!shell)
		return ;
	cleanup_t(shell);
	cleanup_p(shell);
	cleanup_in_shell(shell);
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
	rl_clear_history();
}
