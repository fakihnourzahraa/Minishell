/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:29:30 by miwehbe           #+#    #+#             */
/*   Updated: 2025/09/11 21:29:30 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strndup(const char *s, size_t n)
{
  char    *dup;
  size_t  i;

  dup = malloc(n + 1);
  if (!dup)
    return (NULL);
  i = 0;
  while (i < n && s[i])
  {
    dup[i] = s[i];
    i++;
  }
  dup[i] = '\0';
  return (dup);
}
