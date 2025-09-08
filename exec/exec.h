/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:32:30 by miwehbe           #+#    #+#             */
/*   Updated: 2025/08/29 14:32:30 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
#define EXEC_H
#include "../minishell.h"
#include "../libft/libft.h"
#include "../builtins/builtin.h"
#include"../main/main.h"
#include<fcntl.h>

typedef struct s_pipe_info
{
  int **pipes;
  int cmd_index;
  int cmd_count;
} t_pipe_info;

int     is_builtin(char *cmd);
int     execute_builtin(t_cmd *cmd, t_shell *shell);
int     execute_single(t_shell *shell, t_cmd *cmd); 
char    *execute_path(char *cmd,t_shell *shell);
char    *get_cmd_path(const char *cmd, t_shell *shell);
void	  free_paths(char **paths);
int     open_infile(char *filename);
int     open_outfile(char *filename, int append);
int     redirect_fd(int fd, int target_fd);
int     apply_redirections(t_cmd *cmd, t_shell *shell);
int     run_heredoc(char *delimiter, t_shell *shell);
int     execute_pipeline(t_shell *shell, t_cmd *cmds);
int     **setup_pipes(int cmd_count);
void    close_all_pipes(int **pipes, int pipe_count);
int     count_commands(t_cmd *cmds);
void    wait_for_children(t_cmd *cmds,t_shell *shell);
void    close_unused_pipes(int **pipes, int pipe_count, int current_cmd);
int     execute_cmd_in_pipeline(t_shell *shell, t_cmd *cmd, t_pipe_info *info);
void    setup_cmd_fds(t_cmd *cmd, t_pipe_info *info,t_shell shell);
void    free_pipes(int **pipes, int pipe_count);
void    cleanup_pipes(int **pipes, int count);
int     create_single_pipe(int **pipes, int index);
int     handle_input_redirections(t_cmd *cmd, t_shell *shell);
int     handle_output_redirections(t_cmd *cmd);
int     execute_multiple_cmds(t_shell *shell, t_cmd *cmds, int cmd_count);
void    connect_pipes(int *input_fd, int *output_fd, t_pipe_info *info);
#endif
