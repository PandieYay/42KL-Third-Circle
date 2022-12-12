/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:43:47 by jakoh             #+#    #+#             */
/*   Updated: 2022/04/07 13:43:50 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	sub_len(char const *s, size_t start, size_t len);

// return a substring of string s thats
// starts at index start and given length.
char	*ft_substr(char const *s, size_t start, size_t len)
{
	char	*sub;
	size_t	i;

	if (!s)
		return (NULL);
	len = sub_len(s, start, len);
	sub = malloc(sizeof(char) * len + 1);
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = s[start];
		start++;
		i++;
	}
	sub[i] = 0;
	return (sub);
}

int	sub_len(char const *s, size_t start, size_t len)
{
	size_t	slen;

	slen = ft_strlen(s);
	if (start >= slen)
		return (0);
	if (slen < len)
		return (slen);
	return (len);
}
