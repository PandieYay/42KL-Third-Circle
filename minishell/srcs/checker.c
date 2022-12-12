/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlim <edlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:17:56 by jakoh             #+#    #+#             */
/*   Updated: 2022/11/04 11:28:08 by edlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief check if both string is similar
 * 
 * @param a string 1
 * @param b string 2
 * @return int 
 * returns 0 if string is similar
 * else returns 1
 */
int	ft_strcmp(char *a, char *b)
{
	if (ft_strlen(a) != ft_strlen(b))
		return (1);
	while (*a || *b)
		if (*(a++) != *(b++))
			return (1);
	return (*a - *b);
}

/**
 * @brief malloc & converts string from src to lowercase and 
 * set dest to new string
 * 
 * @param src string to convert to lowercase
 * @param dest destination of lowercase string
 */
void	to_lower(char *src, char **dest)
{
	char	*str;
	int		i;

	i = -1;
	str = ft_calloc(ft_strlen(src) + 1, sizeof(char));
	while (src[++i])
	{
		if (src[i] >= 'A' && src[i] <= 'Z')
			str[i] = src[i] + 32;
		else
			str[i] = src[i];
	}
	*dest = str;
}

/**
 * @brief check if string is one of the build in function
 * 
 * @param str input string
 * @return int 
 * 1 if str is built in,
 * 0 if false
 */
int	is_built_in(char *str)
{
	char	*lower;
	int		i;

	i = 0;
	to_lower(str, &lower);
	if (!ft_strcmp(lower, "echo") || !ft_strcmp(lower, "cd")
		|| !ft_strcmp(lower, "pwd") || !ft_strcmp(lower, "export")
		|| !ft_strcmp(lower, "unset") || !ft_strcmp(lower, "env")
		|| !ft_strcmp(lower, "exit"))
		i = 1;
	free(lower);
	return (i);
}

/**
 * @brief compares input character and returns a specific value
 * 
 * @param c char
 * @return int 
 * 1 quote,
 * 2 redirection,
 * 3 pipe,
 * 4-7 seems to be redundant,
 * 8 dollar sign,
 * 9 end and spaces,
 * 0 none of the above.
 */
int	is_op(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	if (c == '<' || c == '>')
		return (2);
	if (c == '|')
		return (3);
	if (c == '/' || c == '.')
		return (4);
	if (c == '(' || c == '[' || c == '{')
		return (5);
	if (c == ')' || c == ']' || c == '}')
		return (6);
	if (c == '\\')
		return (7);
	if (c == '$')
		return (8);
	if ((c >= '\t' && c <= '\r') || c == ' ' || c == ';' || c == '\0')
		return (9);
	return (0);
}

/**
 * @brief check if input str is a token,
 * like redirection, heredoc or pipe
 * 
 * @param str normal string
 * @return int 
 * 0 if string is token
 * 1 if string is not token
 */
int	is_token(char	*str)
{
	if (!ft_strcmp(str, "<<") || !ft_strcmp(str, ">>") || !ft_strcmp(str, "<")
		|| !ft_strcmp(str, ">") || !ft_strcmp(str, "|"))
		return (0);
	return (1);
}
