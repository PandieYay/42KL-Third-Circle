/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:48:36 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/28 16:10:45 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Set input and output of command groups \
 * @brief set to read from heredoc or pipe if needed or \
 * @brief set write to file or pipe if needed
 * 
 * @param direct contains heredoc fd
 * @param cmds command group
 */
void	set_direction(t_direct **direct, t_cmds **cmds)
{
	if ((*direct)->tol_heredoc != 0)
		set_heredoc(direct, cmds);
	if ((*direct)->tol_pipes != 0)
		set_pipes(direct, cmds);
}

/**
 * @brief command group input and output fd to pipe fd if needed
 * 
 * @param direct contains pipe fd
 * @param cmds command group
 */
void	set_pipes(t_direct **direct, t_cmds **cmds)
{
	int		i;
	t_cmds	*temp;

	i = -1;
	temp = *cmds;
	while (temp != NULL)
	{
		++i;
		if (i == 0 && temp->output == 1)
			temp->output = (*direct)->fd_pipes[i][1];
		else if (i == (*direct)->tol_pipes && temp->input == 0)
				temp->input = (*direct)->fd_pipes[i - 1][0];
		else if (i != 0 && i != (*direct)->tol_pipes)
		{
			if (temp->input == 0)
				temp->input = (*direct)->fd_pipes[i - 1][0];
			if (temp->output == 1)
				temp->output = (*direct)->fd_pipes[i][1];
		}
		temp = temp->next;
	}
}

/**
 * @brief Set command group input fd to heredoc fd if needed
 * 
 * @param direct contains heredoc fd
 * 
 * @param cmds command group
 */
void	set_heredoc(t_direct **direct, t_cmds **cmds)
{
	t_cmds	*cur_cmd;
	int		i;

	fd_heredoc_helper(direct, cmds);
	i = 0;
	cur_cmd = *cmds;
	while (cur_cmd != NULL)
	{
		if (cur_cmd->input == -2)
		{
			if ((*direct)->heredoc[cur_cmd->heredoc_no] != NULL)
				write((*direct)->fd_heredoc[i][1],
					(*direct)->heredoc[cur_cmd->heredoc_no],
					ft_strlen((*direct)->heredoc[cur_cmd->heredoc_no]));
			close((*direct)->fd_heredoc[i][1]);
			cur_cmd->input = (*direct)->fd_heredoc[i][0];
			cur_cmd->heredoc_no = i;
			++i;
		}
		else
			cur_cmd->heredoc_no = -1;
		cur_cmd = cur_cmd->next;
	}
}

/**
 * @brief counts how many heredoc fd we need \
 * @brief malloc and pipe fds for heredoc
 * 
 * @param direct stores heredoc fd in direct
 * @param cmds command group
 */
void	fd_heredoc_helper(t_direct **direct, t_cmds **cmds)
{
	t_cmds	*cur_cmd;
	int		tol;
	int		i;

	tol = 0;
	cur_cmd = *cmds;
	while (cur_cmd != NULL)
	{
		if (cur_cmd->input == -2)
			tol++;
		cur_cmd = cur_cmd->next;
	}
	if (tol == 0)
		return ;
	(*direct)->fd_heredoc = ft_calloc(tol + 1, sizeof(int *));
	(*direct)->fd_heredoc[tol] = NULL;
	i = -1;
	while (++i < tol)
	{
		(*direct)->fd_heredoc[i] = ft_calloc(2, sizeof(int));
		pipe((*direct)->fd_heredoc[i]);
	}
}
