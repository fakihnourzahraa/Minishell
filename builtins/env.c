/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 19:09:19 by miwehbe           #+#    #+#             */
/*   Updated: 2025/09/10 19:09:19 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void    print_env_list(t_env *env)
{
  t_env   *current;

  current = env;
  while (current)
  {
    if (current->avail)
    {
      ft_putstr_fd(current->name, 1);
      ft_putchar_fd('=', 1);
      ft_putstr_fd(current->val, 1);
      ft_putchar_fd('\n', 1);
    }
    current = current->next;
  }
}

// Main builtin_env function
void    builtin_env(t_cmd *cmd, t_shell *shell)
{
  if (cmd->args[1] != NULL)
  {
    ft_putstr_fd("env: ", 2);
    ft_putstr_fd(cmd->args[1], 2);
    ft_putstr_fd(": No such file or directory\n", 2);
    shell->exit_status = 1;
    return;
  }
  print_env_list(shell->env);
  shell->exit_status = 0;
}
