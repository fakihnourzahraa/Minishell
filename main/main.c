/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:35:19 by miwehbe           #+#    #+#             */
/*   Updated: 2025/08/29 14:46:36 by nfakih           ###   ########.fr       */
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
	int		i;
	t_shell	*a;
	signal(SIGINT,sigint_handler);//ctrl+c(sigint here is a signal and signit_han is fct)
	signal(SIGQUIT,SIG_IGN);//ctrl+\ (sigquit here is a signal and sif_in is a macro in os to ignore the signal)

	a = malloc(sizeof(t_shell));
	i = 0;
	init_shell(a);
	while(1)//infinite loop bcz always should print minishell$
	{
		a->in[i] = readline("minishell$ ");
		if(a->in[i] == NULL)
			break;//ctrl+D
    	if(a->in[i] != '\0')
      		add_history(a->in[i]);
    	i++;
	}
  return (0);
}