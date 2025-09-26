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
  fd = open_outfile(redir->s, 0);  // 0 = truncate mode
  return (redirect_fd(fd, STDOUT_FILENO));
}

static int handle_append_redir(t_redir *redir)
{
  int fd;

  if (!redir || !redir->s)
    return (-1);
  fd = open_outfile(redir->s, 1);  // 1 = append mode
  return (redirect_fd(fd, STDOUT_FILENO));
}

/*int apply_redirections(t_cmd *cmd, t_shell *shell)
{
  t_redir *current;
  char *heredoc_delimiters[100];
  int heredoc_count ;
  int final_input_fd ;
  heredoc_count = 0;
  final_input_fd = -1;
  if (!cmd)
    return (0);

  current = cmd->rd;
  while (current && heredoc_count < 100)
  {
    if (current->type == R_HEREDOC)
    {
      if (!current->s || ft_strlen(current->s) == 0)
      {
        //ft_putstr_fd("minishell: syntax error near unexpected token `<<'\n", 2);
        return (-1);
      }
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
    return (redirect_fd(final_input_fd, STDIN_FILENO));
  }
    
  return (0);
}*/

int apply_redirections(t_cmd *cmd, t_shell *shell)
{
    t_redir *current;
    int heredoc_fd = -1;
    
    if (!cmd)
        return (0);

    current = cmd->rd;
    
    // Handle non-heredoc redirections first
    while (current)
    {
        if (current->type == R_IN && handle_in_redir(shell, current) == -1)
            return (-1);
        else if (current->type == R_OUT && handle_out_redir(current) == -1)
            return (-1);
        else if (current->type == R_APPEND && handle_append_redir(current) == -1)
            return (-1);
        else if (current->type == R_HEREDOC)
        {
            // Process THIS command's heredoc only
            if (!current->s || ft_strlen(current->s) == 0)
                return (-1);
                
            // Run single heredoc for this command
            heredoc_fd = run_heredoc(current->s, shell);
            if (heredoc_fd == -1)
                return (-1);
                
            // Redirect this heredoc to stdin
            if (redirect_fd(heredoc_fd, STDIN_FILENO) == -1)
            {
                close(heredoc_fd);
                return (-1);
            }
            close(heredoc_fd);
        }
        current = current->next;
    }
    
    return (0);
}

int is_redirect_only_command(t_cmd *cmd)
{
  if (!cmd)
    return (0);
  if ((!cmd->cmd || ft_strlen(cmd->cmd) == 0) && cmd->rd)
    return (1);
        
  return (0);
} // If no command or empty command, but has redirections

int execute_redirect_only(t_cmd *cmd, t_shell *shell)
{
  int saved_stdin;
  int saved_stdout;;
  int result;
    
  if (!cmd || !cmd->rd)
    return (0);
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