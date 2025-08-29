/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buitl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:32:24 by miwehbe           #+#    #+#             */
/*   Updated: 2025/08/29 14:32:24 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int is_builtin(char *cmd)
{
  if (cmd ==NULL)
    return(NOT_BUILTIN);
  if (strcmp(cmd,"echo") == 0)
    return (BUILTIN_ECHO);
  if (ft_strcmp(cmd,"pwd") == 0)
    return (BUILTIN_PWD);
  if(ft_strcmp(cmd,"exit") == 0)
    return (BUILTIN_EXIT);
  return (0);
}