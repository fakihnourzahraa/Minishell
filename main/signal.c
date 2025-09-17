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

int g_signal = 0;

/*void sigint_handler(int signum)
{
    (void)signum;
    printf("DEBUG: Signal handler called!\n");
    g_signal = SIGINT;

    rl_replace_line("", 0); // clear current input line
    rl_on_new_line();       // move cursor to new line
    rl_redisplay();         // redraw the prompt immediately
}*/

void sigint_handler(int signum)
{
    (void)signum;
    
    g_signal = SIGINT;
    
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    //rl_redisplay();
}
void signals_prompt(void)
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
}

void signals_child_heredoc(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
}

void signals_parent(void)
{
    signal(SIGINT, SIG_IGN);    // Ignore Ctrl+C during child execution
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
}
void signals_child(void)
{
    signal(SIGINT, SIG_DFL);   // Default behavior for Ctrl+C
    signal(SIGQUIT, SIG_DFL);  // Default behavior for Ctrl+
}