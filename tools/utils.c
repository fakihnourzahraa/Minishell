/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 20:13:56 by miwehbe           #+#    #+#             */
/*   Updated: 2025/08/29 20:13:56 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"
#include <stdlib.h>

void free_split(char **split)
{
  int i ;

  i = 0;
  if (!split)
    return ;
  while (split[i])
  {
    free(split[i]);
    i++;
  }
  free(split);
}
