/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 19:01:37 by jakoh             #+#    #+#             */
/*   Updated: 2022/04/06 19:02:19 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Implementation of memcpy
// man memcpy for more info
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dstcpy;
	char	*srccpy;

	dstcpy = (char *)dst;
	srccpy = (char *)src;
	i = 0;
	while (i < n)
	{
		if (dstcpy == srccpy)
			return (0);
		dstcpy[i] = srccpy[i];
		i++;
	}
	return (dst);
}
