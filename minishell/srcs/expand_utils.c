/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:59:27 by jakoh             #+#    #+#             */
/*   Updated: 2022/11/02 12:19:30 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// set i = 1 if u want it to check for left and right
// set i = 0 if u just dont give a fuck
void	cut_and_paste(t_toke_var *s, t_node **cur_node, int i)
{
	char	*temp;
	t_node	*node;

	temp = NULL;
	node = *cur_node;
	if (i == 1)
	{
		if (s->left != s->right)
		{
			temp = ft_substr(node->val, s->left, s->right - s->left);
			s->str = sjoin_ext(s->str, temp);
		}
	}
	else
	{
		temp = ft_substr(node->val, s->left, s->right - s->left);
		s->str = sjoin_ext(s->str, temp);
	}
}

// this is string join but use it when u want to free s1 & s2
char	*sjoin_ext(char *s1, char *s2)
{
	char	*temp;

	if (s1 == NULL)
		return (s2);
	if (s2 == NULL)
		return (s1);
	temp = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (temp);
}

// parsing dollar sign $ string
// expand enviroment variable and stick it to back of 
// s1 string, s2 should be the env variable
char	*dollar_join(t_main *m_var, char *s1, char *s2)
{
	char	*str;
	char	*temp;

	if (ft_strcmp(s2, "?") == 0)
		str = ft_itoa(m_var->exit_code);
	else if (ft_strcmp(s2, "$") == 0)
		str = ft_strdup("$");
	else
	{
		temp = NULL;
		if (ft_strlen(s2) != 0)
			temp = get_ev(m_var, s2);
		if (temp == NULL)
			str = ft_strdup("");
		else
			str = ft_strdup(temp);
	}
	str = sjoin_ext(s1, str);
	free(s2);
	return (str);
}

// need to handle question mark '?'
// might need to handle foward slash '\'
void	found_cash(t_main *m_var, t_node **cur_node, t_toke_var	*s)
{
	char	*temp;
	t_node	*node;

	temp = NULL;
	node = *cur_node;
	cut_and_paste(s, cur_node, 1);
	s->left = s->right;
	++(s->right);
	if (is_op(node->val[s->right]) == 9
		|| is_op(node->val[s->right]) == 1)
		return ;
	while (is_op(node->val[s->right]) != 9 && is_op(node->val[s->right]) != 1
		&& node->val[s->right - 1] != '?' && node->val[s->right] != '$')
		++(s->right);
	if (node->val[s->right] == '$' && node->val[s->right - 1] == '$')
		temp = ft_substr(node->val, s->left, s->right - s->left);
	else
		temp = ft_substr(node->val, s->left + 1, s->right - s->left - 1);
	s->str = dollar_join(m_var, s->str, temp);
	s->left = s->right;
}
