/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:35:19 by miwehbe           #+#    #+#             */
/*   Updated: 2025/09/07 16:12:07 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"main.h"
//#include "tools.h"
//#include "exec.h"
//#include "builtin.h"
/*void	init_shell(t_shell *a)
{
	a->env = NULL;
	a->tkns = NULL;
	a->cmds = NULL;
	a->in = NULL;
	a->envp = NULL;
	a->exit_status = 0;
	a->cwd = NULL;
}
void	init_shell(t_shell *shell, char **envp)
{
	int	i;

	if (!shell)
		return ;
	shell->exit_status = 0;
	shell->in = NULL;

	// Count env variables
	i = 0;
	while (envp[i])
		i++;

	// Allocate and copy envp
	shell->envp = malloc(sizeof(char *) * (i + 1));
	if (!shell->envp)
		return ;
	i = 0;
	while (envp[i])
	{
		shell->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	shell->envp[i] = NULL;
}


void	free_shell(t_shell *shell)
{
	int	i;

	if (!shell)
		return ;
	if (shell->envp)
	{
		i = 0;
		while (shell->envp[i])
		{
			free(shell->envp[i]);
			i++;
		}
		free(shell->envp);
	}
}*/

/*int	main(int argc, char **argv, char **envp)
{
	t_shell	*a;
	(void)argc;
	(void)argv;
	t_cmd	cmd;
	char	**args;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);

	a = malloc(sizeof(t_shell));
	if (!a)
		return (1);
	init_shell(a,envp);
	while (1)
	{
		a->in = readline("minishell$ ");
		if (!a->in)
			break ;
		if (a->in[0] != '\0')
			add_history(a->in);
		args = ft_split(a->in, ' ');
		if (!args)
		{
			free(a->in);
			continue ;
		}
		cmd.args = args;
		cmd.builtin = is_builtin(args[0]);
		if (args[0])
		{
			if (cmd.builtin != NOT_BUILTIN)
				execute_builtin(&cmd, a);
			else
				execute_single(a, &cmd);
		}
		free_split(args);
		free(a->in);
	}
	free_shell(a);
	free(a);
	return (0);
}
*/

#include"main.h"

void	init_shell(t_shell *shell, char **envp)
{
	int	i;

	if (!shell)
		return ;
	shell->exit_status = 0;
	shell->in = NULL;

	// Count env variables
	i = 0;
	while (envp[i])
		i++;

	// Allocate and copy envp
	shell->envp = malloc(sizeof(char *) * (i + 1));
	if (!shell->envp)
		return ;
	i = 0;
	while (envp[i])
	{
		shell->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	shell->envp[i] = NULL;
}

void	free_shell(t_shell *shell)
{
	int	i;

	if (!shell)
		return ;
	if (shell->envp)
	{
		i = 0;
		while (shell->envp[i])
		{
			free(shell->envp[i]);
			i++;
		}
		free(shell->envp);
	}
}

int main(int argc, char **argv, char **envp)
{
    t_shell *shell;
    t_cmd cmd;
    char **tokens;

    (void)argc;
    (void)argv;

    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);

    shell = malloc(sizeof(t_shell));
    if (!shell)
        return 1;
    init_shell(shell, envp);

    while (1)
    {
        g_signal = 0;  // Reset signal flag
        if (g_signal != SIGINT)  // Only show prompt if not interrupted
            shell->in = readline("minishell$ ");
        else
        {
            shell->in = readline("minishell$ ");  // This will show the prompt
            g_signal = 0;
        }
        //shell->in = readline("minishell$ ");
        
        // Handle Ctrl+C during readline
        if (g_signal == SIGINT)
        {
            shell->exit_status = 130;
            printf("minishell$ ");  // Show new prompt
            fflush(stdout);
            continue;
        }
        
        if (!shell->in)
            break;
        if (shell->in[0] != '\0')
            add_history(shell->in);

        tokens = ft_split(shell->in, ' ');
        if (!tokens)
        {
            free(shell->in);
            continue;
        }

        // --- REDIRECTION DETECTION ---
        t_redir *redir = NULL;
        t_redir *last = NULL;
        int i = 0;

        while (tokens[i])
        {
            if (strcmp(tokens[i], "<") == 0 && tokens[i + 1])
            {
                t_redir *new = malloc(sizeof(t_redir));
                new->type = R_IN;
                new->s = tokens[i + 1];
                new->next = NULL;
                if (!redir)
                    redir = new;
                else
                    last->next = new;
                last = new;
                // Remove tokens[i] and tokens[i+1] from args
                int j = i;
                while (tokens[j + 2])
                {
                    tokens[j] = tokens[j + 2];
                    j++;
                }
                tokens[j] = NULL;
                tokens[j + 1] = NULL;
                continue; // stay at same i
            }
            else if (strcmp(tokens[i], ">") == 0 && tokens[i + 1])
            {
                t_redir *new = malloc(sizeof(t_redir));
                new->type = R_OUT;
                new->s = tokens[i + 1];
                new->next = NULL;
                if (!redir)
                    redir = new;
                else
                    last->next = new;
                last = new;
                int j = i;
                while (tokens[j + 2])
                {
                    tokens[j] = tokens[j + 2];
                    j++;
                }
                tokens[j] = NULL;
                tokens[j + 1] = NULL;
                continue;
            }
            else if (strcmp(tokens[i], ">>") == 0 && tokens[i + 1])
            {
                t_redir *new = malloc(sizeof(t_redir));
                new->type = R_APPEND;
                new->s = tokens[i + 1];
                new->next = NULL;
                if (!redir)
                    redir = new;
                else
                    last->next = new;
                last = new;
                int j = i;
                while (tokens[j + 2])
                {
                    tokens[j] = tokens[j + 2];
                    j++;
                }
                tokens[j] = NULL;
                tokens[j + 1] = NULL;
                continue;
            }
            else if (strcmp(tokens[i], "<<") == 0 && tokens[i + 1])
            {
                t_redir *new = malloc(sizeof(t_redir));
                new->type = R_HEREDOC;
                new->s = tokens[i + 1];
                new->next = NULL;
                if (!redir)
                    redir = new;
                else
                    last->next = new;
                last = new;
                int j = i;
                while (tokens[j + 2])
                {
                    tokens[j] = tokens[j + 2];
                    j++;
                }
                tokens[j] = NULL;
                tokens[j + 1] = NULL;
                continue;
            }
            i++;
        }

        cmd.args = tokens;
        cmd.rd = redir;
        cmd.builtin = tokens[0] ? is_builtin(tokens[0]) : NOT_BUILTIN;

        // --- EXECUTION ---
        if (tokens[0])
        {
            if (cmd.builtin != NOT_BUILTIN)
                execute_builtin(&cmd, shell);
            else
                execute_single(shell, &cmd);
        }

        // --- FREE ---
        t_redir *tmp;
        while (redir)
        {
            tmp = redir->next;
            free(redir);
            redir = tmp;
        }

        free_split(tokens);
        free(shell->in);
    }

    free_shell(shell);
    free(shell);
    return 0;
}