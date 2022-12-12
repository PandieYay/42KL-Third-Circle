/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:39:47 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/03 18:19:07 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Locates the first occurrence of character in string.
char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c && *s != 0)
		++s;
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}
