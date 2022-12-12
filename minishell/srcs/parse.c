/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlim <edlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 21:01:55 by jakoh             #+#    #+#             */
/*   Updated: 2022/11/04 14:31:34 by edlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Get the num arguments for each command group
 * 
 * @param lists tokenize list
 * @param hd destination for here doc
 * 
 * @return type: t_node *, returns a empty command group hd is set.
 */
t_cmds	*init_cur_group(t_node *lists, int *hd)
{
	int		num_args;

	num_args = 0;
	while (lists != NULL)
	{
		if (lists->type == PIPE)
			break ;
		else if (lists->type == REDIRECT)
		{
			if (ft_strcmp(lists->val, "<<") == 0)
				++(*hd);
			lists = lists->next;
		}
		else
			++num_args;
		lists = lists->next;
	}
	return (cmd_groups_init(0, 1, num_args, *hd));
}

/**
 * @brief check permission and open fd if able
 * 
 * @param path file path
 * @param type 
 * 0 = READ <
 * 1 = WRITE >
 * 2 = APPEND >>
 * @param cur current command group
 * 
 * @return int 
 * 1 if fail
 * 0 if success
 */
int	check_access(char *path, int type, t_cmds **cur)
{
	if (type == 0)
	{
		if (access(path, R_OK) == -1)
		{
			printf("%s: %s\n", path, strerror(errno));
			return (-1);
		}
		(*cur)->input = open(path, O_RDONLY);
	}
	else if (type == 1 || type == 2)
	{
		if (type == 1)
			(*cur)->output = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		else
			(*cur)->output = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if ((*cur)->output == -1 && access(path, W_OK) == -1)
		{
			printf("%s: %s\n", path, strerror(errno));
			close((*cur)->output);
			return (-1);
		}
	}
	return (0);
}

/**
 * @brief extention for grouping function \
 * @brief this function runs checks for pipe and redirection \
 * @brief and open fd for input and output if necessary
 * 
 * @param list tokenize linked list
 * @param cur_group current_group linked list
 * @param i tracks arguments resets if current token is a pipe
 * @param hd represents current here_doc
 * 
 * @return type: int, -1 if fail to redirect
 * 2 if redirection successful (useless for now)
 * 1 if pipe encountered (useless for now)
 */
int	grouping_ext(t_node **list, t_cmds **cur_group, int *i, int *hd)
{
	int	check;

	check = 0;
	if ((*list)->type == PIPE)
	{
		*i = -1;
		(*cur_group)->next = init_cur_group((*list)->next, hd);
		(*cur_group) = (*cur_group)->next;
		check = 1;
	}
	else if ((*list)->type == REDIRECT)
	{
		if (ft_strcmp((*list)->val, "<") == 0)
			check = check_access((*list)->next->val, 0, cur_group);
		else if (ft_strcmp((*list)->val, "<<") == 0)
				(*cur_group)->input = -2;
		else if (ft_strcmp((*list)->val, ">") == 0)
			check = check_access((*list)->next->val, 1, cur_group);
		else if (ft_strcmp((*list)->val, ">>") == 0)
			check = check_access((*list)->next->val, 2, cur_group);
		*list = (*list)->next;
	}
	return (check);
}

/**
 * @brief Create command group link list \
 * @brief set each groups input, output and arguments
 * @brief ALL COMMAND GROUP SHARES THE SAME ENVP SO FREE CAREFULLY
 * 
 * @param m_var main variable for ac, av & envp
 * @param lists tokenize lists
 * @param direct contains info about heredoc and pipes 
 */
t_cmds	*grouping(t_main *m_var, t_node *lists, t_direct **direct)
{
	t_cmds	*cmd_groups;
	t_cmds	*cur_group;
	int		hd;
	int		i;

	hd = -1;
	i = -1;
	cmd_groups = init_cur_group(lists, &hd);
	cur_group = cmd_groups;
	while (lists != NULL && lists->val != NULL)
	{
		if (lists->type == PIPE || lists->type == REDIRECT)
		{
			if (grouping_ext(&lists, &cur_group, &i, &hd) == -1)
			{
				(*direct)->error = 1;
				break ;
			}
		}
		else
			cur_group->args[++i] = ft_strdup(lists->val);
		lists = lists->next;
	}
	add_envp(m_var, &cmd_groups);
	return (cmd_groups);
}
