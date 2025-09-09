/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:35:19 by miwehbe           #+#    #+#             */
/*   Updated: 2025/09/08 19:26:02 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"main.h"

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

//for testing red without pipe

void init_shell(t_shell *shell, char **envp)
{
    int i = 0;
    shell->exit_status = 0;
    shell->in_h = 0;
    while (envp[i]) i++;
    shell->envp = malloc(sizeof(char *) * (i + 1));
    i = 0;
    while (envp[i]) {
        shell->envp[i] = ft_strdup(envp[i]);
        i++;
    }
    shell->envp[i] = NULL;
}

t_redir *create_redir(t_r_type type, char *file)
{
    t_redir *redir = malloc(sizeof(t_redir));
    redir->type = type;
    redir->s = ft_strdup(file);
    redir->next = NULL;
    return redir;
}

t_cmd *create_cmd(char **args, t_redir *redir)
{
    t_cmd *cmd = malloc(sizeof(t_cmd));
    cmd->cmd = ft_strdup(args[0]);
    cmd->args = args;
    cmd->rd = redir;
    cmd->builtin = is_builtin(args[0]);
    cmd->next = NULL;
    cmd->pid = 0;
    return cmd;
}

void free_cmd_chain(t_cmd *cmd)
{
    t_cmd *next;
    t_redir *redir, *next_redir;
    
    while (cmd) {
        next = cmd->next;
        if (cmd->cmd) free(cmd->cmd);
        redir = cmd->rd;
        while (redir) {
            next_redir = redir->next;
            free(redir->s);
            free(redir);
            redir = next_redir;
        }
        free(cmd);
        cmd = next;
    }
}

void parse_and_execute(t_shell *shell, char *input)
{
    char **tokens = ft_split(input, ' ');
    if (!tokens || !tokens[0]) {
        if (tokens) free_split(tokens);
        return;
    }
    
    // Simple parsing for pipes and redirections
    t_cmd *first_cmd = NULL, *current_cmd = NULL;
    char **cmd_args = malloc(sizeof(char *) * 10);
    int arg_count = 0;
    t_redir *redir = NULL;
    
    for (int i = 0; tokens[i]; i++) {
        if (ft_strcmp(tokens[i], "|") == 0) {
            // Create command and add to chain
            cmd_args[arg_count] = NULL;
            t_cmd *new_cmd = create_cmd(cmd_args, redir);
            if (!first_cmd) first_cmd = new_cmd;
            else current_cmd->next = new_cmd;
            current_cmd = new_cmd;
            
            // Reset for next command
            cmd_args = malloc(sizeof(char *) * 10);
            arg_count = 0;
            redir = NULL;
        }
        else if (ft_strcmp(tokens[i], "<") == 0 && tokens[i+1]) {
            redir = create_redir(R_IN, tokens[++i]);
        }
        else if (ft_strcmp(tokens[i], ">") == 0 && tokens[i+1]) {
            redir = create_redir(R_OUT, tokens[++i]);
        }
        else if (ft_strcmp(tokens[i], ">>") == 0 && tokens[i+1]) {
            redir = create_redir(R_APPEND, tokens[++i]);
        }
        else if (ft_strcmp(tokens[i], "<<") == 0 && tokens[i+1]) {
            redir = create_redir(R_HEREDOC, tokens[++i]);
        }
        else {
            cmd_args[arg_count++] = tokens[i];
        }
    }
    
    // Create last command
    if (arg_count > 0) {
        cmd_args[arg_count] = NULL;
        t_cmd *new_cmd = create_cmd(cmd_args, redir);
        if (!first_cmd) first_cmd = new_cmd;
        else current_cmd->next = new_cmd;
    }
    
    // Execute
    if (first_cmd) {
        if (first_cmd->next) {
            execute_pipeline(shell, first_cmd);
        } else {
            execute_single(shell, first_cmd);
        }
        free_cmd_chain(first_cmd);
    }
    
    free_split(tokens);
}


/*int main(int argc, char **argv, char **envp)
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
            continue;
        }

        if (shell.in[0] == '\0')
        {
            free(shell.in);
            continue;
        }

        add_history(shell.in);

        // Tokenize by spaces
        tokens = ft_split(shell.in, ' ');
        if (!tokens || !tokens[0])
        {
            free(shell.in);
            if (tokens)
                free_split(tokens);
            continue;
        }

        // Parse redirections and clean command arguments
        t_redir *redir = NULL;
        t_redir *last = NULL;
        char **clean_tokens = malloc(sizeof(char *) * 100);
        int clean_idx = 0;
        int i = 0;

        while (tokens[i])
        {
            if (ft_strcmp(tokens[i], ">") == 0 && tokens[i + 1])
            {
                t_redir *new = malloc(sizeof(t_redir));
                new->type = R_OUT;
                new->s = ft_strdup(tokens[i + 1]);
                new->next = NULL;
                if (!redir)
                    redir = new;
                else
                    last->next = new;
                last = new;
                i += 2;
            }
            else if (ft_strcmp(tokens[i], "<") == 0 && tokens[i + 1])
            {
                t_redir *new = malloc(sizeof(t_redir));
                new->type = R_IN;
                new->s = ft_strdup(tokens[i + 1]);
                new->next = NULL;
                if (!redir)
                    redir = new;
                else
                    last->next = new;
                last = new;
                i += 2;
            }
            else if (ft_strcmp(tokens[i], ">>") == 0 && tokens[i + 1])
            {
                t_redir *new = malloc(sizeof(t_redir));
                new->type = R_APPEND;
                new->s = ft_strdup(tokens[i + 1]);
                new->next = NULL;
                if (!redir)
                    redir = new;
                else
                    last->next = new;
                last = new;
                i += 2;
            }
            else if (ft_strcmp(tokens[i], "<<") == 0 && tokens[i + 1])
            {
                t_redir *new = malloc(sizeof(t_redir));
                new->type = R_HEREDOC;
                new->s = ft_strdup(tokens[i + 1]);
                new->next = NULL;
                if (!redir)
                    redir = new;
                else
                    last->next = new;
                last = new;
                i += 2;
            }
            else
            {
                clean_tokens[clean_idx++] = ft_strdup(tokens[i]);
                i++;
            }
        }
        clean_tokens[clean_idx] = NULL;

        // Set up command structure
        t_cmd cmd = {0};
        cmd.args = clean_tokens;
        cmd.rd = redir;
        cmd.builtin = clean_tokens[0] ? is_builtin(clean_tokens[0]) : NOT_BUILTIN;

        // Execute command
        if (cmd.builtin != NOT_BUILTIN)
        {
            execute_builtin(&cmd, &shell);
        }
        else
        {
            execute_single(&shell, &cmd);
        }

        // Handle signals after execution
        if (g_signal == SIGINT)
        {
            g_signal = 0;
            shell.exit_status = 130;
        }

        // Cleanup
        t_redir *tmp;
        while (redir)
        {
            tmp = redir->next;
            free(redir->s);
            free(redir);
            redir = tmp;
        }
        
        for (int j = 0; j < clean_idx; j++)
            free(clean_tokens[j]);
        free(clean_tokens);
        
        free_split(tokens);
        free(shell.in);
    }
    
    // Cleanup shell
    if (shell.envp)
    {
        for (int i = 0; shell.envp[i]; i++)
            free(shell.envp[i]);
        free(shell.envp);
    }
    
    return shell.exit_status;
}*/



