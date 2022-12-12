/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exportenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlim <edlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:47:03 by edlim             #+#    #+#             */
/*   Updated: 2022/11/05 09:11:14 by edlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export(t_main *m_var, t_cmds **cmd_groups)
{
	t_envp	*temp;

	temp = m_var->envp;
	if ((*cmd_groups)->input != 0 || (*cmd_groups)->output != 1)
		return ;
	if ((*cmd_groups)->args[1] == NULL)
	{
		while (temp != NULL)
		{
			printf("declare -x ");
			if (temp->val == NULL)
				printf("%s", temp->key);
			else
				printf("%s=", temp->key);
			if (temp->val != NULL)
				printf("\"%s\"", temp->val);
			printf("\n");
			temp = temp->next;
		}
		return ;
	}
	exportloop(cmd_groups, temp);
}

void	env(t_main *m_var)
{
	t_envp	*temp;

	temp = m_var->envp;
	while (temp != NULL)
	{
		if (temp->val != NULL)
		{
			printf("%s=", temp->key);
			printf("%s\n", temp->val);
		}
		temp = temp->next;
	}
}

// Test cases
// export e
// export c=d
// any other command
// Will leak

// Test cases
// export e
// export c=d
// Won't leak