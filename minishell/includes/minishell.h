/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlim <edlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 15:04:18 by jakoh             #+#    #+#             */
/*   Updated: 2022/11/05 09:09:04 by edlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <limits.h>
# include <signal.h>
# include <termios.h>

enum e_type
{
	NO_TYPE,
	CMD,
	ARG,
	REDIRECT,
	PIPE,
};

typedef struct termios		t_term;

// type 0 = no type, 1 = built in command,
// 2 = arguments, 3 = redirections,
// 4 = pipe
typedef struct s_node
{
	int				id;
	char			*val;
	int				type;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

// linked-list like data struct 
// to store enviroment variable
typedef struct s_envp
{
	char			*key;
	char			*val;
	struct s_envp	*next;
}	t_envp;

// struct to store main parameters
typedef struct s_main
{
	int		ac;
	char	**av;
	t_envp	*envp;
	int		exit_code;
	t_term	ogterm;
}	t_main;

// tokenizing/parsing struct
// use to shorten code.
typedef struct s_toke_var
{
	int		left;
	int		right;
	int		len;
	char	*str;
}	t_toke_var;

/**
 * @brief stores
 * @param error
 * error = 1 if error encountered during parsing
 * else error = 0;
 * @param tol_hereodc
 * total number of heredoc 
 * @param tol_pipes
 * total number of pipes
 * @param delim
 * delimiter in 2d char *,
 * heredocs as string in 2d  char *
 * fd for pipes in 2d int array,
 */
typedef struct s_direct
{
	int		error;
	int		tol_heredoc;
	int		tol_pipes;
	char	**delim;
	int		**fd_pipes;
	char	**heredoc;
	int		**fd_heredoc;
}	t_direct;

/**
 * @brief this is execution group
 * determines input and output fd
 * @param input
 * 0 is default else will be read end of pipe or heredoc fd
 * @param output_fd
 * 1 is default else will be write end of pipe or fd of output file
 * @param heredoc_no
 * all heredoc is called before any execution, 
 * this determines which heredoc to use 
 * if there "<<a <<b | <<c" 3 heredoc but for first command group,
 * we use heredoc number 2 "<<b" and second command group we use,
 * heredoc 3 "<<c". This will store the number of heredoc we need
 * to put into a heredoc file and set input to fd of that heredoc file.
 * if theres heredoc changes input to heredoc file
 * @param args
 * arguments to be run in execve, args[0] will be command
 * @param envp
 * enviroment variable in array format
 * @param next
 * next command group, for piping
 */
typedef struct s_cmds
{
	int				input;
	int				output;
	int				heredoc_no;
	char			**args;
	char			**envp;
	struct s_cmds	*next;
}	t_cmds;

typedef struct s_utils
{
	int	status;
	int	input;
	int	output;
}	t_utils;
// checker.c
int			is_op(char c);
int			is_token(char	*str);
int			is_built_in(char *str);
int			ft_strcmp(char *a, char *b);
void		to_lower(char *src, char **dest);

// inits.c
t_direct	*init_direct(void);
void		init_toke_var(t_toke_var *s, int len, char *temp);
t_cmds		*cmd_groups_init(int ipt, int opt, int num_args, int hd);
void		ft_init_main_var(t_main *main, int ac, char **av, char **envp);

// init_utils.c
char		*get_key(char *envp);
char		*get_val(char *envp);

// env.c
char		**envp_converter(t_main *m_var);
char		*get_ev(t_main *m_var, char *var);
int			get_env_len(t_envp *envp);
void		add_envp(t_main *m_var, t_cmds **cmd_groups);

// node_utils.c
t_node		*ft_node(int id, char *val, int type, t_node **prev);
t_node		*assign_node(t_node **cur_node, char *val, int type);

// tokenize.c
void		token_quote(t_main *m_var, char *str, t_toke_var *s,
				t_node **cur_node);
void		token_arg(t_main *m_var, char *str, t_toke_var *s,
				t_node **cur_node);
void		token_symbol(char *str, t_toke_var *s, t_node **cur_node);
void		tokenize(t_main *m_var, char *str, t_node **tree);

// expand.c
void		expand_env(t_main *m_var, t_node **cur_node);
void		expand_env_ext(t_main *m_var, t_node **cur_node, t_toke_var *s);
void		expand_env_ext_quote(t_main *m_var, t_node **cur_node,
				t_toke_var *s);

// expand_utils.c
char		*sjoin_ext(char *s1, char *s2);
char		*dollar_join(t_main *m_var, char *s1, char *s2);
void		cut_and_paste(t_toke_var *s, t_node **cur_node, int i);
void		found_cash(t_main *m_var, t_node **cur_node, t_toke_var	*s);

// direct.c
t_direct	*director(t_node **lists);
void		get_total(t_node **lists, t_direct **direct);
void		get_tol_condition(t_direct **direct, t_node *cur_node);

// direct_utils.c
void		malloc_pipes(t_direct **direct);
void		malloc_heredoc(t_direct **direct);

// here_doc.c
char		*c_to_s(char c);
char		*here_doc(char *delim);
void		write_to_heredoc(t_direct **direct);
void		get_delim(t_node **lists, t_direct **direct);
t_node		*here_quote(char *str, char quote, t_node **list);

//parse.c
t_cmds		*init_cur_group(t_node *lists, int *hd);
int			check_access(char *path, int type, t_cmds **cur);
int			grouping_ext(t_node **list, t_cmds **cur_group, int *i, int *hd);
t_cmds		*grouping(t_main *m_var, t_node *lists, t_direct **direct);
void		set_heredoc(t_direct **direct, t_cmds **cmds);

// parse_utils.c
void		set_pipes(t_direct **direct, t_cmds **cmds);
void		set_heredoc(t_direct **direct, t_cmds **cmds);
void		set_direction(t_direct **direct, t_cmds **cmds);
void		fd_heredoc_helper(t_direct **direct, t_cmds **cmds);

// execution.c
void		executor(t_cmds **cmds);
pid_t		forker(t_cmds **cur_cmd, t_direct **direct);
void		function(t_main *m_var, t_direct **direct, t_cmds **cmds);

// execution_utils.c
char		*get_path(t_cmds **cmds);
char		**find_path(t_cmds **cmds);
void		ft_close_pipes(t_direct **direct);
void		handle_io(int input, int output, int check);

// error.c
int			syntax_error(char *msg);
void		call_exit(t_main *m_var);

// free.c
void		free_lists(t_node **lists);
void		free_direct(t_direct **direct);
void		free_envp(t_envp **envp);
void		free_cmds(t_cmds **cmds);

// see.c
void		ft_see_group(t_cmds **groups);
void		ft_see(t_node **lists);

// main.c
t_node		*token_reader(t_main *m_var);
void		mini_main(t_main *m_var, t_node **lists);

//builtins
void		builtins(t_main *m_var, t_cmds **cmd_groups);
void		cdpwd(t_main *m_var, t_cmds **cmd_groups);
void		export(t_main *m_var, t_cmds **cmd_groups);
void		env(t_main *m_var);
void		exportloop(t_cmds **cmd_groups, t_envp *temp);
// void		exportutil(t_cmds **cmd_groups, t_envp *temp);
void		checkifnegative(t_cmds **cmd_groups);
void		printnumericexit(t_cmds **cmd_groups);

#endif