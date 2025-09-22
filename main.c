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

//int execute_external_command(t_shell *shell, t_cmd *cmd);
//void debug_cmd_structure(t_cmd *cmd);

/*void debug_cmd_structure(t_cmd *cmd)
{
    printf("=== COMMAND DEBUG ===\n");
    printf("cmd->cmd: '%s'\n", cmd->cmd ? cmd->cmd : "NULL");
    printf("cmd->builtin: %d\n", cmd->builtin);
    
    if (cmd->args) {
        for (int i = 0; cmd->args[i]; i++) {
            printf("cmd->args[%d]: '%s'\n", i, cmd->args[i]);
        }
    } else {
        printf("cmd->args: NULL\n");
    }
    
    t_redir *r = cmd->rd;
    if (r) {
        printf("REDIRECTIONS:\n");
        while (r) {
            printf("  type=%d, file='%s'\n", r->type, r->s ? r->s : "NULL");
            r = r->next;
        }
    } else {
        printf("No redirections\n");
    }
    printf("=== END DEBUG ===\n");
}*/

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

    //cleanup_t(shell);
    //cleanup_p(shell);

    if (shell->in)
    {
        free(shell->in);
        shell->in = NULL;
    }
    cleanup_t(shell);
    cleanup_p(shell);
    /*if (shell->env)
    {
        free_env_list(shell->env);
        shell->env = NULL;
    }*/

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

/*int nour_parsing(t_shell *shell)
{
    printf("DEBUG: nour_parsing started\n");
    printf("DEBUG: shell->in = '%s'\n", shell->in ? shell->in : "NULL");
    
    int tokenize_result = tokenize_line(shell);
    printf("DEBUG: tokenize_line returned: %d\n", tokenize_result);
    
    if (tokenize_result == -1)
        return (-1);
    
    printf("DEBUG: About to check tokens\n");
    if (check_tkns(shell->tkns) == -1)
        return (-1);
    
    printf("DEBUG: About to call parse\n");
    parse(shell, shell->tkns);
    printf("DEBUG: parse finished\n");
    
    return (0);
}*/

/*int nour_parsing(t_shell *shell)
{
    printf("DEBUG: Starting tokenization for: \"%s\"\n", shell->in);
    
    int tokenize_result = tokenize_line(shell);
    if (tokenize_result == -1)
    {
        printf("ERROR: Tokenization failed!\n");
        return (-1);
    }
    
    printf("DEBUG: Tokenization successful\n");
    print_toke(shell->tkns);  // This should show your tokens
    
    if (check_tkns(shell->tkns) == -1)
    {
        printf("SYNTAX ERROR: Invalid token sequence detected!\n");
        return (-1);
    }
    
    printf("DEBUG: Starting parsing...\n");
    parse(shell, shell->tkns);
    
    // Add this debug to see what commands were created
    printf("DEBUG: Commands created:\n");
    t_cmd *current = shell->cmds;
    int cmd_num = 0;
    while (current)
    {
        printf("Command %d: cmd='%s'\n", cmd_num, current->cmd ? current->cmd : "NULL");
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
}*/
void mira_execution(t_shell *shell)
{
    //printf("DEBUG: mira_execution started\n");
    t_cmd *cmd_chain = shell->cmds;
    
    if (!cmd_chain)
    {
        //printf("DEBUG: No commands to execute\n");
        return;
    }
    //printf("DEBUG: Command found: '%s'\n", cmd_chain->cmd ? cmd_chain->cmd : "NULL");
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

/*void mira_execution(t_shell *shell)
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
    
    // ADD DEBUG HERE
    printf("=== DEBUGGING COMMAND STRUCTURE ===\n");
    current = cmd_chain;
    int cmd_num = 0;
    while (current)
    {
        printf("--- Command %d ---\n", cmd_num++);
        debug_cmd_structure(current);
        current = current->next;
    }
    printf("=== END DEBUGGING ===\n");
    
    if (cmd_chain->next)
        execute_pipeline(shell, cmd_chain);
    else
    {
        if (cmd_chain->builtin != NOT_BUILTIN)
            execute_builtin(cmd_chain, shell);
        else
            execute_single(shell, cmd_chain);  // This calls the function from exec/execute_single.c
    }
}*/

int process_input(t_shell *shell, char *input)
{
    //printf("DEBUG: process_input started\n");
    shell->in = ft_strdup(input);
    if (!shell->in)
        return (-1);
    //printf("DEBUG: About to call nour_parsing\n");
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
    if (shell->in)
    {
        free(shell->in);
        shell->in = NULL;
    }
    //free(shell->in);
    //shell->in = NULL;
    //printf("DEBUG: process_input finished\n");
    return (0);
}

/*int main_loop(t_shell *shell)
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
}*/

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
        
        // Normal command processing
        if (process_input(shell, input) == -1)
        {
            printf("Error processing command\n");
        }
        
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