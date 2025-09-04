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
#include<fcntl.h>

int     is_builtin(char *cmd);
int     execute_builtin(t_cmd *cmd, t_shell *shell);
int     execute_single(t_shell *shell, t_cmd *cmd); 
char    *execute_path(char *cmd,t_shell *shell);
char    *get_cmd_path(const char *cmd, t_shell *shell);
void	  free_paths(char **paths);
int     open_infile(char *filename);
int     open_outfile(char *filename, int append);
int     redirect_fd(int fd, int target_fd);
int     apply_redirections(t_cmd *cmd);
#endif
