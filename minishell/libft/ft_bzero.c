/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:38:04 by jakoh             #+#    #+#             */
/*   Updated: 2022/04/06 13:39:47 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Implementation of bzero
// Writes zeros/NULL to a string
// Writes n amout of 0 to s
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
