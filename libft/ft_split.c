/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:04:41 by miwehbe           #+#    #+#             */
/*   Updated: 2025/05/26 19:04:41 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*copy_word(const char *start, int len)
{
	char	*word;
	int		i;

	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = start[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	free_all(char **words, int i)
{
	while (i--)
		free(words[i]);
	free(words);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;
	int		word_index;
	int		start;
	int		len;

	i = 0;
	word_index = 0;
	if (!s)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!result)
		return (NULL);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			start = i;
			len = 0;
			while (s[i] && s[i] != c)
			{
				i++;
				len++;
			}
			result[word_index] = copy_word(s + start, len);
			if (!result[word_index])
			{
				free_all(result, word_index);
				return (NULL);
			}
			word_index++;
		}
	}
	result[word_index] = NULL;
	return (result);
}
