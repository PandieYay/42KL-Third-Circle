/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlim <edlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 11:02:23 by jakoh             #+#    #+#             */
/*   Updated: 2022/11/04 09:57:36 by edlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// returns 1 to shorten code
int	syntax_error(char *msg)
{
	ft_putstr_fd("ms: syntax error near unexpected token `", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("'\n", 2);
	return (258);
}

void	call_exit(t_main *m_var)
{
	tcsetattr(0, 0, &m_var->ogterm);
	system("leaks minishell");
	printf("exit\n");
	exit(0);
}

// system("leaks minishell");