/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:04:29 by nfakih            #+#    #+#             */
/*   Updated: 2025/10/23 19:49:09 by nour             ###   ########.fr       */
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
}
