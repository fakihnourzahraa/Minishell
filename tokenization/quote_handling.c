/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:24:02 by nour              #+#    #+#             */
/*   Updated: 2025/09/04 16:07:21 by nour             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "tokenization.h"

int	split_q(char *a, t_shell *shell, int i)
{
	int	z;
	int	j;

	z = i;

	j = z + 1;
	while (a[j])
	{
		if (a[j] == a[z])
		{
			split_word(a, z, shell, a[z] % 3 + 1);
			return (j);
		}
		j++;
	}
	return (-1);
}
//this goes off of where the last index is, so either the original one if there are quotes
//or tokenizes whats between quotes, or -1 on error
//34 is " 39 is '
//shell->tkns->quotes = (a[z] % 3) + 1; is its single quote it'll be 0 + 1 else 1 + 1

int main()
{
	t_shell *a;
	a = malloc(1);
    char *b = readline("Enter text: ");
    printf("%d\n", split_q(b, a, 0));
    
    return 0;
}

//int	main(int argc, char **argv, char **envp)
// {
// 	t_shell	*a;
// 	(void)argc;
// 	(void)argv;
// 	t_cmd	cmd;
// 	char	**args;

// 	a = malloc(sizeof(t_shell));
// 	if (!a)
// 		return (1);
// 	// init_shell(a,envp);
// 	while (1)
// 	{
// 		a->in = readline("minishell$ ");
// 		if (!a->in)
// 			break ;
// 		args = ft_split(a->in, ' ');
// 	}
// 	return (0);
// }