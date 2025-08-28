/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:36:30 by miwehbe           #+#    #+#             */
/*   Updated: 2025/05/24 12:36:30 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*str;
	const unsigned char	*str1;

	str = (const unsigned char *)s1;
	str1 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (str[i] != str1[i])
			return ((int)(str[i] - str1[i]));
		i++;
	}
	return (0);
}

/*int main()
{
	char s[]="helloooo";
	char s1[]="hell";
	int result =ft_memcmp(s,s1,0);
	printf("%d",result);
}*/
