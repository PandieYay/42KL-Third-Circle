/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 14:17:47 by jakoh             #+#    #+#             */
/*   Updated: 2022/04/07 14:18:02 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_size(char const *s1, char const *s2);

// Join two strings.
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*joined;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	joined = malloc(sizeof(char) * get_size(s1, s2));
	i = -1;
	if (joined == NULL)
		return (NULL);
	while (s1[++i] != 0)
		joined[i] = s1[i];
	j = 0;
	while (s2[j] != 0)
	{
		joined[i] = s2[j];
		j++;
		i++;
	}
	joined[i] = 0;
	return (joined);
}

// malloc size
int	get_size(char const *s1, char const *s2)
{
	int	s1len;
	int	s2len;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	return (s1len + s2len + 1);
}
