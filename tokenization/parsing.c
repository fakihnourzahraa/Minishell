/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 22:53:52 by nour              #+#    #+#             */
/*   Updated: 2025/09/13 15:23:36 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "tokenization.h"

int	word_count(t_token *token)
{
	int		i;

	i = 0;
	while (token && token->type != T_EOF && token->type != PIPE)
	{
		if (token->type == WORD)
			i++;
		token = token->next;
	}
	return (i);
}
void	add_cmd(t_shell *shell, t_cmd *cmd)
{
	t_cmd	*cur;

	if (!shell->cmds)
		shell->cmds = cmd;
	else
	{
		cur = shell->cmds;
		while (cur->next)
			cur = cur->next;
		cur->next = cmd;
	}
	    printf("Added command: %s\n", cmd->cmd); 
}
t_cmd	*init_cmd(t_shell *shell, t_token *t)
{
	int	wc;
	t_cmd	*cmd;
	
	wc = word_count(t);
	cmd = malloc(sizeof(t_cmd));
	cmd->args = malloc(sizeof(char *) * (wc + 1));
	cmd->path =	NULL;
	cmd->rd = NULL;
	cmd->i_fd =	-1;
	cmd->o_fd = -1;
	cmd->pid = -1;
	cmd->builtin = (t_builtin)NULL;
	cmd->next = NULL;
	return (cmd);
}

void	cleanup_parsing(t_shell *shell)
{
	t_cmd *c;
	int		i;

	i = 0;
	while (shell->cmds)
	{
		while (shell->cmds->args)
		{
			while (shell->cmds->args[i])
			{
				free(shell->cmds->args[i]);
				i++;
			}
			free(shell->cmds->args);
		}
		c = shell->cmds;
		shell->cmds = shell->cmds->next;
		free(c);
	}
}
void TT(t_token_type type)
{
    switch(type) {
        case WORD: printf("WORD"); break;
        case PIPE: printf("PIPE"); break;
        case IN: printf("IN"); break;
        case OUT: printf("OUT"); break;
        case APPEND: printf("APPEND"); break;
        case HEREDOC: printf("HEREDOC"); break;
        case T_EOF: printf("T_EOF"); break;
        default: printf("UNKNOWN"); break;
    }
}
void print_toke(t_token *token)
{
    t_token *current = token;
    int i = 0;
    
    printf("\n--- TOKENS ---\n");
    while (current)
    {
        printf("Token %d: ", i++);
        TT(current->type);
        printf(" | Content: '%s' | Quotes: %d\n", 
               current->s ? current->s : "(null)", 
               current->quotes);
        if (current->type == T_EOF)
            break;
        current = current->next;
    }
    printf("--- END TOKENS ---\n\n");
}
void	parse(t_shell *shell, t_token *token)
{
	int		i;
	t_cmd	*cmd;
	printf("IN PARSING");
	print_toke(token);

	if (!token || token->type != WORD)
		return ;
	cmd = init_cmd(shell, token);
	cmd->cmd = ft_strdup(token->s);
	cmd->args[0] = ft_strdup(token->s);
	i = 1;
	token = token->next;
	while (token && token->type != T_EOF)
	{
		if(token->type == WORD)
		{
			if (token->quotes == 1)
				cmd->args[i] = ft_strtrim(token->s, "'");
			else if (token->quotes == 2)
				cmd->args[i] = ft_strtrim(token->s, "\"");
			else
				cmd->args[i] = ft_strdup(token->s);
			i++;
		}
		else if (token->type == PIPE)
		{
			cmd->args[i] = NULL;
			add_cmd(shell, cmd);
			parse(shell, token->next);
			return ;
		}
		else
		{
			fill_r(token, shell);
			token = token->next;
		}
		if (token)
			token = token->next;
	}
	cmd->args[i] = NULL;
	add_cmd(shell, cmd);
}
//extra token.next so it skips filename

//parses till eof only

//should take the first token
// typedef struct s_cmd
// {
// 	char	*cmd;
// 	char	**args;
// 	char	*path;
// 	t_redir	*rd;
// 	int		i_fd;
// 	int		o_fd;
// 	pid_t	pid;
// 	t_builtin builtin;
// 	t_cmd	*next;
// }			t_cmd;
//rd: redirections
//i_fd: input fd
//o_fd: output fd
//pid: so we can wait on it later