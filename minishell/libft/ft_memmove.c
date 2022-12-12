/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:30:25 by jakoh             #+#    #+#             */
/*   Updated: 2022/04/06 13:30:27 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Implementation of memmove
// man memmove for more info
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = -1;
	if (src < dst)
	{
		while (len-- > 0)
		{
			if ((char *)dst == (char *)src)
				return (0);
			((char *)dst)[len] = ((char *)src)[len];
		}
	}
	else
	{
		while (++i < len)
		{
			if ((char *)dst == (char *)src)
				return (0);
			((char *)dst)[i] = ((char *)src)[i];
		}
	}
	return (dst);
}
