/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:29:45 by miwehbe           #+#    #+#             */
/*   Updated: 2025/08/27 17:29:45 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int ft_strcmp(const char *s1, const char *s2)
{
  int i;

  i = 0;
  while (s1[i] && s2[i])
  {
    if ((unsigned char)s1[i] != (unsigned char)s2[i])
      return ((unsigned char)s1[i] - (unsigned char)s2[i]);
    i++;
  }
  return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
