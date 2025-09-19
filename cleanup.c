/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:46:40 by nfakih            #+#    #+#             */
/*   Updated: 2025/09/19 13:36:34 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_t(t_shell *shell)
{
	t_token *t;

	while (shell->tkns)
	{
		if (shell->tkns->s)
			free(shell->tkns->s);
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
        if (redir->s)
            free(redir->s);
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

    current = shell->cmds;
    while (current)
    {
        if (current->cmd)
            free(current->cmd);
        if (current->path)
            free(current->path);

        if (current->args)
        {
            i = 0;
            while (current->args[i])
            {
                free(current->args[i]);
                i++;
            }
            free(current->args);
        }

        cleanup_redirs(current->rd);

        tmp = current;
        current = current->next;
        free(tmp);
    }
    shell->cmds = NULL;
}

void cleanup_env(t_shell *shell)
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