/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:44:22 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/27 10:30:18 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_direct	*director(t_node **lists)
{
	t_direct	*tol;

	tol = init_direct();
	if ((*lists)->type == PIPE)
	{
		tol->error = syntax_error((*lists)->val);
		return (tol);
	}
	get_total(lists, &tol);
	if (tol->tol_heredoc != 0)
	{
		malloc_heredoc(&tol);
		get_delim(lists, &tol);
		write_to_heredoc(&tol);
	}
	if (tol->tol_pipes != 0 && tol->error != 1)
		malloc_pipes(&tol);
	return (tol);
}

/**
 * @brief
 * Gets total number of pipes,
 * number of heredoc,
 * check if theres token error,
 * if error found then output error message.
 * 
 * @param lists 
 * link list of tokenized input string.
 * @param direct 
 * direct contains info for pipes and here_doc
 */
void	get_total(t_node **lists, t_direct **direct)
{
	t_node	*temp;

	temp = *lists;
	while (temp != NULL && temp->val != NULL)
	{
		get_tol_condition(direct, temp);
		if ((*direct)->error == 258)
			return ;
		temp = temp->next;
	}
}

/**
 * @brief extention of get_total function,
 * checks and print token error. And count number of 
 * pipes '|' and redirection '< > >> <<'
 * @param direct 
 * direct contains info for pipes and here_doc
 * @param cur_node 
 * current node in loop
 */
void	get_tol_condition(t_direct **direct, t_node *cur_node)
{
	if (cur_node->type == PIPE)
	{
		if (cur_node->next == NULL || cur_node->next->type == PIPE)
			(*direct)->error = syntax_error(cur_node->val);
	}
	else if (cur_node->type == REDIRECT)
	{
		if (cur_node->next == NULL)
			(*direct)->error = syntax_error("newline");
		else if (is_token(cur_node->next->val) == 0)
			(*direct)->error = syntax_error(cur_node->next->val);
	}
	if (ft_strcmp(cur_node->val, "<<") == 0)
		++((*direct)->tol_heredoc);
	else if (cur_node->type == PIPE)
		++((*direct)->tol_pipes);
}
