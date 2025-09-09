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

void free_split(char **split)
{
  int i ;

  i = 0;
  if (!split)
    return ;
  while (split[i])
  {
    free(split[i]);
    i++;
  }
  free(split);
}
