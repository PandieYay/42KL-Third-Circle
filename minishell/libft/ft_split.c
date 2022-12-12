/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 11:50:20 by jakoh             #+#    #+#             */
/*   Updated: 2022/04/08 11:50:43 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		count_words(char const *s, char c);
char	*ft_substr(char const *s, size_t start, size_t len);
void	put_words(char **splits, char const *s, char c);
char	*sub_strs(char const *s, int start, int end);
void	sub_split(char **split, char const *s, char c);

// In the main function i malloc the array size
// Checks for NULL in string and malloc
// and call sub_split
// sub_split finds the head and tail of the word
// and calls sub_strs
// sub_strs returns the word as string
// and in sub_splits it appends to the the array char **splits
char	**ft_split(char const *s, char c)
{
	char	**splits;

	if (!s)
		return (NULL);
	splits = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!splits)
		return (NULL);
	sub_split(splits, s, c);
	return (splits);
}

void	sub_split(char **split, char const *s, char c)
{
	int	i;
	int	j;
	int	a;

	i = 0;
	a = 0;
	while ((size_t)i < ft_strlen(s))
	{
		if (s[i] != c && s[i] != 0)
		{
			j = i;
			while (s[i] != 0 && s[i] != c)
				i++;
			split[a] = sub_strs(s, j, i);
			a++;
		}
		i++;
	}
	split[a] = 0;
}

char	*sub_strs(char const *s, int start, int end)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * (end - start + 1));
	while (start != end)
	{
		str[i] = s[start];
		start++;
		i++;
	}
	str[i] = 0;
	return (str);
}

int	count_words(char const *s, char c)
{
	int	i;
	int	size;
	int	track;

	track = 0;
	i = 0;
	size = 0;
	while (s[i] != 0)
	{
		if (s[i] != c && track == 0)
		{
			size++;
			track = 1;
		}
		if (s[i] == c)
			track = 0;
		i++;
	}
	return (size);
}
