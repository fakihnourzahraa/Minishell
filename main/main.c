/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:30:14 by nfakih            #+#    #+#             */
/*   Updated: 2025/10/25 14:30:05 by nour             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

extern int	g_signal;

void	init_shell(t_shell *shell, char **envp)
{
	shell->env = init_env_from_envp(envp);
	shell->exit_status = 0;
	shell->in_h = 0;
	shell->exit = false;
	shell->tkns = NULL;
	shell->cmds = NULL;
	shell->in = NULL;
	shell->envp = NULL;
	shell->cwd = NULL;
	shell->sti = NULL;
	shell->sto = NULL;
	shell->quotes = NULL;
	update_shlvl_on_start(shell);
}

static int	handle_empty_input(t_shell *shell, char *input)
{
	if (g_signal == SIGINT && input[0] == '\0')
	{
		g_signal = 0;
		shell->exit_status = 130;
		return (1);
	}
	if (g_signal == SIGINT)
	{
		g_signal = 0;
		shell->exit_status = 130;
	}
	if (input[0] == '\0')
		return (1);
	return (0);
}

static void	execute_check_exit(t_shell *shell, char *input)
{
	add_history(input);
	process_input(shell, input);
	if (g_signal == SIGINT)
	{
		g_signal = 0;
		shell->exit_status = 130;
	}
	if (shell->exit)
		update_shlvl_on_exit(shell);
}

int	main_loop(t_shell *shell)
{
	char	*input;

	while (!shell->exit)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			update_shlvl_on_exit(shell);
			printf("exit\n");
			break ;
		}
		if (!handle_empty_input(shell, input))
			execute_check_exit(shell, input);
		free(input);
		if (shell->exit)
			break ;
	}
	return (shell->exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	int		exit_status;

	if (argc != 1)
	{
		ft_putstr_fd("minishell: unexpected arguements\n", 2);
		return (1);
	}
	(void)argv;
	init_shell(&shell, envp);
	signals_prompt();
	exit_status = main_loop(&shell);
	cleanup_shell(&shell);
	return (exit_status);
}
