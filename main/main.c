/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:35:19 by miwehbe           #+#    #+#             */
/*   Updated: 2025/09/14 12:19:55 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"main.h"

void cleanup_shell(t_shell *shell)
{
    // Free environment list
    if (shell->env)
    {
        free_env_list(shell->env);
        shell->env = NULL;
    }
    
    // Free command chain if any remaining
    if (shell->cmds)
    {
        free_cmd_chain(shell->cmds);
        shell->cmds = NULL;
    }
    
    // Free any remaining input
    if (shell->in)
    {
        free(shell->in);
        shell->in = NULL;
    }
    
    // Clear readline history
    rl_clear_history();
}

void free_cmd_chain_complete(t_cmd *cmd)
{
    t_cmd *next;
    
    while (cmd) 
    {
        next = cmd->next;
        
        // Free command name
        if (cmd->cmd) 
        {
            free(cmd->cmd);
            cmd->cmd = NULL;
        }
        
        // Free path
        if (cmd->path)
        {
            free(cmd->path);
            cmd->path = NULL;
        }
            
        // Free arguments array
        if (cmd->args) 
        {
            for (int i = 0; cmd->args[i]; i++)
            {
                free(cmd->args[i]);
                cmd->args[i] = NULL;
            }
            free(cmd->args);
            cmd->args = NULL;
        }
        
        // Free redirections
        t_redir *redir = cmd->rd;
        while (redir) 
        {
            t_redir *next_redir = redir->next;
            if (redir->s)
            {
                free(redir->s);
                redir->s = NULL;
            }
            free(redir);
            redir = next_redir;
        }
        cmd->rd = NULL;
        
        free(cmd);
        cmd = next;
    }
}

void init_shell(t_shell *shell, char **envp)
{
    shell->exit_status = 0;
    shell->in_h = 0;
    shell->tkns = NULL;
    shell->cmds = NULL;
    shell->in = NULL;
    shell->cwd = NULL;
    shell->sti = NULL;
    shell->sto = NULL;
    shell->exit = false;
    
    // Initialize environment from envp
    shell->env = init_env_from_envp(envp);
    shell->envp = NULL;
}

t_redir *create_redir(t_r_type type, char *file)
{
    t_redir *redir = malloc(sizeof(t_redir));
    if (!redir)
        return NULL;
        
    redir->type = type;
    redir->s = ft_strdup(file);
    redir->next = NULL;
    redir->fd = -1;
    return redir;
}

t_cmd *create_cmd(char **args, t_redir *redir)
{
    t_cmd *cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return NULL;
        
    cmd->cmd = ft_strdup(args[0]);
    cmd->args = args;
    cmd->rd = redir;
    cmd->builtin = is_builtin(args[0]);
    cmd->next = NULL;
    cmd->pid = 0;
    cmd->path = NULL;
    cmd->i_fd = 0;     
    cmd->o_fd = 1;
    return cmd;
}

void parse_and_execute(t_shell *shell, char *input)
{
    char **tokens = ft_split(input, ' ');
    if (!tokens || !tokens[0]) 
    {
        if (tokens) 
            free_split(tokens);
        return;
    }
    
    // Simple parsing for pipes and redirections
    t_cmd *first_cmd = NULL, *current_cmd = NULL;
    char **cmd_args = malloc(sizeof(char *) * 10);
    int arg_count = 0;
    t_redir *redir = NULL;
    
    for (int i = 0; tokens[i]; i++) 
    {
        if (ft_strcmp(tokens[i], "|") == 0) 
        {
            // Create command and add to chain
            if (arg_count > 0)
            {
                cmd_args[arg_count] = NULL;
                t_cmd *new_cmd = create_cmd(cmd_args, redir);
                if (!first_cmd) 
                    first_cmd = new_cmd;
                else 
                    current_cmd->next = new_cmd;
                current_cmd = new_cmd;
            }
            else
            {
                free(cmd_args);
            }
            
            // Reset for next command
            cmd_args = malloc(sizeof(char *) * 10);
            arg_count = 0;
            redir = NULL;
        }
        else if (ft_strcmp(tokens[i], "<") == 0 && tokens[i+1]) 
        {
            redir = create_redir(R_IN, tokens[++i]);
        }
        else if (ft_strcmp(tokens[i], ">") == 0 && tokens[i+1]) 
        {
            redir = create_redir(R_OUT, tokens[++i]);
        }
        else if (ft_strcmp(tokens[i], ">>") == 0 && tokens[i+1]) 
        {
            redir = create_redir(R_APPEND, tokens[++i]);
        }
        else if (ft_strcmp(tokens[i], "<<") == 0 && tokens[i+1]) 
        {
            redir = create_redir(R_HEREDOC, tokens[++i]);
        }
        else 
        {
            cmd_args[arg_count++] = ft_strdup(tokens[i]);
        }
    }
    
    // Create last command
    if (arg_count > 0) 
    {
        cmd_args[arg_count] = NULL;
        t_cmd *new_cmd = create_cmd(cmd_args, redir);
        if (!first_cmd) 
            first_cmd = new_cmd;
        else 
            current_cmd->next = new_cmd;
    }
    else
    {
        free(cmd_args);
        // Free any orphaned redirections
        while (redir)
        {
            t_redir *tmp = redir->next;
            if (redir->s)
                free(redir->s);
            free(redir);
            redir = tmp;
        }
    }
    
    // Execute
    if (first_cmd) 
    {
        if (first_cmd->next) 
        {
            execute_pipeline(shell, first_cmd);
        } 
        else 
        {
            execute_single(shell, first_cmd);
        }
        
        // IMPORTANT: Free the command chain after execution
        free_cmd_chain_complete(first_cmd);
    }
    
    // Free tokens
    free_split(tokens);
}

int main(int argc, char **argv, char **envp)
{
    t_shell shell;
    char **tokens;
    (void)argc; (void)argv;
    
    init_shell(&shell, envp);
    signals_prompt();
   
    while (1)
    {
        shell.in = readline("minishell$ ");
        
        if (!shell.in)
        {
            printf("exit\n");
            break;
        }

        if (g_signal == SIGINT)
        {
            g_signal = 0;
            shell.exit_status = 130;
            free(shell.in);
            shell.in = NULL;
            continue;
        }

        if (shell.in[0] == '\0')
        {
            free(shell.in);
            shell.in = NULL;
            continue;
        }

        add_history(shell.in);

        // Tokenize by spaces
        tokens = ft_split(shell.in, ' ');
        if (!tokens || !tokens[0])
        {
            free(shell.in);
            shell.in = NULL;
            if (tokens)
                free_split(tokens);
            continue;
        }

        // Parse commands, pipes, and redirections
        t_cmd *cmd_list = NULL;
        t_cmd *current_cmd = NULL;
        char **current_args = malloc(sizeof(char *) * 100);
        int arg_idx = 0;
        t_redir *current_redir = NULL;
        t_redir *last_redir = NULL;
        int i = 0;

        while (tokens[i])
        {
            if (ft_strcmp(tokens[i], "|") == 0)
            {
                // Finish current command
                if (arg_idx > 0)
                {
                    current_args[arg_idx] = NULL;
                    
                    t_cmd *new_cmd = malloc(sizeof(t_cmd));
                    new_cmd->cmd = ft_strdup(current_args[0]);
                    new_cmd->args = current_args;
                    new_cmd->rd = current_redir;
                    new_cmd->builtin = is_builtin(current_args[0]);
                    new_cmd->next = NULL;
                    new_cmd->pid = 0;
                    new_cmd->path = NULL;
                    new_cmd->i_fd = 0;
                    new_cmd->o_fd = 1;
                    
                    if (!cmd_list)
                        cmd_list = new_cmd;
                    else
                        current_cmd->next = new_cmd;
                    current_cmd = new_cmd;
                }
                else
                {
                    free(current_args);
                }
                
                // Reset for next command
                current_args = malloc(sizeof(char *) * 100);
                arg_idx = 0;
                current_redir = NULL;
                last_redir = NULL;
                i++;
            }
            else if (ft_strcmp(tokens[i], ">") == 0 && tokens[i + 1])
            {
                t_redir *new_redir = malloc(sizeof(t_redir));
                new_redir->type = R_OUT;
                new_redir->s = ft_strdup(tokens[i + 1]);
                new_redir->next = NULL;
                new_redir->fd = -1;
                
                if (!current_redir)
                    current_redir = new_redir;
                else
                    last_redir->next = new_redir;
                last_redir = new_redir;
                i += 2;
            }
            else if (ft_strcmp(tokens[i], "<") == 0 && tokens[i + 1])
            {
                t_redir *new_redir = malloc(sizeof(t_redir));
                new_redir->type = R_IN;
                new_redir->s = ft_strdup(tokens[i + 1]);
                new_redir->next = NULL;
                new_redir->fd = -1;
                
                if (!current_redir)
                    current_redir = new_redir;
                else
                    last_redir->next = new_redir;
                last_redir = new_redir;
                i += 2;
            }
            else if (ft_strcmp(tokens[i], ">>") == 0 && tokens[i + 1])
            {
                t_redir *new_redir = malloc(sizeof(t_redir));
                new_redir->type = R_APPEND;
                new_redir->s = ft_strdup(tokens[i + 1]);
                new_redir->next = NULL;
                new_redir->fd = -1;
                
                if (!current_redir)
                    current_redir = new_redir;
                else
                    last_redir->next = new_redir;
                last_redir = new_redir;
                i += 2;
            }
            else if (ft_strcmp(tokens[i], "<<") == 0 && tokens[i + 1])
            {
                t_redir *new_redir = malloc(sizeof(t_redir));
                new_redir->type = R_HEREDOC;
                new_redir->s = ft_strdup(tokens[i + 1]);
                new_redir->next = NULL;
                new_redir->fd = -1;
                
                if (!current_redir)
                    current_redir = new_redir;
                else
                    last_redir->next = new_redir;
                last_redir = new_redir;
                i += 2;
            }
            else
            {
                current_args[arg_idx++] = ft_strdup(tokens[i]);
                i++;
            }
        }

        // Add the last command
        if (arg_idx > 0)
        {
            current_args[arg_idx] = NULL;
            
            t_cmd *new_cmd = malloc(sizeof(t_cmd));
            new_cmd->cmd = ft_strdup(current_args[0]);
            new_cmd->args = current_args;
            new_cmd->rd = current_redir;
            new_cmd->builtin = is_builtin(current_args[0]);
            new_cmd->next = NULL;
            new_cmd->pid = 0;
            new_cmd->path = NULL;
            new_cmd->i_fd = 0;
            new_cmd->o_fd = 1;
            
            if (!cmd_list)
                cmd_list = new_cmd;
            else
                current_cmd->next = new_cmd;
        }
        else
        {
            free(current_args);
            // Free any orphaned redirections
            while (current_redir)
            {
                t_redir *tmp = current_redir->next;
                free(current_redir->s);
                free(current_redir);
                current_redir = tmp;
            }
        }

        // Execute commands
        if (cmd_list)
        {
            if (cmd_list->next)  // Pipeline (multiple commands)
            {
                execute_pipeline(&shell, cmd_list);
            }
            else  // Single command
            {
                if (cmd_list->builtin != NOT_BUILTIN)
                    execute_builtin(cmd_list, &shell);
                else
                    execute_single(&shell, cmd_list);
            }
            
            // Free command list completely
            free_cmd_chain_complete(cmd_list);
        }

        // Handle signals after execution
        if (g_signal == SIGINT)
        {
            g_signal = 0;
            shell.exit_status = 130;
        }

        free_split(tokens);
        free(shell.in);
        shell.in = NULL;
    }
    
    // Clean up everything before exit
    cleanup_shell(&shell);
    
    return shell.exit_status;
}