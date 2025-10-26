/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 19:01:33 by miwehbe           #+#    #+#             */
/*   Updated: 2025/10/26 23:43:40 by nour             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H
# include "../minishell.h"
# include "../libft/libft.h"
# include "../env/env.h"

typedef struct s_expand_data
{
	char	*result;
	char	*new_var;
	int		i;
	int		old_len;
}	t_expand_data;

char	*get_exit_status_string(t_shell *shell);
char	*expand_variable(t_shell *shell, const char *var_name);
void	iterate_expansion(t_shell *shell);
int		expand_at(char *s, int i, char *q, bool h);
char	*expand_and_trim(t_shell *shell, char *var);
char	*trim_expand(t_shell *shell, int i, int old_len, char *s);
char	*trim_vars(char *s, int *i, int old_len, char *new_var);
char	*trim_vars_fq(char *s, int i, int j);
char	*trim(char *a);
void	quoted(char *a, char *b, int *i, int *j);
void	unquoted(char *a, char *b, int *i, int *j);
char	set_a(char a, char s);
void	handle_expansion(t_shell *shell, t_expand_data *data);
char	set_a(char a, char s);
char	*trim_expand(t_shell *shell, int i, int old_len, char *s);
char	*expand(t_shell *shell, char *s, bool h);
void	write_expanded_line(int write_fd, char *line, t_shell *shell);
int		count_args(char **args);
int		copy_args_segments(char **new_args, char **old_args,
			char **split, int i);
int		split_argss(t_shell *shell, t_cmd **current, int i);
#endif