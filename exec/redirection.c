/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:32:56 by miwehbe           #+#    #+#             */
/*   Updated: 2025/09/03 14:32:56 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int apply_redirections(t_cmd *cmd)
{
  if(cmd == NULL || cmd->rd == NULL)
    return (0);
  t_redir *current_redir;
  int fd;

  current_redir = cmd->rd;
  while(current_redir !=  NULL)
  {
    if (current_redir->type ==R_IN)
    {
      fd = open_infile(current_redir->s);
      if(fd == -1)
        return(-1);
      redirect_fd(fd,STDIN_FILENO);
    }
    else if(current_redir->type == R_OUT)
    {
      fd = open_outfile(current_redir->s,0);
      if (fd ==-1)
        return (-1);
      redirect_fd(fd,STDOUT_FILENO);
    }
    else if (current_redir->type ==R_APPEND)
    {
      fd= open_outfile(current_redir->s, 1);
      if(fd==-1)
        return(-1);
      redirect_fd(fd,STDOUT_FILENO);
    }
    current_redir = current_redir->next;
  }
  return (0);
}