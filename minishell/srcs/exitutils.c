/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exitutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlim <edlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:29:00 by edlim             #+#    #+#             */
/*   Updated: 2022/11/04 18:30:54 by edlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	checkifnegative(t_cmds **cmd_groups)
{
	int	i;

	i = 1;
	if ((*cmd_groups)->args[1][0] == '-')
		;
	else
		return ;
	if ((*cmd_groups)->args[1][i] == '0')
		exit (0);
	while ((*cmd_groups)->args[1][i] != '\0')
	{
		if ((*cmd_groups)->args[1][i] < '0'
			|| (*cmd_groups)->args[1][i] > '9')
		{
			printf("minishell: exit: %s: numeric argument required\n",
				(*cmd_groups)->args[1]);
			exit(255);
		}
		i++;
	}
	exit(256 + ft_atoi((*cmd_groups)->args[1]));
}

void	printnumericexit(t_cmds **cmd_groups)
{
	printf("minishell: exit: %s: numeric argument required\n",
		(*cmd_groups)->args[1]);
	exit(255);
}
