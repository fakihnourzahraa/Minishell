/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:46:40 by nfakih            #+#    #+#             */
/*   Updated: 2025/09/16 16:47:41 by nfakih           ###   ########.fr       */
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

void cleanup_p(t_shell *shell)
{
    t_cmd   *current;
	t_cmd *c;
    t_cmd   *next;
    int     i;

    if (!shell)
        return;
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
