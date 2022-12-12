/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 09:25:02 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/25 14:33:47 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Locates first occurance of string 'needle in 'haystack' \
 * @brief more than 'len' character and returns a pointer to first character
 * 
 * @param haystack place to search for needle
 * @param needle thing to look for
 * @param len length of search
 * @return type: char *, first occurance of  needle in haystack
 */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*needle == 0)
		return ((char *)haystack);
	while (i < len && haystack[i] != 0)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && (i + j) < len)
		{
			if (needle[j + 1] == 0)
				return ((char *)(haystack + i));
			j++;
		}
		i++;
	}
	return (0);
}
