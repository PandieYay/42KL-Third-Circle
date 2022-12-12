/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlim <edlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:12:21 by jakoh             #+#    #+#             */
/*   Updated: 2022/11/04 17:55:03 by edlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief set utilities for function \
 * @brief sets status = 0 and store default input and output
 * @param utils pointer to utils variable in function
 */
void	utils_init(t_utils *utils)
{
	utils->status = 0;
	utils->input = dup(0);
	utils->output = dup(1);
}

/**
 * @brief execute non builtin functions
 * 
 * @param cmds current command group
 */
void	executor(t_cmds **cmds)
{
	char	*path;
	int		i;

	i = -1;
	if ((*cmds)->args[0] == NULL)
		return ;
	path = get_path(cmds);
	execve(path, (*cmds)->args, (*cmds)->envp);
	exit(127);
}

/**
 * @brief function to execute command group\
 * @brief this is where we fork processes to execute commands
 * 
 * @param m_var main variable contains envp and error code
 * @param direct contains all fd needed to handle input and output
 * @param cmds commands groups in linked list
 */
void	function(t_main *m_var, t_direct **direct, t_cmds **cmds)
{
	t_cmds	*temp;
	t_utils	utils;

	utils_init(&utils);
	temp = *cmds;
	while (temp != NULL)
	{
		if (temp->args[0] == NULL)
			;
		else if (is_built_in(temp->args[0]) == 1)
		{
			handle_io(temp->input, temp->output, 3);
			builtins(m_var, &temp);
			handle_io(utils.input, utils.output, 1);
		}
		else
			forker(&temp, direct);
		handle_io(temp->input, temp->output, 2);
		temp = temp->next;
	}
	handle_io(utils.input, utils.output, 3);
	ft_close_pipes(direct);
	while (waitpid(-1, &(utils.status), 0) > 0)
		;
	m_var->exit_code = WEXITSTATUS(utils.status);
}

/**
 * @brief forking is done here
 * 
 * @param cur_cmd current command group
 * @param direct contains fd to close after dupping
 * @return pid_t 
 */
pid_t	forker(t_cmds **cur_cmd, t_direct **direct)
{
	pid_t	id;

	id = fork();
	if (id < 0)
		return (-1);
	if (id == 0)
	{
		handle_io((*cur_cmd)->input, (*cur_cmd)->output, 3);
		ft_close_pipes(direct);
		executor(cur_cmd);
		return (id);
	}
	return (id);
}
