/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlim <edlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:28:26 by jakoh             #+#    #+#             */
/*   Updated: 2022/11/04 13:48:44 by edlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Readline and string join '\n' if quote not found. \
 * @brief this function handles missing quote not needed to pass \
 * @brief but already handle so ._.
 * 
 * @param str user input string
 * @param quote the quote to look for ' or "
 * @param cur_node current node in tokenization process
 * 
 * @return type: t_node *, a new token node with string. 
 */
t_node	*here_quote(char *str, char quote, t_node **cur_node)
{
	char	*rl;
	char	*store;
	char	*temp;
	char	*schr;

	temp = ft_strjoin(str, "\n");
	free(str);
	while (1)
	{
		rl = readline("> ");
		if (rl == NULL)
			rl = c_to_s(quote);
		store = ft_strjoin(temp, rl);
		free(temp);
		schr = ft_strchr(rl, quote);
		if (rl == schr || (schr != 0 && *(schr - 1) != '\\'))
			break ;
		temp = ft_strjoin(store, "\n");
		free(store);
		free(rl);
	}
	if (rl)
		free(rl);
	return (assign_node(cur_node, store, 2));
}

/**
 * @brief here_doc function \
 * @brief keeps reading input, if input == delimiter then loop ends
 * @brief here_doc is stored in string format for now.
 * 
 * @param delim delimiter to stop readling line
 * 
 * @return type: char *,
 * here_doc is stored in string format for now.
 */
char	*here_doc(char *delim)
{
	char	*rl;
	char	*store;

	store = NULL;
	if (delim == NULL)
		return (store);
	while (1)
	{
		rl = readline("heredoc> ");
		if (rl == NULL || ft_strcmp(rl, delim) == 0)
			break ;
		store = sjoin_ext(store, rl);
		store = sjoin_ext(store, ft_strdup("\n"));
	}
	if (rl)
		free(rl);
	return (store);
}

/**
 * @brief 
 * get delimiter for each heredoc 
 * and store in malloc (*direct)->delim 2d array
 * 
 * @param lists 
 * link list of tokenized input string.
 * @param direct 
 * direct contains info for pipes and here_doc
 */
void	get_delim(t_node **lists, t_direct **direct)
{
	t_node		*cur_node;
	t_direct	*cur_tol;
	int			i;

	i = 0;
	cur_node = *lists;
	cur_tol = *direct;
	while (cur_node != NULL && i < cur_tol->tol_heredoc)
	{
		if (ft_strcmp(cur_node->val, "<<") == 0)
		{
			if (cur_node->next == NULL)
				break ;
			else if (cur_node->next->type == PIPE
				|| cur_node->next->type == REDIRECT)
				break ;
			cur_node = cur_node->next;
			cur_tol->delim[i] = ft_strdup(cur_node->val);
			i++;
		}
		cur_node = cur_node->next;
	}
}

/**
 * @brief write/store heredoc 2d array in direct
 * 
 * @param direct 
 * contains info for pipes and here_doc
 */
void	write_to_heredoc(t_direct **direct)
{
	t_direct	*temp;
	int			i;

	i = -1;
	temp = *direct;
	while (++i < temp->tol_heredoc)
		temp->heredoc[i] = here_doc(temp->delim[i]);
}

char	*c_to_s(char c)
{
	char	*str;

	str = malloc(2 * sizeof(char));
	str[0] = c;
	str[1] = 0;
	return (str);
}
