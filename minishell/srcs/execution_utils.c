/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlim <edlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:59:14 by jakoh             #+#    #+#             */
/*   Updated: 2022/11/04 15:42:13 by edlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief sets input and output for processes \
 * @brief for execution
 * 
 * @param cur current command group
 * @param check
 * if check == 1 dup input/output ONLY,
 * if check == 2 close input/output ONLY if possible,
 * if check == 3 dup and close input/output.
 */
void	handle_io(int input, int output, int check)
{
	if (check == 1 || check == 3)
	{
		dup2(input, STDIN_FILENO);
		dup2(output, STDOUT_FILENO);
	}
	if (check == 2 || check == 3)
	{
		if (input != STDIN_FILENO)
			close(input);
		if (output != STDOUT_FILENO)
			close(output);
	}
}

/**
 * @brief close all pipes in 'direct' this includes pipes fd and heredoc fd
 *
 * @param direct N/A
 */
void	ft_close_pipes(t_direct **direct)
{
	int			i;

	i = -1;
	if ((*direct)->fd_pipes != NULL)
	{
		while ((*direct)->fd_pipes[++i] != NULL)
		{
			close((*direct)->fd_pipes[i][0]);
			close((*direct)->fd_pipes[i][1]);
			free((*direct)->fd_pipes[i]);
		}
		free((*direct)->fd_pipes);
		(*direct)->fd_pipes = NULL;
	}
	i = -1;
	if ((*direct)->fd_heredoc != NULL)
	{
		while ((*direct)->fd_heredoc[++i] != NULL)
		{
			close((*direct)->fd_heredoc[i][0]);
			free((*direct)->fd_heredoc[i]);
		}
		free((*direct)->fd_heredoc);
		(*direct)->fd_heredoc = NULL;
	}
}

char	**search_path(t_cmds **cmds)
{
	int	i;

	i = -1;
	while ((*cmds)->envp[++i] != NULL)
	{
		if (ft_strnstr((*cmds)->envp[i], "PATH", 4) != 0)
			return (ft_split((*cmds)->envp[i] + 5, ':'));
	}
	return (NULL);
}

/**
 * @brief returns a 2d array of all possible PATH for executable
 * 
 * @param cmds current command group
 * @return type: char **, 2d array of possible executable PATH 
 */
char	**find_path(t_cmds **cmds)
{
	char	**all;
	char	*temp;
	int		i;

	if ((*cmds)->args[0] == NULL)
		return (NULL);
	all = search_path(cmds);
	i = -1;
	while (all[++i] != NULL)
	{
		temp = all[i];
		all[i] = ft_strjoin(temp, "/");
		free(temp);
		temp = all[i];
		all[i] = ft_strjoin(temp, (*cmds)->args[0]);
		free(temp);
	}
	return (all);
}

/**
 * @brief Check if current path is executable 
 * if none of the paths is executable, command not found is printed 
 * and exit(127) is called;
 * @param cmds current command group
 * @return type: char *, executable path
 */
char	*get_path(t_cmds **cmds)
{
	char	**paths;
	char	*temp;
	int		i;

	if (access((*cmds)->args[0], X_OK) == 0)
		return ((*cmds)->args[0]);
	i = -1;
	temp = NULL;
	paths = find_path(cmds);
	while (paths[++i] != NULL)
	{
		if (access(paths[i], X_OK) != -1 && temp == NULL)
			temp = ft_strdup(paths[i]);
		free(paths[i]);
	}
	free(paths);
	if (temp == NULL && (*cmds)->args[0] != NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd((*cmds)->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	return (temp);
}
