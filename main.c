/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:30:14 by nfakih            #+#    #+#             */
/*   Updated: 2025/10/13 17:06:06 by nour             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_signal;

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

    rl_clear_history();
}

int nour_parsing(t_shell *shell)
{
    int tokenize_result = tokenize_line(shell);
    if (tokenize_result == -1)
        return (-1);
    
    if (check_tkns(shell, shell->tkns) == -1)
        return (-1);
    
    parse(shell, shell->tkns);
	iterate_expansion(shell);
    
    return (0);
}

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
    int cmd_num;
    t_cmd *cmd_chain;

    cmd_num = 0;
    cmd_chain = shell->cmds;
    
    if (!cmd_chain)
        return;
    t_cmd *current = cmd_chain;
    while (current)
    {
        if (current->cmd)
            current->builtin = is_builtin(current->cmd);
        else
            current->builtin = NOT_BUILTIN;
        
        current = current->next;
        cmd_num++;
    }
    if (cmd_chain->next)
    {
        execute_pipeline(shell, cmd_chain);
    }

    else
    {
        if (is_redirect_only_command(cmd_chain))
        {
            execute_redirect_only(cmd_chain, shell);
        }
        else if (cmd_chain->builtin != NOT_BUILTIN)
        {
            execute_builtin(cmd_chain, shell);
        }
        else
        {
            execute_single(shell, cmd_chain);
        }
    }
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
        if (shell->in)
        {
            free(shell->in);
            shell->in = NULL;
        }
        return (-1);
    }
    
    mira_execution(shell);
    cleanup_t(shell);
    cleanup_p(shell);
    if (shell->in)
    {
        free(shell->in);
        shell->in = NULL;
    }
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
        
        // Normal command processing
        process_input(shell, input);
        // if (process_input(shell, input) == -1)
        //     printf("Error\n");
        if (g_signal == SIGINT)
        {
            g_signal = 0;
            shell->exit_status = 130;
        }
        
        if (shell->exit)
        {
            update_shlvl_on_exit(shell);
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