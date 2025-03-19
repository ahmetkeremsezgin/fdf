/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:43:50 by asezgin           #+#    #+#             */
/*   Updated: 2025/03/19 08:25:16 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int	word_count(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static char	*get_word(char const *s, char c, int *i)
{
	char	*word;
	int		j;
	int		start;

	while (s[*i] == c)
		(*i)++;
	start = *i;
	while (s[*i] && s[*i] != c)
		(*i)++;
	word = (char *)malloc(sizeof(char) * (*i - start + 1));
	if (!word)
		return (NULL);
	j = 0;
	while (start < *i)
		word[j++] = s[start++];
	word[j] = '\0';
	return (word);
}

static char	**allocate_result(int words)
{
	char	**result;

	result = (char **)malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	return (result);
}

static int	fill_words(char **result, char const *s, char c, int words)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < words)
	{
		result[j] = get_word(s, c, &i);
		if (!result[j])
		{
			while (j > 0)
				free(result[--j]);
			free(result);
			return (0);
		}
		j++;
	}
	result[j] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		words;

	if (!s)
		return (NULL);
	words = word_count(s, c);
	result = allocate_result(words);
	if (!result)
		return (NULL);
	if (!fill_words(result, s, c, words))
		return (NULL);
	return (result);
}
