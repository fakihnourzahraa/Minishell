/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:35:19 by miwehbe           #+#    #+#             */
/*   Updated: 2025/09/14 18:11:37 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_redir *create_simple_redir(t_r_type type, char *filename)
{
    t_redir *redir;

    redir = malloc(sizeof(t_redir));
    if (!redir)
        return NULL;

    redir->type = type;
    redir->s = filename ? ft_strdup(filename) : NULL;
    redir->fd = -1;
    redir->next = NULL;

    return redir;
}

// Add redirection to command
void add_redir_to_cmd(t_cmd *cmd, t_redir *new_redir)
{
    t_redir *current;

    if (!cmd || !new_redir)
        return;

    if (!cmd->rd)
    {
        cmd->rd = new_redir;
    }
    else
    {
        current = cmd->rd;
        while (current->next)
            current = current->next;
        current->next = new_redir;
    }
}

// Create command from tokens (handles redirections) - FIXED VERSION
t_cmd *create_cmd_with_redir(char **tokens, int start, int end)
{
    t_cmd *cmd;
    char **args;
    int arg_count = 0;
    int i, j;

    if (!tokens || start >= end)
        return NULL;

    cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return NULL;

    // Count non-redirection arguments
    i = start;
    while (i < end)
    {
        if (ft_strcmp(tokens[i], "<") == 0 || ft_strcmp(tokens[i], ">") == 0 ||
            ft_strcmp(tokens[i], ">>") == 0 || ft_strcmp(tokens[i], "<<") == 0)
        {
            i += 2; // Skip operator and filename
        }
        else
        {
            arg_count++;
            i++;
        }
    }

    if (arg_count == 0)
    {
        free(cmd);
        return NULL;
    }

    // Allocate arguments array
    args = malloc(sizeof(char *) * (arg_count + 1));
    if (!args)
    {
        free(cmd);
        return NULL;
    }

    // Initialize args array to NULL for safety
    for (int k = 0; k <= arg_count; k++)
        args[k] = NULL;

    // Fill arguments and handle redirections
    i = start;
    j = 0;
    cmd->rd = NULL;

    while (i < end)
    {
        if (ft_strcmp(tokens[i], "<") == 0 && i + 1 < end)
        {
            t_redir *redir = create_simple_redir(R_IN, tokens[i + 1]);
            if (!redir)
            {
                // Cleanup on error
                while (--j >= 0)
                    free(args[j]);
                free(args);
                free(cmd);
                return NULL;
            }
            add_redir_to_cmd(cmd, redir);
            i += 2;
        }
        else if (ft_strcmp(tokens[i], ">") == 0 && i + 1 < end)
        {
            t_redir *redir = create_simple_redir(R_OUT, tokens[i + 1]);
            if (!redir)
            {
                // Cleanup on error
                while (--j >= 0)
                    free(args[j]);
                free(args);
                free(cmd);
                return NULL;
            }
            add_redir_to_cmd(cmd, redir);
            i += 2;
        }
        else if (ft_strcmp(tokens[i], ">>") == 0 && i + 1 < end)
        {
            t_redir *redir = create_simple_redir(R_APPEND, tokens[i + 1]);
            if (!redir)
            {
                // Cleanup on error
                while (--j >= 0)
                    free(args[j]);
                free(args);
                free(cmd);
                return NULL;
            }
            add_redir_to_cmd(cmd, redir);
            i += 2;
        }
        else if (ft_strcmp(tokens[i], "<<") == 0 && i + 1 < end)
        {
            t_redir *redir = create_simple_redir(R_HEREDOC, tokens[i + 1]);
            if (!redir)
            {
                // Cleanup on error
                while (--j >= 0)
                    free(args[j]);
                free(args);
                free(cmd);
                return NULL;
            }
            add_redir_to_cmd(cmd, redir);
            i += 2;
        }
        else
        {
            args[j] = ft_strdup(tokens[i]);
            if (!args[j])
            {
                // Cleanup on strdup failure
                while (--j >= 0)
                    free(args[j]);
                free(args);
                // Also free any redirections we created
                t_redir *redir = cmd->rd;
                while (redir)
                {
                    t_redir *next = redir->next;
                    if (redir->s)
                        free(redir->s);
                    free(redir);
                    redir = next;
                }
                free(cmd);
                return NULL;
            }
            j++;
            i++;
        }
    }

    // Set command fields
    cmd->cmd = ft_strdup(args[0]);
    if (!cmd->cmd)
    {
        // Cleanup on cmd strdup failure
        for (int k = 0; k < j; k++)
            free(args[k]);
        free(args);
        t_redir *redir = cmd->rd;
        while (redir)
        {
            t_redir *next = redir->next;
            if (redir->s)
                free(redir->s);
            free(redir);
            redir = next;
        }
        free(cmd);
        return NULL;
    }

    cmd->args = args;
    cmd->path = NULL;
    cmd->i_fd = STDIN_FILENO;
    cmd->o_fd = STDOUT_FILENO;
    cmd->pid = -1;
    cmd->builtin = is_builtin(cmd->cmd);
    cmd->next = NULL;

    return cmd;
}

// Parse input and create command chain (handles pipes)
t_cmd *parse_input_simple(char **tokens)
{
    t_cmd *first_cmd = NULL;
    t_cmd *current_cmd = NULL;
    int start = 0;
    int i = 0;
    int token_count;

    if (!tokens || !tokens[0])
        return NULL;

    // Count tokens
    token_count = 0;
    while (tokens[token_count])
        token_count++;

    // Split by pipes and create commands
    while (i <= token_count)
    {
        // Find next pipe or end
        if (i == token_count || (tokens[i] && ft_strcmp(tokens[i], "|") == 0))
        {
            if (i > start)
            {
                t_cmd *new_cmd = create_cmd_with_redir(tokens, start, i);
                if (new_cmd)
                {
                    if (!first_cmd)
                        first_cmd = new_cmd;
                    else
                        current_cmd->next = new_cmd;
                    current_cmd = new_cmd;
                }
            }
            start = i + 1;
        }
        i++;
    }

    return first_cmd;
}

// Free command chain
void free_cmd_chain(t_cmd *cmd)
{
    t_cmd *next_cmd;
    t_redir *redir, *next_redir;
    int i;

    while (cmd)
    {
        next_cmd = cmd->next;

        if (cmd->cmd)
            free(cmd->cmd);
        if (cmd->path)
            free(cmd->path);

        if (cmd->args)
        {
            i = 0;
            while (cmd->args[i])
            {
                free(cmd->args[i]);
                i++;
            }
            free(cmd->args);
        }

        redir = cmd->rd;
        while (redir)
        {
            next_redir = redir->next;
            if (redir->s)
                free(redir->s);
            free(redir);
            redir = next_redir;
        }

        free(cmd);
        cmd = next_cmd;
    }
}

// Initialize shell
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

// Cleanup shell - FIXED VERSION
void cleanup_exec_shell(t_shell *shell)
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
    if (shell->cmds)
    {
        free_cmd_chain(shell->cmds);
        shell->cmds = NULL;
    }
    rl_clear_history();
}

// Execute commands (handles single, pipeline, builtins, external)
void execute_commands(t_shell *shell, t_cmd *cmd_chain)
{
    if (!cmd_chain)
        return;

    if (cmd_chain->next)
    {
        // Pipeline - use your pipeline execution
        execute_pipeline(shell, cmd_chain);
    }
    else
    {
        // Single command
        if (cmd_chain->builtin != NOT_BUILTIN)
        {
            // Builtin command
            execute_builtin(cmd_chain, shell);
        }
        else
        {
            // External command
            execute_single(shell, cmd_chain);
        }
    }
}

// Global cleanup function
void cleanup_on_exit(void)
{
    // This will be called on exit
}

int main(int argc, char **argv, char **envp)
{
    t_shell shell;
    char *input;
    char **tokens;
    t_cmd *cmd_chain;
    
    (void)argc;
    (void)argv;

    // Initialize
    init_exec_shell(&shell, envp);
    signals_prompt();
    
    // Register cleanup function
    atexit(cleanup_on_exit);
    
    while (!shell.exit)
    {
        // Get user input
        input = readline("minishell$ ");
        
        // Handle EOF (Ctrl+D)
        if (!input)
        {
            printf("exit\n");
            break;
        }
        
        // Handle signal
        if (g_signal == SIGINT)
        {
            g_signal = 0;
            shell.exit_status = 130;
            if (input)
            {
                free(input);
                input = NULL;
            }
            continue;
        }
        
        // Skip empty input
        if (input[0] == '\0')
        {
            free(input);
            continue;
        }
        
        // Add to history
        add_history(input);
        
        // Simple tokenization (split by spaces)
        tokens = ft_split(input, ' ');
        if (!tokens || !tokens[0])
        {
            free(input);
            if (tokens)
                free_split(tokens);
            continue;
        }
        
        // Parse into command chain (handles pipes and redirections)
        cmd_chain = parse_input_simple(tokens);
        if (!cmd_chain)
        {
            printf("Failed to create command\n");
            free_split(tokens);
            free(input);
            continue;
        }
        
        // Execute using YOUR execution functions
        execute_commands(&shell, cmd_chain);
        
        // Show exit status (comment this out if you don't want it)
        // printf("Exit status: %d\n", shell.exit_status);
        
        // Handle signal after execution
        if (g_signal == SIGINT)
        {
            g_signal = 0;
            shell.exit_status = 130;
        }
        
        // Clean up - PROPER ORDER
        free_cmd_chain(cmd_chain);
        free_split(tokens);
        free(input);
    }
    
    // Final cleanup - THIS WAS MISSING!
    cleanup_exec_shell(&shell);
    
    return shell.exit_status;
}