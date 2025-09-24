/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:46:40 by nfakih            #+#    #+#             */
/*   Updated: 2025/09/25 01:19:34 by nour             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void cleanup_t(t_shell *shell)
{
    t_token *t;

    if (!shell)
        return;
    
    while (shell->tkns)
    {
        /*if (shell->tkns->s)
            free(shell->tkns->s);*/
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

static void cleanup_redirs(t_redir *redir)
{
    t_redir *tmp;

    while (redir)
    {
        /*if (redir->s)
            free(redir->s);*/
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

void cleanup_p(t_shell *shell)
{
    t_cmd *current;
    t_cmd *tmp;
    int i;

    if (!shell)
        return;
    current = shell->cmds;
    while (current)
    {
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
        /*cleanup_redirs(current->rd);
        current->rd = NULL;*/
        if (current->rd)
        {
            cleanup_redirs(current->rd);
            current->rd = NULL;
        }
        tmp = current;
        current = current->next;
        free(tmp);
    }
    shell->cmds = NULL;
}

// void cleanup_env(t_shell *shell)
// {
//     if (!shell)
//         return;
//     if (shell->env)
//     {
//         free_env_list(shell->env);
//         shell->env = NULL;
//     }

//     if (shell->envp)    
//     {
//           free_envp(shell->envp);
//           shell->envp = NULL;
//     }
// }

void cleanup_pipeline_resources(t_shell *shell)
{
    if (!shell)
        return;
    
    // Clean up current input string
    if (shell->in)
    {
        free(shell->in);
        shell->in = NULL;
    }
    
    // Clean up current working directory if allocated
    if (shell->cwd)
    {
        free(shell->cwd);
        shell->cwd = NULL;
    }
    
    // Clean up standard input/output buffers if allocated
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

/*void cleanup_p(t_shell *shell)
{
    t_cmd   *current;
	t_cmd *c;
    //t_cmd   *next;
    int     i;

    if (!shell)
        return;
   current = shell->cmds;
    while (current)
    {
        //printf("DEBUG: Freeing command: '%s'\n", current->cmd ? current->cmd : "NULL");
        if (current->cmd)
            free(current->cmd);
        if (current->path)
            free(current->path);
        if (current->args)
        {
            i = 0;
            while (current->args[i])
            {
                //printf("DEBUG: Freeing arg[%d]: '%s'\n", i, current->args[i]);
                free(current->args[i]);
                i++;
            }
            free(current->args);
        }
        t_redir *redir = current->rd;
        while (redir)
        {
            t_redir *next_redir = redir->next;
            if (redir->s)
                free(redir->s);
            free(redir);
            redir = next_redir;
        }
        c = current;
		current = current->next;
        free(c);
    }
    shell->cmds = NULL;
}
*/