// for testing red with pipe

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
            continue;
        }

        if (shell.in[0] == '\0')
        {
            free(shell.in);
            continue;
        }

        add_history(shell.in);

        // Tokenize by spaces
        tokens = ft_split(shell.in, ' ');
        if (!tokens || !tokens[0])
        {
            free(shell.in);
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
            
            // Free command list
            t_cmd *cmd_tmp;
            while (cmd_list)
            {
                cmd_tmp = cmd_list->next;
                
                // Free redirections
                t_redir *redir_tmp;
                while (cmd_list->rd)
                {
                    redir_tmp = cmd_list->rd->next;
                    free(cmd_list->rd->s);
                    free(cmd_list->rd);
                    cmd_list->rd = redir_tmp;
                }
                
                // Free args
                if (cmd_list->args)
                {
                    for (int j = 0; cmd_list->args[j]; j++)
                        free(cmd_list->args[j]);
                    free(cmd_list->args);
                }
                
                // Free command fields
                if (cmd_list->cmd)
                    free(cmd_list->cmd);
                if (cmd_list->path)
                    free(cmd_list->path);
                
                free(cmd_list);
                cmd_list = cmd_tmp;
            }
        }

        // Handle signals after execution
        if (g_signal == SIGINT)
        {
            g_signal = 0;
            shell.exit_status = 130;
        }

        free_split(tokens);
        free(shell.in);
    }
    
    // Cleanup shell
    if (shell.envp)
    {
        for (int i = 0; shell.envp[i]; i++)
            free(shell.envp[i]);
        free(shell.envp);
    }
    
    return shell.exit_status;
}
