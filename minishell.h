/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:23:28 by ewu               #+#    #+#             */
/*   Updated: 2025/01/09 16:57:02 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h> // for read()
# include <limits.h>
# include <readline/history.h> //readline()
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_tokentype
{
	WORD, //Will be disambiguated to Command_builtin, Command_binary, argument or filename in the parser
	COMMAND_BUILTIN,
	COMMAND_BINARY,
	ARGUMENT,
	REDIRECTION, //Will be disambiguated to input, output, append or heredoc
	PIPE,
	INPUT,
	OUTPUT,
	FILENAME,
	HEREDOC,
	DELIMITER,
	APPEND,
	TOKEN_EOF
}						t_tokentype;

typedef struct s_token
{
	t_tokentype			type;
	char				*value;
}						t_token;

// todo: necessary or not?
typedef struct s_env
{
	char **env;
	int var_nb;
}			t_env;

// todo: init t_table in *init.c*
typedef struct s_table
{
	// char				*cmd;
	// char				**cmd_array;
	char				*path;
	int					arg_nb;
	int					*exit_status;

}						t_table;

typedef struct s_astnode
{
	int fd[2];
	t_token				*token;
	struct s_astnode	*right;
	struct s_astnode	*left;
	struct s_astnode	*next_arg;
	int					args_nbr;
	int					*exit_status;
	t_redir				*redirect;
	t_env				*env;
}						t_astnode;

typedef struct s_redir
{
	int					fd;
	t_token				*token;
	t_redir			*right;
	t_redir			*left;

}						t_redir;
// typedef struct s_cmd
// {
// }			t_cmd;



//organize ft
void	exec_ast(t_astnode *ast_node, int *exit_status);
char	**get_command_args(t_astnode *command_node);
int exec_command(t_astnode *astnode, int *exit_status);
int exec_builtins(t_astnode *cmd_node, int *exit_status);

// builtin ft
void ft_echo(char **args, int* exit_status);
int ft_cd(char **args, char ***env, int *exit_status);
void					ft_pwd(int* exit_status);
int						ft_export(char ***env, char **args, int *exit_status);
int ft_unset(char **args, char ***env, int *exit_status);
int						ft_env(char **env, int *exit_status);
void					ft_exit(char **args, int *exit_status);

// cd helper
static char	*cur_path(void);
void					ch_pwd_oldpwd(char **env, int flag, int *exit_status);
char					*cd_home(char **env, int *exit_status);

// env helper ft
size_t					varlen(char **env);
char					**cpy_env(char **env);
void					env_shl(char ***env, char *key);
int						find_env_var(char **env, const char *key);
char					*create_var(const char *key, char *val);
void					put_var(char ***env, char *n_var);
int						update_env(char ***env, const char *key, char *val,
							bool flg);
void					mod_val(char **env, char *key, char *val);
void					del_var(char ***env, char *key);
void					del_val(char **env, char *key);
char					*env_value(char **env, const char *key);

// export hlper
char					*smallest(char **tmp);
size_t					nonull_varlen(char **env);
char					**nonull_cpy(char **env, size_t len);
char					**sort_env(char **env);
int					exp_only(char **env, int *exit_status);
int						exp_arg(char ***env, char *arg);
int						withsigh(char ***env, char *arg, char *sign);
int						nosign(char ***env, char *arg);
bool					valid_exp(const char *arg);

// unset hpler
bool					valid_unset(const char *arg);
int						unset_env(char ***env, char *arg);

// general hlper n' wrapper
char					*safe_join(char *s1, char *s2);
void					*safe_malloc(size_t size);
void					*ft_realloc(void *ptr, size_t old, size_t new);
size_t					args_nbr(char **arr);

// error, free, exit
//void					ft_exit_status(int exit_code);
void					print_err(char *s1, char *s2, char *s3);

// redirect
int exec_redirect(t_astnode *astnode, int *exit_status);
int ft_out(t_astnode *astnode, int *exit_status);
int ft_in(t_astnode *astnode, int *exit_status);
int here_doc(char *de, int *exit_status);

// pipe
int create_pip(int fd[2], int *exit_status);
int left_node(t_astnode *pipe_node, int fd[2], int *exit_status);
int right_node(t_astnode *pipe_node, int fd[2], int *exit_status);
int exec_pipe(t_astnode *pipe_node, int *exit_status);

// temporary prototype
// char *ft_strchr(char *s, char c);
// int ft_strncmp(char *s1, char *s2);
// char *ft_strdup(char *s);

#endif