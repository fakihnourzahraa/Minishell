/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:04:47 by miwehbe           #+#    #+#             */
/*   Updated: 2025/08/29 13:31:44 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"


/*void  sigint_handler(int signum)
{
  (void)signum;
  write(1,"\n",1);
  rl_on_new_line();// tell readline we are on a new line
  rl_replace_line("",0); // clear current input
  rl_redisplay();// redraw prompt
}*/
int g_signal = 0;

void sigint_handler(int signum)
{
  g_signal = signum;  // just store the signal number
  write(1, "\n", 1);
}

void	signals_prompt(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	signals_child_heredoc(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_IGN);
}

void	signals_parent(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

//here we must found some leak but we are not responsible on it bcz the said this in the given