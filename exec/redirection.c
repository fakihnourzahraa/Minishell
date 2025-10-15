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


static int handle_in_redir(t_shell *shell, t_redir *redir)
{
  int fd;

  (void)shell;
  if (!redir || !redir->s)
    return (-1);
  fd = open_infile(redir->s);
  return (redirect_fd(fd, STDIN_FILENO));
}

static int handle_out_redir(t_redir *redir)
{
  int fd;

  if (!redir || !redir->s)
    return (-1);
  fd = open_outfile(redir->s, 0);
  return (redirect_fd(fd, STDOUT_FILENO));
}

static int handle_append_redir(t_redir *redir)
{
  int fd;

  if (!redir || !redir->s)
    return (-1);
  fd = open_outfile(redir->s, 1);
  return (redirect_fd(fd, STDOUT_FILENO));
}

/*int apply_redirections(t_cmd *cmd, t_shell *shell)
{
  t_redir *current;
  char *heredoc_delimiters[100];
  int heredoc_count = 0;
  int final_input_fd = -1;
  
  if (!cmd)
    return (0);
  current = cmd->rd;  
  while (current && heredoc_count < 100)
  {
    if (current->type == R_HEREDOC)
    {
      if (!current->s || ft_strlen(current->s) == 0)
        return (-1);
      heredoc_delimiters[heredoc_count] = current->s;
      heredoc_count++;
    }
    current = current->next;
  }
  
  current = cmd->rd;
  while (current)
  {
    if (current->type == R_IN && handle_in_redir(shell, current) == -1)
      return (-1);
    else if (current->type == R_OUT && handle_out_redir(current) == -1)
      return (-1);
    else if (current->type == R_APPEND && handle_append_redir(current) == -1)
      return (-1);
    current = current->next;
  }
  if (heredoc_count > 0)
  {
    final_input_fd = run_multiple_heredocs(heredoc_delimiters, heredoc_count, shell);
	if (final_input_fd == -1)
      return (-1);
    if (redirect_fd(final_input_fd, STDIN_FILENO) == -1)
    {
      close(final_input_fd);
      return (-1);
    }
    close(final_input_fd);
  }
  return (0);
}*/

int apply_redirections(t_cmd *cmd, t_shell *shell)
{
  t_redir *current;
  
  if (!cmd)
    return (0);
  
  // Process output redirections first
  current = cmd->rd;
  while (current)
  {
    if (current->type == R_OUT && handle_out_redir(current) == -1)
      return (-1);
    else if (current->type == R_APPEND && handle_append_redir(current) == -1)
      return (-1);
    current = current->next;
  }
  
  // Process input redirections (files only, NOT heredocs)
  current = cmd->rd;
  while (current)
  {
    if (current->type == R_IN && handle_in_redir(shell, current) == -1)
      return (-1);
    current = current->next;
  }
  
  // Handle pre-processed heredoc (if cmd->i_fd was set by execute_single)
  if (cmd->i_fd > 0)
  {
    if (redirect_fd(cmd->i_fd, STDIN_FILENO) == -1)
    {
      close(cmd->i_fd);
      return (-1);
    }
    // redirect_fd already closes the fd, so don't close it again
  }
  
  return (0);
}

/*int apply_redirections(t_cmd *cmd, t_shell *shell)
{
    t_redir *current;
    
    if (!cmd)
        return (0);
    
    current = cmd->rd;
    while (current)
    {
        if (current->type == R_OUT && handle_out_redir(current) == -1)
            return (-1);
        else if (current->type == R_APPEND && handle_append_redir(current) == -1)
            return (-1);
        current = current->next;
    }
    current = cmd->rd;
    while (current)
    {
        if (current->type == R_IN && handle_in_redir(shell, current) == -1)
            return (-1);
        current = current->next;
    }
    if (cmd->i_fd != -1)
    {
        if (redirect_fd(cmd->i_fd, STDIN_FILENO) == -1)
        {
            close(cmd->i_fd);
            return (-1);
        }
        close(cmd->i_fd);
    }
    
    return (0);
}
*/
int is_redirect_only_command(t_cmd *cmd)
{
  if (!cmd)
    return (0);
  if ((!cmd->cmd || ft_strlen(cmd->cmd) == 0) && cmd->rd)
    return (1);
        
  return (0);
}

int execute_redirect_only(t_cmd *cmd, t_shell *shell)
{
  int saved_stdin;
  int saved_stdout;;
  int result;

  if (!cmd || !cmd->rd)
    {
        return (0);
    }
  saved_stdin = dup(STDIN_FILENO);
  saved_stdout = dup(STDOUT_FILENO);
    
  if (saved_stdin == -1 || saved_stdout == -1)
  {
    if (saved_stdin != -1) 
      close(saved_stdin);
    if (saved_stdout != -1)
      close(saved_stdout);
    return (-1);
  }
  result = apply_redirections(cmd, shell);

  dup2(saved_stdin, STDIN_FILENO);
  dup2(saved_stdout, STDOUT_FILENO);
  close(saved_stdin);
  close(saved_stdout);
    
  return (result);
}