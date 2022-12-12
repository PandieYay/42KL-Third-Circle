/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 09:10:34 by jakoh             #+#    #+#             */
/*   Updated: 2022/04/11 09:10:46 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Convert integer to ascii number
// and write it to specific file descriptor
void	ft_putnbr_fd(int n, int fd)
{
	char	s;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write (fd, "-", 1);
		n *= -1;
	}
	s = '0' + (n % 10);
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
	}
	write(fd, &s, 1);
}
