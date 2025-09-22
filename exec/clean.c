/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:37:52 by miwehbe           #+#    #+#             */
/*   Updated: 2025/09/22 16:37:52 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"exec.h"

/*void cleanup_child_process(t_shell *shell)
{
    if (!shell)
        return;
        
    if (shell->env)
    {
        free_env_list(shell->env);
        shell->env = NULL;
    }
    cleanup_t(shell);
    cleanup_p(shell);

    if (shell->in)
    {
        free(shell->in);
        shell->in = NULL;
    }
}*/
void cleanup_pipeline_child(t_shell *shell)
{
    if (!shell)
        return;
    if (shell->in)
    {
        free(shell->in);
        shell->in = NULL;
    }
}

/*void cleanup_heredoc_child(t_shell *shell)
{
    if (!shell)
        return;
    if (shell->in)
    {
        free(shell->in);
        shell->in = NULL;
    }
}*/
