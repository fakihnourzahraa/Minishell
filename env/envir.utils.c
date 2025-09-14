/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envir.utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 23:07:15 by miwehbe           #+#    #+#             */
/*   Updated: 2025/09/11 23:07:15 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void free_env_list(t_env *env)
{
  t_env *next;

  while (env)
  {
    next = env->next;
    free(env->name);
    free(env->val);
    free(env);
    env = next;
  }
}

void free_envp(char **envp)
{
  int i;

  if (!envp)
    return;
  i = 0;
  while (envp[i])
  {
    free(envp[i]);
    i++;
  }
  free(envp);
}
