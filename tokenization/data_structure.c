/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:45:13 by nfakih            #+#    #+#             */
/*   Updated: 2025/09/24 18:54:30 by nour             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

int	set_single(int n, int i, char a, t_token *t)
{
	char	*b;

	b = malloc (sizeof(char) * 2);
	b[0] = a;
	b[1] = '\0';
	t->type = n;
	t->s = b;
	//printf("DEBUG: set_single created '%s' at address %p\n", b, b);
	return (i + 1);
}
int	set_double(int n, char a, t_token *t, int i)
{
	char	*b;

	b = malloc (sizeof(char) * 3);
	b[0] = a;
	b[1] = a;
	b[2] = '\0';
	t->type = n;
	t->s = b;
	return (i + 2);
}

void	empty_token(char *a, t_shell *shell, int i)
{
	char	*b;
	t_token	*t;

	b = malloc(sizeof(char));
	b[0] = '\0';
	t = init_token();
	if (!skipable_space(a[1 + i]))
		t->space = false;
	t->s = b;
	t->type = EMPTY;
	t->quotes = (a[i] == '\'') ? 1 : 2;
	add_token(shell, t);
}

int	split_q(char *a, t_shell *shell, int i)
{
	int	j;

	j = i + 1;
	while (a[j])
	{
		if (a[j] == a[i])
		{
			if (j == i + 1)
				return (i + 2);
			return (split_quote(a, i, shell, a[i]));
		}
		j++;
	}
	return (-1);
}
//this goes off of where the last index is, so either the original one if there are quotes
//or tokenizes whats between quotes, or -1 on error
//34 is " 39 is '
//shell->tkns->quotes = (a[z] % 3) + 1; is its single quote it'll be 0 + 1 else 1 + 1

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
}
t_cmd	*init_cmd(t_token *t)
{
	int		wc;
	int		i;
	t_cmd	*cmd;
	
	wc = word_count(t);
	cmd = malloc(sizeof(t_cmd));
	cmd->args = malloc(sizeof(char *) * (wc + 1));
	cmd->path =	NULL;
	cmd->rd = NULL;
	cmd->i_fd = STDIN_FILENO;   
	cmd->o_fd = STDOUT_FILENO; 
	cmd->pid = -1;
	cmd->builtin = NOT_BUILTIN;
	cmd->next = NULL;
	i = 0;
	while (i <= wc)
	{
		cmd->args[i] = NULL;
		i++;
	}
	// if (t->s == NULL)
	// {
	// 	cmd->args[0] = NULL;
	// 	cmd->cmd = NULL;
	// 	return (cmd);
	// }
	return (cmd);
}
