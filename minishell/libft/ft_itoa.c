/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 16:33:29 by jakoh             #+#    #+#             */
/*   Updated: 2022/06/23 14:41:26 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int		get_len(int n);
char	get_num(int n);
void	num_first(char *s, int *n);

// Converts integer to ASCII number
char	*ft_itoa(int n)
{
	char	*nums;
	int		size;

	size = get_len(n);
	nums = malloc(sizeof(char) * size + 1);
	if (!nums)
		return (NULL);
	num_first(nums, &n);
	nums[size] = 0;
	if (nums[0] == '0' || nums[0] == '1')
		return (nums);
	while (n > 0)
	{
		nums[--size] = get_num(n);
		n /= 10;
	}
	return (nums);
}

// Get first character
// if its negative then add '-' to front of string
// if number is MIN_INT then add '-' and '2' to first 2 position of string
void	num_first(char *s, int *n)
{
	if (*n == 0)
		s[0] = '0';
	if (*n == 1)
		s[0] = '1';
	if (*n == -2147483648)
	{
		*n = 147483648;
		s[0] = '-';
		s[1] = '2';
	}
	if (*n < 0)
	{
		s[0] = '-';
		*n *= -1;
	}
}

// get length of string to malloc
int	get_len(int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
		return (11);
	if (n == 0)
	{
		return (1);
	}
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

// Converts integer to its ASCII number
char	get_num(int n)
{
	char	c;

	c = '0' + (n % 10);
	return (c);
}
