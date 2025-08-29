/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:35:19 by miwehbe           #+#    #+#             */
/*   Updated: 2025/08/29 13:34:14 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"main.h"

void	init_shell(t_shell *a)
{
	a->env = NULL;
	a->tkns = NULL;
	a->cmds = NULL;
	a->in = NULL;
	a->envp = NULL;
	a->exit_status = NULL;
	a->cwd = NULL;
}
int main()
{
	t_shell	*a;
	signal(SIGINT,sigint_handler);//ctrl+c(sigint here is a signal and signit_han is fct)
	signal(SIGQUIT,SIG_IGN);//ctrl+\ (sigquit here is a signal and sif_in is a macro in os to ignore the signal)
	char *line;

	a = malloc(sizeof(t_shell));
	init_shell(a);
	while(1)//infinite loop bcz always should print minishell$
	{
		line = readline("minishell$ ");
		if(line == NULL)
			break;//ctrl+D
    	if(*line != '\0')
      		add_history(line);
    	free(line);
	}
  return (0);
}