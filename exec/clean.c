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
/*void cleanup_child_process(t_shell *shell)
{
    if (!shell)
        return;
    
    // Clean up environment variables
    if (shell->env)
    {
        free_env_list(shell->env);
        shell->env = NULL;
    }
    
    // Clean up tokens
    cleanup_t(shell);
    
    // Clean up parsed commands
    cleanup_p(shell);

    // Clean up input string
    if (shell->in)
    {
        free(shell->in);
        shell->in = NULL;
    }
    
    // Clean up current working directory if stored
    if (shell->cwd)
    {
        free(shell->cwd);
        shell->cwd = NULL;
    }
    
    // Clean up stdin/stdout backup
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
    
    // Clear readline history in child (if needed)
    rl_clear_history();
}
*/
void cleanup_child_process(t_shell *shell)
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

void cleanup_pipeline_child(t_shell *shell)
{
    if (!shell)
        return;

    
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
