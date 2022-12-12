/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:29:58 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/28 16:27:07 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Implementation of atoi (ASCII to Integer)
int	ft_atoi(const char *str)
{
	int	i;
	int	ans;
	int	neg;

	neg = 1;
	ans = 0;
	i = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		++i;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			neg = -1;
	while (str[i] >= '0' && str[i] <= '9')
		ans = (ans * 10) + (str[i++] - '0');
	return (ans * neg);
}
