/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlim <edlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 16:42:02 by jakoh             #+#    #+#             */
/*   Updated: 2022/11/03 13:38:44 by edlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_quote(t_main *m_var, char *str, t_toke_var *s, t_node **cur_node);
void	token_arg(t_main *m_var, char *str, t_toke_var *s, t_node **cur_node);
void	token_symbol(char *str, t_toke_var *s, t_node **cur_node);

// store and parse readline string into link list
// 1st if statement checks if quote ' or " is accompanied by '\'
// if accompanied by '\' then just move on
// 2nd if statement checks for quote only ' or "
// 3rd if statement checks for ' ' \0  ;
// space, end or semi-colon
// 4th if statement checks for < > |
// redirections and pipes
void	tokenize(t_main *m_var, char *str, t_node **list)
{
	t_toke_var		s;
	t_node			*cur_node;

	cur_node = *list;
	s.left = 0;
	s.right = 0;
	if (str == NULL)
		call_exit(m_var);
	s.len = ft_strlen(str) + 1;
	while (s.right < s.len && s.left < s.len)
	{
		if (s.right != 0 && str[s.right - 1] == '\\'
			&& is_op(str[s.right]) == 1)
				++(s.right);
		else if (is_op(str[s.right]) == 1)
			token_quote(m_var, str, &s, &cur_node);
		else if (s.left != s.right && (is_op(str[s.right]) == 9
				|| is_op(str[s.right]) == 2 || is_op(str[s.right]) == 3))
			token_arg(m_var, str, &s, &cur_node);
		else if (is_op(str[s.right]) == 2 || is_op(str[s.right]) == 3)
			token_symbol(str, &s, &cur_node);
		else
			++(s.right);
	}
}

// parse quote ' or "
// if closing quote not found 
// then call here_quote which will call readline
// until quote is found 
void	token_quote(t_main *m_var, char *str, t_toke_var *s, t_node **cur_node)
{
	int		prev;
	char	*temp;

	prev = s->right;
	while (str[++(s->right)] != str[prev] && str[s->right] != 0)
		;
	if (str[s->right] == 0)
	{
		temp = ft_substr(str, s->left, (s->right - s->left + 1));
		*cur_node = here_quote(temp, str[prev], cur_node);
		expand_env(m_var, cur_node);
	}
	++(s->right);
}

// parse arguments and check if its a command or not
// function will only be called if hits a space, end of string or ';'
void	token_arg(t_main *m_var, char *str, t_toke_var *s, t_node **cur_node)
{
	char	*temp;

	if (is_op(str[s->left]) == 9)
		s->left++;
	if ((s->left == s->right || is_op(str[s->left]) == 9))
		return ;
	temp = ft_substr(str, s->left, (s->right - s->left));
	*cur_node = assign_node(cur_node, temp, 2);
	expand_env(m_var, cur_node);
	if (is_op(str[s->right]) != 2 && is_op(str[s->right]) != 3)
	{
		s->left = ++(s->right);
	}
	else
		s->left = s->right;
}

// parse redirection and pipe "<" "<<" ">" ">>" "|"
// if theres anything before symbol then
// store it in linked list before storing symbol
// example : asd<
// stores "asd" in link list before storing "<"
void	token_symbol(char *str, t_toke_var *s, t_node **cur_node)
{
	char	*temp;

	if (s->left != s->right && !(s->right - s->left == 1
			&& is_op(str[s->left]) == 9))
	{
		temp = ft_substr(str, s->left, (s->right - s->left));
		*cur_node = assign_node(cur_node, temp, 2);
	}
	s->left = s->right;
	if (is_op(str[s->right]) == 2)
	{
		if (str[s->right] == str[s->right + 1])
		{
			*cur_node = assign_node(cur_node, ft_substr(str, s->left, 2), 3);
			++(s->right);
		}
		else
			*cur_node = assign_node(cur_node, ft_substr(str, s->left, 1), 3);
	}
	else if (is_op(str[s->right]) == 3)
		*cur_node = assign_node(cur_node, ft_substr(str, s->left, 1), 4);
	s->left = ++(s->right);
}
