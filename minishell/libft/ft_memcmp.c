/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 09:44:57 by jakoh             #+#    #+#             */
/*   Updated: 2022/04/07 09:44:59 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Implementation of memcmp
// man memcmp for more info
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ts1;
	unsigned char	*ts2;

	ts1 = (unsigned char *)s1;
	ts2 = (unsigned char *)s2;
	while (n--)
	{
		if (*ts1 != *ts2)
		{
			return ((int)(*ts1 - *ts2));
		}
		ts1++;
		ts2++;
	}
	return (0);
}
