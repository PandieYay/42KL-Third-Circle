/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 08:48:04 by jakoh             #+#    #+#             */
/*   Updated: 2022/04/11 08:48:27 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Loop through each character in a string
// while applying function f to each of the character
// passing in it's index along with it.
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	if (f && s)
	{
		while (s[i] != 0)
		{
			f(i, &(s[i]));
			i++;
		}
	}
}
