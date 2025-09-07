/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsexec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:59:33 by miwehbe           #+#    #+#             */
/*   Updated: 2025/09/01 13:59:33 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_paths(char **paths)
{
	int	i;

	if (!paths)
		return ;
	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

void free_pipes(int **pipes, int pipe_count)//3
{
	int i;

	if(!pipes)
		return ;
	i = 0;
	while(i<pipe_count)
	{
		if(pipes[i] != NULL)
			free(pipes[i]);
		i++;
	}
	free(pipes);
}

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

/*void setup_cmd_fds(t_cmd *cmd, t_pipe_info *info)//6
{

}

int execute_cmd_in_pipeline(t_shell *shell, t_cmd *cmd, t_pipe_info *info)//8
{

}*/