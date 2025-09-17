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

/*extern int g_signal;

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
}

void cleanup_shell(t_shell *shell)
{
    if (shell->env)
    {
        free_env_list(shell->env);
        shell->env = NULL;
    }
    if (shell->in)
    {
        free(shell->in);
        shell->in = NULL;
    }
    cleanup_t(shell);
    cleanup_p(shell);
    rl_clear_history();
}

int nour_parsing(t_shell *shell)
{
    printf("DEBUG: Starting tokenization for: \"%s\"\n", shell->in);
    
    int tokenize_result = tokenize_line(shell);
    if (tokenize_result == -1)
    {
        printf("ERROR: Tokenization failed!\n");
        return (-1);
    }

    printf("DEBUG: Tokenization successful\n");
    print_toke(shell->tkns);
    if (check_tkns(shell->tkns) == -1)
    {
        printf("SYNTAX ERROR: Invalid token sequence detected!\n");
        return (-1);
    }
    printf("DEBUG: Starting parsing...\n");
    parse(shell, shell->tkns);
    t_cmd *current = shell->cmds;
    int cmd_num = 0;
    while (current)
    {
        if (current->args)
        {
            for (int i = 0; current->args[i]; i++)
                printf("  Arg[%d]: '%s'\n", i, current->args[i]);
        }
        t_redir *redir = current->rd;
        while (redir)
        {
            printf("  Redir: type=%d, file='%s'\n", redir->type, redir->s ? redir->s : "(null)");
            redir = redir->next;
        }
        
        current = current->next;
        cmd_num++;
    }
    
    return (0);
}

void mira_execution(t_shell *shell)
{
    t_cmd *cmd_chain = shell->cmds;
    
    if (!cmd_chain)
    {
        printf("DEBUG: No commands to execute\n");
        return;
    }
    
    printf("DEBUG: Starting execution...\n");
    t_cmd *current = cmd_chain;
    while (current)
    {
        current->builtin = is_builtin(current->cmd);
        current = current->next;
    }
    if (cmd_chain->next)
    {
        printf("DEBUG: Executing pipeline\n");
        execute_pipeline(shell, cmd_chain);
    }
    else
    {
        // In mira_execution(), right before execute_builtin():
        if (cmd_chain->builtin != NOT_BUILTIN)
        {
            printf("=== DEBUG COMMAND STRUCTURE ===\n");
            printf("cmd->cmd = '%s'\n", cmd_chain->cmd ? cmd_chain->cmd : "NULL");
            printf("cmd->builtin = %d\n", cmd_chain->builtin);
            printf("cmd->args[0] = '%s'\n", cmd_chain->args[0] ? cmd_chain->args[0] : "NULL");
            printf("cmd->args[1] = '%s'\n", cmd_chain->args[1] ? cmd_chain->args[1] : "NULL");
            
            if (cmd_chain->rd)
            {
                printf("REDIRECTIONS FOUND:\n");
                t_redir *r = cmd_chain->rd;
                while (r)
                {
                    printf("  type=%d, file='%s'\n", r->type, r->s ? r->s : "NULL");
                    r = r->next;
                }
            }
            else
            {
                printf("NO REDIRECTIONS\n");
            }
            printf("=== END DEBUG ===\n");
        
            execute_builtin(cmd_chain, shell);
        }
    }
    
    printf("DEBUG: Execution finished with exit status: %d\n", shell->exit_status);
}

int process_input(t_shell *shell, char *input)
{
    shell->in = ft_strdup(input);
    if (!shell->in)
        return (-1);
    if (nour_parsing(shell) == -1)
    {
        cleanup_t(shell);
        cleanup_p(shell);
        free(shell->in);
        shell->in = NULL;
        return (-1);
    }
    mira_execution(shell);
    cleanup_t(shell);
    cleanup_p(shell);
    free(shell->in);
    shell->in = NULL;
    
    return (0);
}

int main_loop(t_shell *shell)
{
    char *input;
    
    while (!shell->exit)
    {
        // Get user input
        input = readline("minishell$ ");
        
        // Handle EOF (Ctrl+D)
        if (!input)
        {
            printf("exit\n");
            break;
        }
        
        // Handle signal after readline
        if (g_signal == SIGINT)
        {
            g_signal = 0;  // Reset signal flag
            shell->exit_status = 130;
            
            if (input)
            {
                free(input);
                input = NULL;
            }
            continue;  // Signal handler already showed prompt
        }
        
        // Skip empty input
        if (input[0] == '\0')
        {
            free(input);
            continue;
        }
        
        // Add to history
        add_history(input);
        
        // Reset signal flag before processing
        g_signal = 0;
        
        // Process the input (parsing + execution)
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
        
        // Check if exit was called during execution
        if (shell->exit)
        {
            free(input);
            break;
        }
        
        // Clean up input
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
    
    // Set up signal handling
    signals_prompt();
    
    printf("=== MINISHELL - INTEGRATED PARSING + EXECUTION TEST ===\n");
    printf("Type commands to test both parsing and execution together\n");
    printf("Use 'exit' to quit\n\n");
    
    // Main loop
    int exit_status = main_loop(&shell);
    
    // Final cleanup
    cleanup_shell(&shell);
    
    return (exit_status);
}*/

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
        // Get user input
        input = readline("minishell$ ");
        
        // Handle EOF (Ctrl+D)
        if (!input)
        {
            printf("exit\n");
            break;
        }
        
        // Handle signal after readline
        if (g_signal == SIGINT)
        {
            g_signal = 0;  // Reset signal flag
            shell->exit_status = 130;
            
            if (input)
            {
                free(input);
                input = NULL;
            }
            continue;  // Signal handler already showed prompt
        }
        
        // Skip empty input
        if (input[0] == '\0')
        {
            free(input);
            continue;
        }
        
        // Add to history
        add_history(input);
        
        // Reset signal flag before processing
        g_signal = 0;
        
        // Process the input (parsing + execution)
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
        
        // Check if exit was called during execution
        if (shell->exit)
        {
            free(input);
            break;
        }
        
        // Clean up input
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
    
    // Set up signal handling
    signals_prompt();
    
    //printf("=== MINISHELL - INTEGRATED PARSING + EXECUTION TEST ===\n");
    //printf("Type commands to test both parsing and execution together\n");
    //printf("Use 'exit' to quit\n\n");
    
    // Main loop
    int exit_status = main_loop(&shell);
    
    // Final cleanup
    cleanup_shell(&shell);
    
    return (exit_status);
}