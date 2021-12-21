/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_g_minishell.h                                     :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 16:16:14 by marvin            #+#    #+#             */
/*   Updated: 2021/05/12 16:16:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <dirent.h>
# include <string.h>
# include <stdlib.h>
# include <termios.h>

# include "../srcs/libft/libft.h"

# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

# define MS_ERROR_PARSE 1
# define MS_ERROR_TOO_MANY_ARG 2
# define MS_ERROR_TO_PERROR 3
# define MS_ERROR_NO_CMD 4
# define MS_ERROR_INVALID_QUOTE 5
# define MS_ERROR_SYNTAX 6

typedef enum e_token_type
{
	space,
	line_return,
	pipeline,
	semicolon,
	simple_redir_left,
	simple_redir_right,
	double_redir_left,
	double_redir_right,
	single_quote,
	double_quote,
	backslash,
	variable,
	literal,
	cmd_instr,
	filename,
	none
}	t_token_type;

typedef struct s_symbols
{
	char			*symbol;
	t_token_type	type;
}				t_symbols;

typedef struct s_token
{
	void			*value;
	t_token_type	type;
	int				pipe_in;
	int				pipe_out;
}					t_token;

typedef struct s_cmd
{
	t_token			*content;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct s_minishell
{
	t_cmd			*list_input;
	char			**env;
	int				last_return_value;
	t_bool			parsing_error;
	int				signal;
}					t_minishell;

t_minishell			g_minishell;

/* 
** export
*/

void				ft_exporting(t_cmd *list, char *value);

/*
** minishell
*/

void				sh_pre(void);
int					main(int argc, char **argv, char **env);
void				sigint_handler(int sig);

/* 
**	cmd_struct 
*/

void				ft_cmdadd_back(t_cmd **alst, t_cmd *new);
void				ft_cmdadd_front(t_cmd **alst, t_cmd *new);
t_cmd				*ft_cmdlast(t_cmd *lst);
t_cmd				*ft_cmdnew(void *content);
size_t				ft_cmdsize(t_cmd *lst);
t_cmd				*ft_cmdfirst(t_cmd *lst);

/*
** parser
*/

void				parsing(char *user_input);
void				pre_parsing(char *user_input);
void				tokenizer(char *input);
void				detect_cmd_type(void);
void				detect_file_type(void);

t_bool				is_there_literal_for_file(void);
void				parse_simple_redirection_left(void);
void				parse_simple_redirection_right(void);
void				parse_double_redirection_left(void);
void				parse_double_redirection_right(void);
void				parse_pipe(void);
void				assign_pipe(int *fd, t_cmd *current);
t_bool				is_there_pipe(void);

/*
** search_in_parsing
*/

t_cmd				*find_next_literal(int range);
t_cmd				*find_prev_cmd(void);
t_cmd				*find_next_cmd(void);
t_bool				ft_isstop(t_cmd *list);

/*
**	dollars.c
*/

int					replace_value_from_env(t_cmd *list);
char				*get_value_env(char *name);

/*
**	quotes.c
*/

char				*remove_quote(char *str);
int					get_quote_len(char *str);

/*
** dollar_utils_*.c
*/

char				*remove_space(char *original_str, int len, t_cmd *list);
int					get_dollar_len(char *str);

/*
**	env.c
*/

int					main_env(void);
void				print_env(t_cmd *list);
int					add_env(char *name, char *value);
char				**realloc_env(char **env, size_t size);
int					size_env(char **env);
char				*get_value_env(char *name);
char				*dollar_to_value(char *original_str, int len);

/*
** concat_tokens.c
*/

void				concat_tokens_same_type(void);
t_bool				concat_no_spaces(void);
void				concat_tokens_quotes(void);
void				concat_tokens_var(void);

/*
** utils_concat_tokens.c
*/

void				relink_nodes(void);
t_cmd				*delete_node(t_cmd *node_to_delete);

/*
** tokens
*/

t_token				*create_token(char *value, t_token_type type);
t_token_type		find_type(char c);
t_token_type		get_token_type(t_token *token);
char				*get_token_value(t_token *token);

/*
** checker.c
*/

t_bool				checking_if_quotes_even(void);
t_bool				check_path(char *cmd);
t_bool				check_exec(char *path);

/*
** errors.c
*/

void				cmd_error(void);
void				parsing_error(int error_code);

/*
** free.c
*/

void				free_list(void);

/*
** debug.c
*/

void				debug(void);
void				print_current_chain(void);

/*
** hub.c
*/

void				cmd_hub(void);
void				cmd_unset(t_cmd *list);
void				cmd_echo(t_cmd *list, int out, int in);
void				cmd_export(t_cmd *list, int out, int in);
void				cmd_execve(t_cmd *list);
void				cmd_execute(t_cmd *list, int in, int out);
void				cmd_pwd(t_cmd *list);
void				cmd_cd(t_cmd *list);
void				cmd_exit(t_cmd *list);
void				free_array(char **array);

/*
**export_utils.c
*/

int					envchr(char *value, int i);
int					ft_envplussearch(char *value);
char				*ft_plus_cut(char *value);
int					ft_envncmp(char *needle, char *env, int len);

#endif