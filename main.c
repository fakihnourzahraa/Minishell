/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:30:14 by nfakih            #+#    #+#             */
/*   Updated: 2025/09/16 17:51:01 by nfakih           ###   ########.fr       */
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
int	while_l(t_shell *shell, char *input)
{
	while (!shell->exit)
    {
        input = readline("minishell$ ");
        if (!input)
			return (0);//	return free_env(shell); which inclues printf exit;
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
		// if (!nour(shell))
		// 	exit (127);
		//add execute commands to nour
        execute_commands(shell);
        if (g_signal == SIGINT)
        {
            g_signal = 0;
            shell->exit_status = 130;
        }
        if (shell->exit)
        {
            cleanup_p(shell);
            cleanup_t(shell);
           // free(input);
            break;
        }
        cleanup_p(shell);
       // free(input);
    }
}
int main(int argc, char **argv, char **envp)
{
    t_shell *shell;
	char	*input;
    (void)argc;
    (void)argv;

    init_exec_shell(shell, envp);
    signals_prompt();
	while_l(shell, input);
    return (shell->exit_status);
}
