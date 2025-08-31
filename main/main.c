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
//#include "tools.h"
//#include "exec.h"
//#include "builtin.h"
void	init_shell(t_shell *a)
{
	a->env = NULL;
	a->tkns = NULL;
	a->cmds = NULL;
	a->in = NULL;
	a->envp = NULL;
	a->exit_status = 0;
	a->cwd = NULL;
}
int main()
{
	//int		i;
	t_shell	*a;

	signal(SIGINT,sigint_handler);//ctrl+c(sigint here is a signal and signit_han is fct)
	signal(SIGQUIT,SIG_IGN);//ctrl+\ (sigquit here is a signal and sif_in is a macro in os to ignore the signal)

	a = malloc(sizeof(t_shell));
	if(!a)
		return (1);
	init_shell(a);
	while(1)
	{
		a->in = readline("minishell$ ");
		if(!a->in)
			break;//ctrl+D
    if(a->in[0] != '\0')
      add_history(a->in);
		char **args = ft_split(a->in,' ');
		t_cmd cmd;
		cmd.args=args;
		if (args[0]) // make sure there is a command
    {
      if (is_builtin(args[0]))
        execute_builtin(&cmd, a);
      else
        printf("will execute external command tomorrow\n");
    }
    free_split(args);
		free(a->in);
	}
	free(a);
  return (0);
}