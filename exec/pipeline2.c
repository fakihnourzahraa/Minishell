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

static void handle_file_error(char *filename)
{
  perror(filename);
  exit(1);
}

int handle_input_redirections(t_cmd *cmd, t_shell *shell)
{
  t_redir *redir;
  int input_fd;
  int temp_fd;
  
  (void)shell;
  if (cmd->i_fd > 0)
    return cmd->i_fd;
  input_fd = STDIN_FILENO;
  redir = cmd->rd;
  
  while (redir)
  { 
    if (redir->type == R_IN)
    {
      temp_fd = input_fd;
      input_fd = open(redir->s, O_RDONLY);
      if (input_fd < 0)
        handle_file_error(redir->s);
      if (temp_fd != STDIN_FILENO && temp_fd > 2)
        close(temp_fd);
    }
    else if (redir->type == R_HEREDOC)
    {
      temp_fd = input_fd;
      input_fd = run_heredoc(redir->s, shell);
      if (input_fd < 0)
        exit(130);
      if (temp_fd != STDIN_FILENO && temp_fd > 2)
        close(temp_fd);
    }
    redir = redir->next;
  }
  return (input_fd);
}


int handle_output_redirections(t_cmd *cmd)
{
  t_redir *redir;
  int output_fd;
  int temp_fd;

  output_fd = STDOUT_FILENO;
  redir = cmd->rd;
  while (redir)
  {
    if (redir->type == R_OUT)
    {
      temp_fd = output_fd;
      output_fd = open(redir->s, O_WRONLY | O_CREAT | O_TRUNC, 0644);
      if (output_fd < 0)
      {
        perror(redir->s);
        exit(1);
      }
      if (temp_fd != STDOUT_FILENO && temp_fd > 2)
        close(temp_fd);
    }
    else if (redir->type == R_APPEND)
    {
      temp_fd = output_fd;
      output_fd = open(redir->s, O_WRONLY | O_CREAT | O_APPEND, 0644);
      if (output_fd < 0)
      {
        perror(redir->s);
        exit(1);
      }
      if (temp_fd != STDOUT_FILENO && temp_fd > 2)
        close(temp_fd);
    }
    redir = redir->next;
  }
  return (output_fd);
}


void setup_cmd_fds(t_cmd *cmd, t_pipe_info *info, t_shell *shell)
{
  int input_fd;
  int output_fd;

  input_fd = handle_input_redirections(cmd, shell);
  output_fd = handle_output_redirections(cmd);
  
  if (info)
    connect_pipes(&input_fd, &output_fd, info);
  if (input_fd != STDIN_FILENO)
  {
    if (dup2(input_fd, STDIN_FILENO) == -1)
    {
      perror("dup2 input");
      if (input_fd > 2)
        close(input_fd);
      exit(1);
    }
    if (input_fd > 2)
      close(input_fd);
  }
  
  if (output_fd != STDOUT_FILENO)
  {
    if (dup2(output_fd, STDOUT_FILENO) == -1)
    {
      perror("dup2 output");
      if (output_fd > 2)
        close(output_fd);
      exit(1);
    }
    if (output_fd > 2)
      close(output_fd);
  }
  if (info)
    close_unused_pipes(info->pipes, info->cmd_count - 1, info->cmd_index);
}

void exec_external_with_env(t_shell *shell, t_cmd *cmd, char *path)
{
  char **envp_array;

  envp_array = env_to_envp(shell->env);
  if (!envp_array)
  {
    free(path);
    cleanup_pipeline_child(shell);
    exit(1);
  }
  execve(path, cmd->args, envp_array);
  perror("execve");
  free_envp(envp_array);
  free(path);
  cleanup_pipeline_child(shell);
  exit(127);
}
