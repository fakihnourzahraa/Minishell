/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:35:19 by miwehbe           #+#    #+#             */
/*   Updated: 2025/08/28 11:35:19 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"main.h"

int main()
{
  signal(SIGINT,sigint_handler);//ctrl+c(sigint here is a signal and signit_han is fct)
  signal(SIGQUIT,SIG_IGN);//ctrl+\ (sigquit here is a signal and sif_in is a macro in os to ignore the signal)
  char *line;

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