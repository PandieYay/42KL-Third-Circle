/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 18:03:29 by jakoh             #+#    #+#             */
/*   Updated: 2022/10/04 18:39:59 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// expanding arguments
// just like tokenizing
// only this time we free cur_node->val
// and string join the new part of the string
void	expand_env(t_main *m_var, t_node **cur_node)
{
	t_node		*node;
	t_toke_var	s;

	node = *cur_node;
	if (node->type != 2 || node->val == NULL)
		return ;
	init_toke_var(&s, ft_strlen(node->val), NULL);
	expand_env_ext(m_var, cur_node, &s);
	free(node->val);
	node->val = s.str;
	if (is_built_in(node->val) == 1)
		node->type = 1;
}

// loop and checks for quotes and dollar
// if not in quote but found $ expand
void	expand_env_ext(t_main *m_var, t_node **cur_node, t_toke_var *s)
{
	t_node	*node;

	node = *cur_node;
	while (s->right < s->len && s->left < s->len)
	{
		if (is_op(node->val[s->right]) == 1)
		{
			cut_and_paste(s, cur_node, 1);
			s->left = s->right;
			expand_env_ext_quote(m_var, cur_node, s);
			s->left = ++(s->right);
		}
		else if (node->val[s->right] == '$')
			found_cash(m_var, cur_node, s);
		else
			++(s->right);
	}
	cut_and_paste(s, cur_node, 0);
}

// if single quote dont expand just loop till it finds it significant other
// if in double quote and found $ then expand
// but also traverse till it finds its significant other
void	expand_env_ext_quote(t_main *m_var, t_node **cur_node, t_toke_var *s)
{
	t_node	*node;

	node = *cur_node;
	if (node->val[(s->left)] == '\'')
	{
		++(s->left);
		while (node->val[++(s->right)] != '\'')
			;
		cut_and_paste(s, cur_node, 0);
	}
	else if (node->val[(s->left)] == '\"')
	{
		++(s->left);
		while (node->val[++(s->right)] != '\"')
		{
			if (node->val[s->right] == '$')
			{
				found_cash(m_var, cur_node, s);
				--(s->right);
				if (node->val[s->right] == '\"')
					break ;
			}
		}
		cut_and_paste(s, cur_node, 0);
	}
}
