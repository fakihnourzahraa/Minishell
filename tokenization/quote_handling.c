/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:24:02 by nour              #+#    #+#             */
/*   Updated: 2025/09/04 13:35:58 by nour             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "tokenization.h"

int	split_q(char *a, t_shell *shell, int i)
{
	int	z;

	z = i;
	int	j = ft_strlen(a);
	while (a[z])
	{
		if (a[z] == 34 || a[z] == 39)
		{
			while (j > i)
			{
				if (a[j] == a[z])
				{
					split_word(a, a[z] % 3 + 1, shell);
					return (j);
				}
				j--;
			}
			return (-1);
		}
		z++;
	}
	return (i);
}
//this goes off of where the last index is, so either the original one if there are quotes
//or tokenizes whats between quotes, or -1 on error
//34 is " 39 is '
//shell->tkns->quotes = (a[z] % 3) + 1; is its single quote it'll be 0 + 1 else 1 + 1

// int main()
// {
//     // Fix: Use proper prompt or NULL instead of uninitialized pointer
//     char *b = readline("Enter text: ");  // or readline(NULL) for no prompt
//     printf("%d", assign_q(b, 0, strlen(b)));
    
//     return 0;
// }