/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:35:54 by jakoh             #+#    #+#             */
/*   Updated: 2022/11/02 12:29:20 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// get specific enviroment variable from linked list envp
char	*get_ev(t_main *m_var, char *var)
{
	t_envp	*temp;

	temp = m_var->envp;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->key, var) == 0)
			break ;
		temp = temp->next;
	}
	if (temp == NULL)
		return (NULL);
	return (temp->val);
}

int	get_env_len(t_envp *envp)
{
	t_envp	*temp;
	int		i;

	i = 0;
	temp = envp;
	while (temp != NULL)
	{
		++i;
		temp = temp->next;
	}
	return (i);
}

/**
 * @brief counts and converts envp in m_var into a 2d string
 * 
 * @param m_var main variable that contains ac av and (envp in linked list)
 * 
 * @return type:char **, envp in 2D String
 */
char	**envp_converter(t_main *m_var)
{
	t_envp	*cur;
	char	**env;
	char	*temp;
	int		i;

	cur = m_var->envp;
	i = get_env_len(cur);
	env = ft_calloc(i + 1, sizeof(char *));
	env[i] = NULL;
	i = -1;
	while (cur != NULL)
	{
		if (cur->val != NULL)
		{
			temp = ft_strjoin(cur->key, "=");
			env[++i] = ft_strjoin(temp, cur->val);
			free(temp);
		}
		cur = cur->next;
	}
	return (env);
}

/**
 * @brief converts envp linked list into 2d char * \
 * @brief and store in cmd_groups->envp
 * 
 * @param m_var main variable that contains ac av and (envp in linked list)
 * @param cmd_groups cmd_groups to be executed.
 */
void	add_envp(t_main *m_var, t_cmds **cmd_groups)
{
	t_cmds	*temp;
	char	**env;

	temp = *cmd_groups;
	env = envp_converter(m_var);
	while (temp != NULL)
	{
		temp->envp = env;
		temp = temp->next;
	}
}
