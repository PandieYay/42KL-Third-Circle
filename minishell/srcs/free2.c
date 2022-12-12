/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlim <edlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:39:14 by jakoh             #+#    #+#             */
/*   Updated: 2022/11/04 13:33:25 by edlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Free strings thats in direct, here_doc delimiter and here_doc as string
 * 
 * @param direct N/A
 */
void	free_direct_str(t_direct **direct)
{
	t_direct	*temp;
	int			i;

	i = -1;
	temp = *direct;
	if (temp->delim != NULL)
	{
		while (temp->delim[++i] != NULL)
		{
			free(temp->delim[i]);
			free(temp->heredoc[i]);
		}
		free(temp->delim);
		free(temp->heredoc);
	}
}

/**
 * @brief free fd in directm, fd of pipes and fd of here_doc
 * 
 * @param direct N/A
 */
void	free_direct_fd(t_direct **direct)
{
	t_direct	*temp;
	int			i;

	temp = *direct;
	i = -1;
	if (temp->fd_pipes != NULL)
	{
		while (temp->fd_pipes[++i] != NULL)
			free(temp->fd_pipes[i]);
		free(temp->fd_pipes);
	}
	i = -1;
	if (temp->fd_heredoc != NULL)
	{
		while (temp->fd_heredoc[++i] != NULL)
			free(temp->fd_heredoc[i]);
		free(temp->fd_heredoc);
	}
}

/**
 * @brief free strings that contains in direct \
 * @brief here_doc delimiter and here_doc string
 * 
 * @param direct N/A
 */
void	free_direct(t_direct **direct)
{
	free_direct_fd(direct);
	free_direct_str(direct);
	if ((*direct) != NULL)
		free(*direct);
}
