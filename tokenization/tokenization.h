/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:10:17 by nour              #+#    #+#             */
/*   Updated: 2025/09/25 22:27:02 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# include "../minishell.h"

// cc token.c token_helpers.c -lreadline

// int main()
// {
// 	t_shell *a;
// 	a = malloc(1);
//     char *b = readline("Enter text: ");
//     printf("%d\n", split_q(b, a, 0));
    
//     return 0;
// }

//int	main(int argc, char **argv, char **envp)
// {
// 	t_shell	*a;
// 	(void)argc;
// 	(void)argv;
// 	t_cmd	cmd;
// 	char	**args;

// 	a = malloc(sizeof(t_shell));
// 	if (!a)
// 		return (1);
// 	// init_shell(a,envp);
// 	while (1)
// 	{
// 		a->in = readline("minishell$ ");
// 		if (!a->in)
// 			break ;
// 		args = ft_split(a->in, ' ');
// 	}
// 	return (0);
// }

int	    skip_spaces(char *a, int i);
bool	skipable_space(char a);
int	    split_word(char *a, int i, t_shell *shell, t_token *n);
int		split_quote(char *a, int i, t_shell *shell, char n);
int		parse(t_shell *shell, t_token *t);
int	    tokenize_line(t_shell *shell);
t_token	*init_token(void);
void	add_token(t_shell *shell, t_token *n);
void	fill_r(t_token *t, t_cmd *cmd);
void	add_redir(t_cmd *cmd, t_redir *c);
int		set_single(int n, int i, char a, t_token *t);
int		set_double(int n, char a, t_token *t, int i);
int		split_q(char *a, t_shell *shell, int i);
void    TT(t_token_type type);
void    print_toke(t_token *token);
void	add_cmd(t_shell *shell, t_cmd *cmd);
t_cmd	*init_cmd(t_token *t);
int		word_count_p(t_token *token);
int		check_tkns(t_token *tkn);
int	word_count_p(t_token *token);
int	split_q(char *a, t_shell *shell, int i);
int	split_word(char *a, int i, t_shell *shell, t_token *n);
int	word_len_cmds(char *a, int i);
int	word_len(char *a, int i);
void	empty_token(char *a, t_shell *shell, int i);
void debug_parse_input(char *input, t_shell *shell);
void debug_print_cmds(t_cmd *cmds);
void debug_print_tokens(t_token *tokens);
#endif
