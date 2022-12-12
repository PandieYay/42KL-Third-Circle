/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 09:45:28 by jakoh             #+#    #+#             */
/*   Updated: 2022/04/07 09:45:33 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Implementation of calloc
// Similar to malloc but with the addition to bzero
// Allocates and return size bytes of memory and filled it with 0
void	*ft_calloc(size_t count, size_t size)
{
	char	*s;

	if (count > 4294967295 || size > 4294967295)
		return (NULL);
	s = malloc(count * size);
	if (s == NULL)
		return (NULL);
	ft_bzero((void *)s, count * size);
	return ((void *)s);
}
