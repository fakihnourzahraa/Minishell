/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:36:28 by miwehbe           #+#    #+#             */
/*   Updated: 2025/09/09 09:36:28 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void close_unused_pipes(int **pipes, int pipe_count, int current_cmd)//5
{
	int i;

	i = 0;
	if(!pipes)
		return ;
	while(i < pipe_count)
	{
		if(current_cmd == 0 || i != current_cmd-1)
			close(pipes[i][0]);//if it is first cmnd 
		if(current_cmd == pipe_count || i != current_cmd)
			close(pipes[i][1]);//if it is the last cmnd or 
		i++;
	}
}

static void execute_child_process(t_shell *shell, t_cmd *cmd, t_pipe_info *info)
{
    signals_child();
    setup_cmd_fds(cmd, info, shell);//decide if it will read < << or write >> >
    close_unused_pipes(info->pipes, info->cmd_count - 1, info->cmd_index);
    
    if (cmd->builtin != NOT_BUILTIN)
    {
        execute_builtin(cmd, shell);//if they are builtin they run directly
        exit(shell->exit_status);//after run we should exit correctly
    }
    else
    {
        cmd->path = get_cmd_path(cmd->args[0], shell);
        if (!cmd->path)
        {
            printf("minishell: %s: command not found\n", cmd->args[0]);
            exit(127);
        }
        exec_external_with_env(shell, cmd, cmd->path);
    }
}


int execute_cmd_in_pipeline(t_shell *shell, t_cmd *cmd, t_pipe_info *info)
{
    pid_t pid;

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return (-1);
    }
    else if (pid == 0)
    {
        execute_child_process(shell, cmd, info);
        exit(1); // This line will never be reached, but satisfies compiler
    }
    else
    {
        cmd->pid = pid;
        return (pid);
    }
}

void connect_pipes(int *input_fd, int *output_fd, t_pipe_info *info)
{
  if (*input_fd == STDIN_FILENO && info->cmd_index > 0)
    *input_fd = info->pipes[info->cmd_index - 1][0];
  if (*output_fd == STDOUT_FILENO && info->cmd_index < info->cmd_count - 1)
    *output_fd = info->pipes[info->cmd_index][1];
}
