/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exportutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlim <edlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:09:14 by edlim             #+#    #+#             */
/*   Updated: 2022/11/05 09:10:13 by edlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	gotequal(char *val)
{
	int	i;

	i = 0;
	while (val[i] != '\0')
	{
		if (val[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

static void	export4(t_cmds **cmd_groups, t_envp *temp, char **split, int argc)
{
	char	*val;
	int		i;

	val = ft_strchr((*cmd_groups)->args[argc], '=');
	val++;
	temp->next = malloc(sizeof(t_envp));
	temp->next->key = ft_strdup(split[0]);
	temp->next->val = ft_strdup(val);
	temp->next->next = NULL;
	i = -1;
	while (split[++i] != NULL)
		free(split[i]);
	free(split);
}

static int	export2(t_cmds **cmd_groups, t_envp *temp, int argc)
{
	if (gotequal((*cmd_groups)->args[argc]) == 0)
	{
		while (temp != NULL)
		{
			if (strcmp(temp->key, (*cmd_groups)->args[argc]) == 0)
				return (1);
			if (temp->next == NULL)
				break ;
			temp = temp->next;
		}
		temp->next = malloc(sizeof(t_envp));
		temp->next->key = ft_strdup((*cmd_groups)->args[argc]);
		temp->next->val = NULL;
		temp->next->next = NULL;
		return (1);
	}
	return (0);
}

static void	exportutil(t_cmds **cmd_groups, t_envp *temp, int argc)
{
	char	**split;
	char	*val;
	int		i;

	split = ft_split((*cmd_groups)->args[argc], '=');
	while (temp != NULL)
	{
		if (strcmp(temp->key, split[0]) == 0)
		{
			i = -1;
			while (split[++i] != NULL)
				free(split[i]);
			free(split);
			val = ft_strchr((*cmd_groups)->args[argc], '=');
			val++;
			if (temp->val != NULL)
				free(temp->val);
			temp->val = ft_strdup(val);
			return ;
		}
		if (temp->next == NULL)
			break ;
		temp = temp->next;
	}
	export4(cmd_groups, temp, split, argc);
}

void	exportloop(t_cmds **cmd_groups, t_envp *temp)
{
	int	i;

	i = 1;
	while ((*cmd_groups)->args[i] != NULL)
	{
		if (export2(cmd_groups, temp, i) == 1)
			;
		else
			exportutil(cmd_groups, temp, i);
		i++;
	}
}
