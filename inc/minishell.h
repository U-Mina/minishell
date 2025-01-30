/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:23:28 by ewu               #+#    #+#             */
/*   Updated: 2025/01/30 15:11:37 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
#include <sys/stat.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <termios.h>
# include <unistd.h>

# define SIGINT_I 2
# define SIGINT_H 3
# define SIGEOF 4

volatile sig_atomic_t	g_signal;

struct					s_data;

// original_state and signal handling
typedef struct s_minishell
{
	struct sigaction	sa[2];
	struct sigaction	old_sa[2];
	struct termios		term;
	struct termios		old_term;
}						t_minishell;

//tokens
typedef enum e_tokentype
{
	WORD,
	COMMAND,
	ARGUMENT,
	REDIRECTION,
	PIPE,
	TOKEN_EOF
}						t_tokentype;

typedef enum e_redirtype
{
	INPUT,
	OUTPUT,
	HEREDOC,
	HEREDOC_Q,
	APPEND
}						t_redirtype;

typedef enum e_cmdtype
{
	COMMAND_BUILTIN,
	COMMAND_BINARY
}						t_cmdtype;

typedef struct s_token
{
	t_tokentype			type;
	char				*value;
}						t_token;

typedef struct s_tokenizer
{
	t_token				*tokens;
	int					capacity;
	int					grow;
	int					count;
}						t_tokenizer;

//AST nodes
struct					s_astnode;

typedef struct s_redir
{
	t_redirtype			type;
	char				*left;
	struct s_astnode	*right;
}						t_redir;

typedef struct s_cmd
{
	t_cmdtype			type;
	int					arg_nb;
	char				**argv;
	char				*path;
}						t_cmd;

typedef struct s_pipe
{
	struct s_astnode	*right;
	struct s_astnode	*left;

}						t_pipe;

typedef union u_nodetype
{
	t_redir				*redir;
	t_cmd				*cmd;
	t_pipe				*pipe;
}						t_nodetype;

typedef struct s_astnode
{
	t_token				*token;
	t_nodetype			node_type;
}						t_astnode;

//data struct
typedef struct s_data
{
	int					exit_status;
	int					child_status;
	char				**env;
	int					heredoc_fd;
	int					o_fd[2];
	int					fd[2];
	t_token				*tokens;
	t_astnode			*ast_root;
	t_minishell			minishell;
	bool				malloc_err;
}						t_data;

//env var
typedef struct s_env_var
{
	char				*val;
	int					start;
	int					end;
	int					name_len;
	int					val_len;
}						t_env_var;

// gc_list
typedef struct s_gc_list
{
	void				*allocated;
	struct s_gc_list	*next;
}						t_gc_list;

// main and init
void					init(char **envp, t_data *data, int ac, char **av);
void					reset_data(t_data *data);
void					reset_signal(t_data *data);
void					exit_eof(t_minishell *minishell);
void					term_minishell(t_minishell *minishell, int rv);

// lexer-tokenizer
int						tokenizer(char *input, t_data *data);
int						make_eof_token(t_token *token);
int						make_word_token(t_token *token, char *input);
int						make_redir_token(t_token *token, char *input);
int						make_pipe_token(t_token *token);

// parser
int						parse(t_token *tokens, t_data *data);
t_astnode				*parse_cmd(t_token *tokens, int *curr_tok,
							t_data *data);
t_astnode				*parse_redir(t_token *tokens, int *curr_tok,
							t_astnode *right_node, t_data *data);
t_astnode				*parse_pipe(t_token *tokens, int *curr_tok,
							t_astnode *left_node, t_data *data);
t_astnode				*create_cmd_node(t_token *token);
t_astnode				*create_redir_node(t_token *token);
t_astnode				*create_pipe_node(t_token *token);
int						handle_quotes(char **str, t_data *data);
int						quote_len(char *str, int i);
void					free_ast(t_astnode *ast_node);

// exec
void					exec_ast(t_astnode *ast_node, t_data *data);
void					exec_cmd(t_astnode *cmd_node, t_data *data);
int						exec_builtins(t_cmd *cmd, t_data *data);
int						get_path(char *cmd, t_cmd *c_node, t_data *data);
void					child_proc(t_cmd *cmd, t_data *data);
t_astnode				*handle_redir_fd(t_astnode *ast_node, t_data *data);
void					exec_heredoc(char *de, int *exit_status, t_data *data,
							bool quote);
int						exec_in(t_redir *redir, t_data *data);
int						exec_out(t_redir *redir, t_data *data);
void					exec_pipe(t_pipe *p_node, t_data *data);
int						dup_err(int fd1, int std_fd);
int						create_pipe(int *fd, t_data *data);
pid_t					fork_err(int *fd);
void					get_child_status(t_data *data);

// builtin ft
void					ft_echo(char **args, int *exit_status);
int						ft_cd(char **args, char ***env, int *exit_status);
void					ft_pwd(int *exit_status);
int						ft_export(char ***env, char **args, int *exit_status);
int						ft_unset(char **args, char ***env, int *exit_status);
int						ft_env(char **env, int *exit_status);
void					ft_exit(t_data *data, char **args);

// cd helper
char					*cur_path(void);
bool					cd_home(char **env, int *exit_status);
bool					check_err_go_dir(char *path, int *exit_status);
void					handle_pwd(char *o_pwd, char ***env);

// env helper ft
char					**create_env(void);
int						varlen(char **env);
char					**cpy_env(char **env);
void					change_shlvl_oldpwd(char ***env, char *key1,
							char *key2);
int						find_env_var(char **env, const char *key);
int						update_env(char ***env, const char *key, char *val,
							bool flg);
void					mod_val(char **env, char *key, char *val);
int						del_var(char ***env, char *key);
char					*create_newvar(const char *key, char *val);
char					*env_var_value(char **env, const char *key);

// export helper
int						exp_only(char **env);
int						exp_with_arg(char ***env, char *arg);

// unset helper
bool					valid_unset(char *arg);
int						unset_env(char ***env, char *arg);

// gc
void					*gc_malloc(size_t size);
void					*gc_realloc(void *ptr, size_t old, size_t new);
t_gc_list				**get_gc_list(void);
void					gc_malloc_error(void);
void					set_malloc_error(t_data *data);
void					add_gc_list(void *new_alloc);
void					gc_free(void *free_ptr);
void					free_double_pointer(char **str);
void					gc_clean(void);
char					**gc_split(char const *s, char c);
char					*gc_strdup(const char *s1);
char					*gc_strjoin(char const *s1, char const *s2);
char					*gc_substr(char const *s, unsigned int start,
							size_t len);
char					*gc_strtrim(char const *s1, char const *set);
char					*gc_itoa(int n);

// signal_handler
void					init_signal_inter(struct sigaction *sa,
							struct sigaction *old_sa);
void					signal_handler(int signum);
void					heredoc_signal_handler(int signum);
void					restore_signal(struct sigaction *old_sa);
void					init_exec_mode(void);

// expand_env
char					*expand_env(char *str, t_data *data);

// utils
int						ft_isspace(char c);
int						ft_issep(char c);
void					print_err(char *s1, char *s2, char *s3);
int						args_nbr(char **arr);

// // comprovations
// void					print_tokens(t_token *tokens);
// void					print_ast(t_astnode *ast_node, int level);

#endif