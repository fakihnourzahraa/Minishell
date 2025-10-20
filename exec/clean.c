/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:37:52 by miwehbe           #+#    #+#             */
/*   Updated: 2025/10/18 16:11:21 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	cleanup_child_environment(t_shell *shell)
{
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
	cleanup_t(shell);
	cleanup_p(shell);
}

static void	cleanup_child_strings(t_shell *shell)
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

void	cleanup_child_process(t_shell *shell)
{
	if (!shell)
		return ;
	cleanup_child_environment(shell);
	cleanup_child_strings(shell);
	rl_clear_history();
}

static void	cleanup_pipeline_data(t_shell *shell)
{
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
	cleanup_t(shell);
	cleanup_p(shell);
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
}

void	cleanup_pipeline_child(t_shell *shell)
{
	if (!shell)
		return ;
	cleanup_pipeline_data(shell);
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
	rl_clear_history();
}
