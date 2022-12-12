/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlim <edlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 10:35:55 by jakoh             #+#    #+#             */
/*   Updated: 2022/11/05 09:09:12 by edlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

/**
 * @brief read user input and tokenize input into linked list
 * 
 * @param m_var main variable which contains "ac, av, envp"
 * @return t_node* 
 * return a tokenize linked list
 */
t_node	*token_reader(t_main *m_var)
{
	char	*str;
	t_node	*lists;

	str = readline("minishell> ");
	if (str && *str)
		add_history(str);
	lists = ft_node(0, NULL, 0, NULL);
	tokenize(m_var, str, &lists);
	free(str);
	return (lists);
}

/**
 * @brief for now it get info on redirection \
 * @brief and create command groups for execution
 * 
 * @param m_var contains main variable "ac, av, envp"
 * @param lists tokenize linked list of 
 */
void	mini_main(t_main *m_var, t_node **lists)
{
	t_direct	*direct;
	t_cmds		*cmds;

	direct = director(lists);
	if (direct->error == 258)
		m_var->exit_code = direct->error;
	if (direct->error != 258)
	{
		cmds = grouping(m_var, *lists, &direct);
		if (direct->error == 1)
			m_var->exit_code = direct->error;
		if (direct->error != 1)
		{
			set_direction(&direct, &cmds);
			function(m_var, &direct, &cmds);
		}
		free_cmds(&cmds);
	}
	free_direct(&direct);
	return ;
}

static void	handle_signal(int num)
{
	if (num == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (num == SIGQUIT)
	{
		write(1, "minishell> ", ft_strlen("minishell> "));
		write(1, rl_line_buffer, ft_strlen(rl_line_buffer));
	}
}

static void	handle_signal2(int num)
{
	if (num == SIGINT)
		write(1, "\n", 1);
}

int	main(int ac, char **av, char **envp)
{
	t_node	*lists;
	t_main	m_var;
	t_term	new_term;

	ft_init_main_var(&m_var, ac, av, envp);
	tcgetattr(0, &m_var.ogterm);
	tcgetattr(0, &new_term);
	new_term.c_lflag &= ~ECHOCTL;
	while (1)
	{
		tcsetattr(0, 0, &new_term);
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, handle_signal);
		lists = token_reader(&m_var);
		tcsetattr(0, 0, &m_var.ogterm);
		signal(SIGINT, handle_signal2);
		if (lists->val != NULL)
			mini_main(&m_var, &lists);
		free_lists(&lists);
	}
	return (0);
}

/*
Operator -
Single Quotes   : ' (print string as string)
Double Quotes   : " (print string as string but expand $PATH)
Redirect Input  : <
Redirect Output : >
here_doc        : <<
Append Output   : >>
Pipe Operator   : |
Enviroment Var	: $PATH
Exit Status		: $?
Dollar Symbol	: $ (Only need to expland for enviroment variable)
*/

/*
Interactive -
ctrl + C	: New prompt on a newline
ctrl + D	: Exit Shell
ctrl + \	: Do Nothing
*/

/*
Commands -
echo	: with option '-n'
cd		: with only relative or absolute path
pwd		: no options
export	: no options
unset	: no options
env		: no options or args
exit	: no options
*/
