/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 22:51:45 by miwehbe           #+#    #+#             */
/*   Updated: 2025/10/24 11:45:23 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	handle_command_not_found(t_shell *shell, t_cmd *cmd, t_pipe_info *info)
{
	pid_t	pid;

	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
	{
		signals_child();
		setup_cmd_fds(cmd, info, shell);
		cleanup_pipeline_child(shell);
		exit(127);
	}
	else
	{
		cmd->pid = pid;
		return (pid);
	}
}

static int	fork_and_execute(t_shell *shell, t_cmd *cmd, t_pipe_info *info)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		if (cmd->path)
		{
			free(cmd->path);
			cmd->path = NULL;
		}
		return (-1);
	}
	else if (pid == 0)
	{
		executes_child_process(shell, cmd, info);
		exit(1);
	}
	else
	{
		cmd->pid = pid;
		return (pid);
	}
}
// Add this debugging function to help identify the issue

void debug_print_cmd(t_cmd *cmd, const char *location)
{
    printf("\n=== DEBUG CMD at %s ===\n", location);
    
    if (!cmd)
    {
        printf("ERROR: cmd is NULL\n");
        return;
    }
    
    printf("cmd->cmd: %s\n", cmd->cmd ? cmd->cmd : "NULL");
    printf("cmd->builtin: %d\n", cmd->builtin);
    printf("cmd->args:\n");
    
    if (!cmd->args)
    {
        printf("  ERROR: args array is NULL\n");
    }
    else if (!cmd->args[0])
    {
        printf("  ERROR: args[0] is NULL\n");
    }
    else
    {
        int i = 0;
        while (cmd->args[i])
        {
            printf("  args[%d]: '%s'\n", i, cmd->args[i]);
            i++;
        }
        printf("  args[%d]: NULL (terminator)\n", i);
    }
    
    printf("cmd->path: %s\n", cmd->path ? cmd->path : "NULL");
    
    // Print redirections
    printf("Redirections:\n");
    t_redir *redir = cmd->rd;
    int count = 0;
    while (redir)
    {
        printf("  redir[%d]: type=%d, file='%s'\n", 
               count, redir->type, redir->s ? redir->s : "NULL");
        redir = redir->next;
        count++;
    }
    if (count == 0)
        printf("  (no redirections)\n");
    
    printf("=== END DEBUG ===\n\n");
}
int	execute_cmd_in_pipeline(t_shell *shell, t_cmd *cmd, t_pipe_info *info)
{
	if (cmd->builtin == NOT_BUILTIN && !ft_strchr(cmd->args[0], '/'))
	{
		cmd->path = get_cmd_path(cmd->args[0], shell);
		if (!cmd->path)
			return (handle_command_not_found(shell, cmd, info));
	}
	return (fork_and_execute(shell, cmd, info));
}
// int	execute_cmd_in_pipeline(t_shell *shell, t_cmd *cmd, t_pipe_info *info)
// {
//     // Add NULL checks
//     if (!cmd)
//     {
//         fprintf(stderr, "Error: NULL command in pipeline\n");
//         return (1);
//     }
    
//     debug_print_cmd(cmd, "execute_cmd_in_pipeline START");
    
//     // CRITICAL: Check if args[0] exists before accessing it
//     if (!cmd->args || !cmd->args[0])
//     {
//         fprintf(stderr, "Error: command has NULL args\n");
//         return (1);
//     }
    
//     // Only check for path if it's not a builtin and args[0] is valid
//     if (cmd->builtin == NOT_BUILTIN && !ft_strchr(cmd->args[0], '/'))
//     {
//         cmd->path = get_cmd_path(cmd->args[0], shell);
//         if (!cmd->path)
//             return (handle_command_not_found(shell, cmd, info));
//     }
    
//     return (fork_and_execute(shell, cmd, info));
// }

void	connect_pipes(int *input_fd, int *output_fd, t_pipe_info *info)
{
	if (*input_fd == STDIN_FILENO && info->cmd_index > 0)
		*input_fd = info->pipes[info->cmd_index - 1][0];
	if (*output_fd == STDOUT_FILENO && info->cmd_index < info->cmd_count - 1)
		*output_fd = info->pipes[info->cmd_index][1];
}
