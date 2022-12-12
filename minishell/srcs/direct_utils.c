/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:18:39 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/20 15:46:26 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief malloc space for heredoc delimiter & heredoc,
 * heredoc is stored in string format.
 * 
 * @param direct 
 * direct is struct to store pipes & heredoc stuff
 */
void	malloc_heredoc(t_direct **direct)
{
	t_direct	*temp;

	temp = *direct;
	if (temp->tol_heredoc != 0)
	{
		temp->delim = ft_calloc(temp->tol_heredoc + 1, sizeof(char *));
		temp->delim[temp->tol_heredoc] = NULL;
		temp->heredoc = ft_calloc(temp->tol_heredoc + 1, sizeof(char *));
		temp->heredoc[temp->tol_heredoc] = NULL;
	}
}

/**
 * @brief 
 * malloc and init fd for pipes
 * 
 * @param direct 
 * direct struct that contains info on pipes and heredoc
 */
void	malloc_pipes(t_direct **direct)
{
	t_direct	*temp;
	int			i;

	temp = *direct;
	if (temp->tol_pipes != 0)
	{
		temp->fd_pipes = ft_calloc(temp->tol_pipes + 1, sizeof(int *));
		temp->fd_pipes[temp->tol_pipes] = NULL;
		i = -1;
		while (++i < temp->tol_pipes)
		{
			temp->fd_pipes[i] = ft_calloc(2, sizeof(int));
			pipe(temp->fd_pipes[i]);
		}
	}
}
