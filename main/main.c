/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:35:19 by miwehbe           #+#    #+#             */
/*   Updated: 2025/09/01 14:19:10 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"main.h"
//#include "tools.h"
//#include "exec.h"
//#include "builtin.h"
/*void	init_shell(t_shell *a)
{
	a->env = NULL;
	a->tkns = NULL;
	a->cmds = NULL;
	a->in = NULL;
	a->envp = NULL;
	a->exit_status = 0;
	a->cwd = NULL;
}*/
void	init_shell(t_shell *shell, char **envp)
{
	int	i;

	if (!shell)
		return ;
	shell->exit_status = 0;
	shell->in = NULL;

	// Count env variables
	i = 0;
	while (envp[i])
		i++;

	// Allocate and copy envp
	shell->envp = malloc(sizeof(char *) * (i + 1));
	if (!shell->envp)
		return ;
	i = 0;
	while (envp[i])
	{
		shell->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	shell->envp[i] = NULL;
}
void	free_shell(t_shell *shell)
{
	int	i;

	if (!shell)
		return ;
	if (shell->envp)
	{
		i = 0;
		while (shell->envp[i])
		{
			free(shell->envp[i]);
			i++;
		}
		free(shell->envp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*a;
	(void)argc;
	(void)argv;
	t_cmd	cmd;
	char	**args;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);

	a = malloc(sizeof(t_shell));
	if (!a)
		return (1);
	init_shell(a,envp);
	while (1)
	{
		a->in = readline("minishell$ ");
		if (!a->in)
			break ;
		if (a->in[0] != '\0')
			add_history(a->in);
		args = ft_split(a->in, ' ');
		if (!args)
		{
			free(a->in);
			continue ;
		}
		cmd.args = args;
		cmd.builtin = is_builtin(args[0]);
		if (args[0])
		{
			if (cmd.builtin != NOT_BUILTIN)
				execute_builtin(&cmd, a);
			else
				execute_single(a, &cmd);
		}
		free_split(args);
		free(a->in);
	}
	free_shell(a);
	free(a);
	return (0);
}