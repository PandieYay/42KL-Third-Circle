/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlim <edlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:48:23 by edlim             #+#    #+#             */
/*   Updated: 2022/11/05 09:30:59 by edlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//test
void	echo(t_cmds **cmd_groups)
{
	int		i;
	char	*isn;

	i = 1;
	isn = (*cmd_groups)->args[i];
	if (isn == NULL)
	{
		printf("\n");
		return ;
	}
	if (ft_strcmp(isn, "-n") == 0)
		++i;
	while ((*cmd_groups)->args[i] != NULL)
	{
		printf("%s", (*cmd_groups)->args[i]);
		++i;
		if ((*cmd_groups)->args[i] != NULL)
			printf(" ");
	}
	if (ft_strcmp(isn, "-n") != 0)
		printf("\n");
}

void	unset(t_main *m_var, t_cmds **cmd_groups)
{
	t_envp	*temp;
	t_envp	*tofree;
	int		i;

	i = 0;
	while ((*cmd_groups)->args[++i] != NULL)
	{
		temp = m_var->envp;
		while (temp->next != NULL)
		{
			if (ft_strcmp(temp->next->key, (*cmd_groups)->args[i]) == 0)
			{
				free(temp->next->key);
				free(temp->next->val);
				tofree = temp->next;
				if (temp->next->next != NULL)
					temp->next = temp->next->next;
				else
					temp->next = NULL;
				free(tofree);
			}
			else
				temp = temp->next;
		}	
	}
}

void	exitbuiltin(t_main *m_var, t_cmds **cmd_groups)
{
	int	i;

	i = -1;
	tcsetattr(0, 0, &m_var->ogterm);
	printf("exit\n");
	if ((*cmd_groups)->args[1] != NULL && (*cmd_groups)->args[2] != NULL)
	{
		printf("minishell: exit: too many arguments\n");
		return ;
	}
	if ((*cmd_groups)->args[1] != NULL)
	{
		checkifnegative(cmd_groups);
		while ((*cmd_groups)->args[1][++i] != '\0')
		{
			if ((*cmd_groups)->args[1][i] < '0'
				|| (*cmd_groups)->args[1][i] > '9')
				printnumericexit(cmd_groups);
		}
		exit(ft_atoi((*cmd_groups)->args[1]));
	}
	exit(0);
}

void	builtins(t_main *m_var, t_cmds **cmd_groups)
{
	m_var->exit_code = 0;
	if (ft_strcmp((*cmd_groups)->args[0], "cd") == 0
		|| ft_strcmp((*cmd_groups)->args[0], "pwd") == 0)
		cdpwd(m_var, cmd_groups);
	else if (ft_strcmp((*cmd_groups)->args[0], "echo") == 0)
		echo(cmd_groups);
	else if (ft_strcmp((*cmd_groups)->args[0], "export") == 0)
		export(m_var, cmd_groups);
	else if (ft_strcmp((*cmd_groups)->args[0], "env") == 0)
		env(m_var);
	else if (ft_strcmp((*cmd_groups)->args[0], "unset") == 0)
		unset(m_var, cmd_groups);
	else if (ft_strcmp((*cmd_groups)->args[0], "exit") == 0)
		exitbuiltin(m_var, cmd_groups);
}
