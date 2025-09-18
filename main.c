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
extern int g_signal;

void init_shell(t_shell *shell, char **envp)
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
    update_shlvl_on_start(shell);
}

void cleanup_shell(t_shell *shell)
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

    cleanup_env(shell);

    rl_clear_history();
}

int nour_parsing(t_shell *shell)
{
    int tokenize_result = tokenize_line(shell);
    if (tokenize_result == -1)
        return (-1);
    
    if (check_tkns(shell->tkns) == -1)
        return (-1);
    
    parse(shell, shell->tkns);
    
    return (0);
}

void mira_execution(t_shell *shell)
{
    t_cmd *cmd_chain = shell->cmds;
    
    if (!cmd_chain)
        return;
    
    t_cmd *current = cmd_chain;
    while (current)
    {
        current->builtin = is_builtin(current->cmd);
        current = current->next;
    }
    
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

int process_input(t_shell *shell, char *input)
{
    //printf("DEBUG: process_input started\n");
    shell->in = ft_strdup(input);
    if (!shell->in)
        return (-1);
    
    if (nour_parsing(shell) == -1)
    {
        //printf("DEBUG: nour_parsing failed, calling cleanup\n");
        cleanup_t(shell);
        cleanup_p(shell);
        free(shell->in);
        shell->in = NULL;
        return (-1);
    }
    
    //printf("DEBUG: calling mira_execution\n");
    mira_execution(shell);
    //printf("DEBUG: mira_execution FINISHED - about to cleanup\n");
    cleanup_t(shell);
    cleanup_p(shell);
    free(shell->in);
    shell->in = NULL;
    //printf("DEBUG: process_input finished\n");
    return (0);
}

int main_loop(t_shell *shell)
{
    char *input;
    
    while (!shell->exit)
    {
        if (g_signal == SIGINT)
        {
            g_signal = 0;
            shell->exit_status = 130;
        }
        input = readline("minishell$ ");
        
        if (!input)
        {
            update_shlvl_on_exit(shell);
            printf("exit\n");
            break;
        }
        if (g_signal == SIGINT)
        {
            g_signal = 0;
            shell->exit_status = 130;
            free(input);
            continue; 
        }
        if (input[0] == '\0')
        {
            free(input);
            continue;
        }
        add_history(input);
        g_signal = 0;
        if (process_input(shell, input) == -1)
        {
            printf("Error processing command\n");
        }
        
        // Handle signal after execution
        if (g_signal == SIGINT)
        {
            g_signal = 0;
            shell->exit_status = 130;
        }
        if (shell->exit)
        {
            free(input);
            break;
        }
        free(input);
    }

    return (shell->exit_status);
}

int main(int argc, char **argv, char **envp)
{
    t_shell shell;
    
    (void)argc;
    (void)argv;
    
    // Initialize shell
    init_shell(&shell, envp);
    signals_prompt();
    
    //printf("=== MINISHELL - INTEGRATED PARSING + EXECUTION TEST ===\n");
    //printf("Type commands to test both parsing and execution together\n");
    //printf("Use 'exit' to quit\n\n");

    int exit_status = main_loop(&shell);
    cleanup_shell(&shell);
    
    return (exit_status);
}