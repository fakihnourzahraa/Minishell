/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 13:12:23 by miwehbe           #+#    #+#             */
/*   Updated: 2025/09/13 13:12:23 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void swap_env(t_env **a, t_env **b)
{
  t_env *tmp = *a;
  *a = *b;
  *b = tmp;
}

int collect_exported_vars(t_shell *shell, t_env **arr)
{
  t_env *curr;
  int count = 0;

  curr = shell->env;
  while (curr)
  {
    if (curr->avail)
      arr[count++] = curr;
    curr = curr->next;
  }
  return count;
}

void sort_exported_vars(t_env **arr, int count)
{
  int i;
  int j;

  i = 0;
  while (i < count - 1)
  {
    j = 0;
    while (j < count - i - 1)
    {
      if (ft_strcmp(arr[j]->name, arr[j + 1]->name) > 0)
          swap_env(&arr[j], &arr[j + 1]);
      j++;
    }
    i++;
  }
}

int is_valid_identifier(const char *str)
{
  int i ;

  if(!str || str[0] =='\0')
    return (0);
  if(!ft_isalpha(str[0]) && str[0] != '_')
    return (0);
  i =1;
  while(str[i])
  {
    if(!ft_isalnum(str[i]) && str[i] != '_')
      return (0);
    i++;
  }
  return (1);
}
