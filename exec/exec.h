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
# define EXEC_H

# include "../minishell.h"
# include "../libft/libft.h"
# include "../builtins/builtin.h"
# include "../env/env.h"
# include "../main/main.h"
# include "../expansion/expansion.h"
# include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

typedef struct s_pipe_info
{
	int	**pipes;
	int	cmd_index;
	int	cmd_count;
}	t_pipe_info;

int		is_builtin(char *cmd);
int		needs_parent_execution(int builtin);
void	execute_builtin_dispatch(t_cmd *cmd, t_shell *shell);
int		save_and_redirect(t_cmd *cmd, t_shell *shell,
			int *stdin_fd, int *stdout_fd);
int		execute_with_redirect_parent(t_cmd *cmd, t_shell *shell);
int		execute_with_redirect_child(t_cmd *cmd, t_shell *shell);
int		execute_builtin(t_cmd *cmd, t_shell *shell);
int		execute_single(t_shell *shell, t_cmd *cmd);
char	*get_cmd_path(const char *cmd, t_shell *shell);
void	free_paths(char **paths);
void	exec_external_with_env(t_shell *shell, t_cmd *cmd, char *path);
int		open_infile(char *filename);
int		open_outfile(char *filename, int append);
int		redirect_fd(int fd, int target_fd);
int		apply_redirections(t_cmd *cmd, t_shell *shell);
int		run_heredoc(char *delimiter, t_shell *shell);
int		execute_pipeline(t_shell *shell, t_cmd *cmds);
int		**setup_pipes(int cmd_count);
void	close_all_pipes(int **pipes, int pipe_count);
void	close_and_free_pipes(int **pipes, int pipe_count);
int		count_commands(t_cmd *cmds);
void	wait_for_children(t_cmd *cmds, t_shell *shell);
void	close_unused_pipes(int **pipes, int pipe_count, int current_cmd);
int		execute_cmd_in_pipeline(t_shell *shell, t_cmd *cmd, t_pipe_info *info);
void	setup_cmd_fds(t_cmd *cmd, t_pipe_info *info, t_shell *shell);
void	free_pipes(int **pipes, int pipe_count);
void	cleanup_pipes(int **pipes, int count);
void	free_split(char **split);
int		create_single_pipe(int **pipes, int index);
int		handle_input_redirections(t_cmd *cmd, t_shell *shell);
int		handle_output_redirections(t_cmd *cmd);
int		execute_multiple_cmds(t_shell *shell, t_cmd *cmds, int cmd_count);
void	connect_pipes(int *input_fd, int *output_fd, t_pipe_info *info);
int		run_multiple_heredocs(char **delimiters, int delimiter_count,
			t_shell *shell);
void	cleanup_child_process(t_shell *shell);
void	cleanup_pipeline_child(t_shell *shell);
int		is_redirect_only_command(t_cmd *cmd);
int		process_heredocs(t_cmd *cmd, t_shell *shell);
int		execute_redirect_only(t_cmd *cmd, t_shell *shell);
int		run_heredoc_internal(char **delims, int count, t_shell *shell);
void	heredoc_child(int write_fd, char **delims, int count, t_shell *shell);
void	wait_child(t_shell *shell, int status);
char	**prepare_child_execution(t_shell *shell, t_cmd *cmd);
void	exec_external_child(t_shell *shell, t_cmd *cmd);
int		check_command_access(const char *cmd);
int		handle_absolute_path(t_shell *shell, t_cmd *cmd);
int		handle_command_path(t_shell *shell, t_cmd *cmd, char **path);
bool	is_valid_var_name(char *str, int len);
int		handle_variable_assignment(t_shell *shell, t_cmd *cmd);
int		handle_in_redir(t_shell *shell, t_redir *redir);
int		handle_out_redir(t_redir *redir);
int		handle_append_redir(t_redir *redir);
int		apply_output_redirections(t_cmd *cmd);
int		save_std_fds(int *saved_stdin, int *saved_stdout);
void	cleanup_and_wait(t_shell *shell, t_cmd *cmds, t_pipe_info *info);
int		execute_all_commands(t_shell *shell, t_cmd *cmds, t_pipe_info *info);
void	executes_child_process(t_shell *shell, t_cmd *cmd, t_pipe_info *info);
void	handle_file_error(char *filename);

#endif
