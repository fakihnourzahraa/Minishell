/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:30:14 by nfakih            #+#    #+#             */
/*   Updated: 2025/09/16 16:54:35 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_commands(t_shell *shell)
{
	t_cmd	*cmd_chain;

	cmd_chain = shell->cmds;
    if (!cmd_chain)
        return;
    if (cmd_chain->next)
        execute_pipeline(shell, cmd_chain);
    else
    {
        if (cmd_chain->builtin != NOT_BUILTIN)
            execute_builtin(cmd_chain, shell);
        else
            execute_single(shell, cmd_chain);
    }
}
void init_exec_shell(t_shell *shell, char **envp)
{
    shell->env = init_env_from_envp(envp);
    shell->exit_status = 0;
    shell->in_h = 0;
    shell->exit = false;
    shell->tkns = NULL;
    shell->cmds = NULL;
    shell->in = NULL;
    shell->envp = NULL;
    shell->cwd = NULL;
    shell->sti = NULL;
    shell->sto = NULL;
}
int main(int argc, char **argv, char **envp)
{
    t_shell *shell;
    char *input;
    char **tokens;
    (void)argc;
    (void)argv;

    init_exec_shell(&shell, envp);
    signals_prompt();
    while (!shell->exit)
    {
        input = readline("minishell$ ");
        if (!input)
        {
			free_env(shell);
            printf("exit\n");
            break;
        }
        if (g_signal == SIGINT)
        {
            g_signal = 0;
            shell->exit_status = 130;
            if (input && input[0] != '\0')
				shell->in = ft_strdup(input);
            continue;
        }
        if (input[0] == '\0')
        {
            free(input);
            continue;
        }
        add_history(input);
        g_signal = 0;
		if (!nour(shell))
			exit (127);
        execute_commands(&shell);
        if (g_signal == SIGINT)
        {
            g_signal = 0;
            shell->exit_status = 130;
        }
        if (shell->exit)
        {
            free_cmd_chain(shell->cmds);
            free_split(tokens);
            free(input);
            break;
        }
        cleanup_p(tokens);
        free(input);
    }
    return shell->exit_status;
}
