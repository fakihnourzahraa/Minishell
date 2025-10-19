/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:30:14 by nfakih            #+#    #+#             */
/*   Updated: 2025/10/18 16:21:39 by nfakih           ###   ########.fr       */
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
	update_shlvl_on_start(shell);
}

void	cleanup_in_shell(t_shell *shell)
{
	if (shell->in)
	{
		free(shell->in);
		shell->in = NULL;
	}
	if (shell->cwd)
	{
		free(shell->cwd);
		shell->cwd = NULL;
	}
	if (shell->sti)
	{
		free(shell->sti);
		shell->sti = NULL;
	}
	if (shell->sto)
	{
		free(shell->sto);
		shell->sto = NULL;
	}
}

void	cleanup_shell(t_shell *shell)
{
	if (!shell)
		return ;
	cleanup_t(shell);
	cleanup_p(shell);
	cleanup_in_shell(shell);
	if (shell->env)
	{
		free_env_list(shell->env);
		shell->env = NULL;
	}
	if (shell->envp)
	{
		free_envp(shell->envp);
		shell->envp = NULL;
	}
	rl_clear_history();
}

<<<<<<< HEAD
void mira_execution(t_shell *shell)
{
    int cmd_num;
    t_cmd *cmd_chain;

    cmd_num = 0;
    cmd_chain = shell->cmds;
    if (!cmd_chain)
        return;
    t_cmd *current = cmd_chain;
    while (current)
    {
        if (current->cmd)
            current->builtin = is_builtin(current->cmd);
        else
            current->builtin = NOT_BUILTIN;
        
        current = current->next;
        cmd_num++;
    }
    if (cmd_chain->next)
    {
        execute_pipeline(shell, cmd_chain);
    }
    else
    {
        if (is_redirect_only_command(cmd_chain))
        {
            execute_redirect_only(cmd_chain, shell);
        }
        else
        {
            execute_single(shell, cmd_chain);
        }
    }
=======
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
		if (g_signal == SIGINT && input[0] == '\0')
		{
			g_signal = 0;
			shell->exit_status = 130;
			free(input);
			continue ;
		}
		if (g_signal == SIGINT)
			g_signal = 0;
		if (input[0] == '\0')
		{
			free(input);
			continue ;
		}
		add_history(input);
		process_input(shell, input);
		if (g_signal == SIGINT)
		{
			g_signal = 0;
			shell->exit_status = 130;
		}
		if (shell->exit)
		{
			update_shlvl_on_exit(shell);
			free(input);
			break ;
		}
		free(input);
	}
	return (shell->exit_status);
>>>>>>> ed47752448a758e0a7afa5611564b10256ccfb83
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
