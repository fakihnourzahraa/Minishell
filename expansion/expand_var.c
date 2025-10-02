/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 18:57:15 by miwehbe           #+#    #+#             */
/*   Updated: 2025/10/02 19:52:36 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char  *get_exit_status_string(t_shell *shell)
{
  int status;
  char *str_status;

  if(!shell)
    return NULL;
  status = shell->exit_status;
  str_status = ft_itoa(status);
  if(!str_status)
    return NULL;
  return str_status;
}

char *expand_variable(t_shell *shell, const char *var_name)
{
  char *env_value;
  char *str_copy;

  if(!shell || !var_name)
    return (NULL);
  if(ft_strcmp(var_name,"?")==0)
    return get_exit_status_string(shell);
  env_value = get_env_value(shell->env,var_name);
  if(!env_value)
    return NULL;
  str_copy= ft_strdup(env_value);
  return(str_copy);
}