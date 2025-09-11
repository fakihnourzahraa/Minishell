/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:34:12 by miwehbe           #+#    #+#             */
/*   Updated: 2025/09/11 22:08:49 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// Split into clean, small functions

static void handle_file_error(char *filename)
{
  perror(filename);
  exit(1);
}
//only used for file open errors
int handle_input_redirections(t_cmd *cmd, t_shell *shell)
{
  t_redir *redir;
  int input_fd;

  input_fd = STDIN_FILENO;
  redir = cmd->rd;
  while (redir)
  {
    if (redir->type == R_IN)
    {
      i        nput_fd = open(redir->s, O_RDONLY);
      if (input_fd < 0)
        handle_file_error(redir->s);
    }
    else if (redir->type == R_HEREDOC)
    {
      input_fd = run_heredoc(redir->s, shell);
      if (input_fd < 0)
        exit(130);
    }
    redir = redir->next;
  }
  return (input_fd);
}//for < || << open file or run herdoc and control the exit

int handle_output_redirections(t_cmd *cmd)
{
  t_redir *redir;
  int output_fd;

  output_fd = STDOUT_FILENO;
  redir = cmd->rd;
  while (redir)
  {
    if (redir->type == R_OUT)
      output_fd = open(redir->s, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if (redir->type == R_APPEND)
      output_fd = open(redir->s, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (output_fd < 0)
    {
      perror(redir->s);
      exit(1);
    }
    redir = redir->next;
  }
  return (output_fd);
}//check the > || >> open the output file

void connect_pipes(int *input_fd, int *output_fd, t_pipe_info *info)
{
  if (*input_fd == STDIN_FILENO && info->cmd_index > 0)
    *input_fd = info->pipes[info->cmd_index - 1][0];
  if (*output_fd == STDOUT_FILENO && info->cmd_index < info->cmd_count - 1)
    *output_fd = info->pipes[info->cmd_index][1];
}// it set the input from prev pipe,output to next pipe 

void setup_cmd_fds(t_cmd *cmd, t_pipe_info *info, t_shell *shell)
{
  int input_fd;
  int output_fd;

  input_fd = handle_input_redirections(cmd, shell);
  output_fd = handle_output_redirections(cmd);
  connect_pipes(&input_fd, &output_fd, info);
    
  if (input_fd != STDIN_FILENO)
  {
    dup2(input_fd, STDIN_FILENO);
    if (input_fd > 2)
      close(input_fd);
  }
  if (output_fd != STDOUT_FILENO)
  {
    dup2(output_fd, STDOUT_FILENO);
    if (output_fd > 2)
      close(output_fd);
  }
  close_all_pipes(info->pipes, info->cmd_count - 1);
}
