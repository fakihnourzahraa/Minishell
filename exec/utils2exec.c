/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 12:58:43 by miwehbe           #+#    #+#             */
/*   Updated: 2025/09/07 12:58:43 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void cleanup_pipes(int **pipes, int count)
{
  int j;

  j = 0;
  while (j < count)
  {
    free(pipes[j]);//free the old pipe
    j++;
  }
  free(pipes);//then the array itself
}

int create_single_pipe(int **pipes, int index)
{
  pipes[index] = malloc(sizeof(int) * 2);
  if (!pipes[index])
    return (-1);
  if (pipe(pipes[index]) == -1)//== pipe(pipefd) ie pipes[i][0]=pipefd[0]
  {
    perror("pipe");
    free(pipes[index]);
    return (-1);
  }
  return (0);
}
