/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:20:32 by jakoh             #+#    #+#             */
/*   Updated: 2022/06/23 14:41:13 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	len(char *str);

// Implementation of strlcat
// man strlcat for more info
size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	cur_d;
	size_t	cur_s;
	size_t	tol;

	cur_d = len(dest);
	tol = len(src);
	if (size < cur_d)
		tol += size;
	else
		tol += cur_d;
	cur_s = 0;
	while (cur_d + 1 < size && src[cur_s] != 0)
	{
		dest[cur_d] = src[cur_s];
		cur_d++;
		cur_s++;
	}
	dest[cur_d] = 0;
	return (tol);
}

// length of string.
size_t	len(char *str)
{
	size_t	count;

	count = 0;
	while (str[count] != 0)
	{
		count++;
	}
	return (count);
}
