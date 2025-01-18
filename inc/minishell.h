/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:23:28 by ewu               #+#    #+#             */
/*   Updated: 2025/01/18 16:35:20 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h> // for read()
# include <limits.h>
# include <readline/history.h> //readline()
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <termios.h>

struct	s_data;

// original_state and signal handling
typedef struct s_minishell
{
	struct sigaction	sa[2];
	struct sigaction	old_sa[2];
	struct termios		old_term;
}						t_minishell;

typedef struct s_env_var
{
	char	*val;
	int		start;
	int		end;
	int		name_len;
	int		val_len;
}			t_env_var;

typedef enum e_tokentype
{
	WORD,
	COMMAND,
	ARGUMENT,
	QUOTE,
	REDIRECTION,
	PIPE,
	TOKEN_EOF
}						t_tokentype;

typedef enum e_redirtype
{
	INPUT,
	OUTPUT,
	HEREDOC,
	APPEND
}						t_redirtype;

typedef enum e_cmdtype
{
	COMMAND_BUILTIN,
	COMMAND_BINARY
}						t_cmdtype;

typedef struct s_token
{
	t_tokentype	type;
	char		*value;
	int			env_var;
}				t_token;

typedef struct s_tokenizer
{
	t_token	*tokens;
	int		capacity;
	int		grow;
	int		count;
}			t_tokenizer;

struct	s_astnode;

// heredoc_fd is specially for heredoc<<
// heredoc need a tmp fd to hold the content, 
//and then call dup2(heredoc_fd, STDIN_FILENO(0))
typedef struct s_redir
{
	t_redirtype			type;
	int					heredoc_fd;
	char				*left; // the filename
	struct s_astnode	*right;
}						t_redir;

typedef struct s_cmd
{
	t_cmdtype	type;
	int			arg_nb;
	char		**argv;
	char		*path;
}				t_cmd;

typedef struct s_pipe
{
	struct s_astnode	*right;
	struct s_astnode	*left;

}						t_pipe;

typedef union u_nodetype
{
	t_redir	*redir;
	t_cmd	*cmd;
	t_pipe	*pipe;
}			t_nodetype;

typedef struct s_astnode
{
	t_token		*token;
	t_nodetype	node_type;
}				t_astnode;

typedef struct s_data
{
	int			exit_status;
	char		**env;
	int			heredoc_fd;
	int			o_fd[2];
	int			fd[2];
	t_token		*tokens;
	t_astnode	*ast_root;
}				t_data;

// gc_list
typedef struct s_gc_list
{
	void				*allocated;
	struct s_gc_list	*next;
}						t_gc_list;

// will add into parse_cmd later
void		init_cmd_env(char **envp, t_cmd *cmd, int *exit_status);

// main and init
void		init_minishell(t_minishell	*minishell, int ac, char **av);
void		term_minishell(t_minishell *minishell, int rv);
void		init_data(char **envp, t_data *data);
void		reset_data(t_data *data);
void		init_cmd_node(t_cmd *cmd_node);
void		init_redir_node(t_redir *redir_node);
void		init_pipe_node(t_pipe *pipe_node);

// lexer-tokenizer
t_token		*tokenizer(char *input);
void		make_eof_token(t_token *token);
void		make_word_token(t_token *token, char *input);
void		make_quote_token(t_token *token, char *input);
void		make_redir_token(t_token *token, char *input);
void		make_pipe_token(t_token *token);

// parser
t_astnode	*parse(t_token *tokens, int *ex_st);
t_astnode	*create_astnode(t_token *token);
t_astnode	*parse_cmd(t_token *tokens, int *curr_tok, int *ex_st);
t_astnode	*parse_redir(t_token *tokens, int *curr_tok, t_astnode *right_node,
				int *ex_st);
t_astnode	*parse_pipe(t_token *tokens, int *curr_tok, t_astnode *left_node,
				int *ex_st);

// free ast
void		free_double_pointer(char **str);
void		free_ast(t_astnode *ast_node);

// exec
void		exec_ast(t_astnode *ast_node, t_data *data);
void		exec_cmd(t_astnode *cmd_node, t_data *data);
int			exec_redir(t_redir *redir, t_data *data);
void		exec_heredoc(char *de, int *exit_status, t_data *data);
int			exec_in(t_redir *redir, t_data *data);
int			exec_out(t_redir *redir, t_data *data);
void		exec_pipe(t_pipe *p_node, t_data *data);
int			create_pipe(int *fd, int *exit_status);
int			exec_builtins(t_cmd *cmd, t_data *data);
void exec_inner_shell(t_data *data);
int			get_path(char *cmd, t_cmd *c_node, t_data *data);
void		child_proc(t_cmd *cmd, t_data *data);

// builtin ft
void		ft_echo(char **args, int *exit_status);
int			ft_cd(char **args, char ***env, int *exit_status);
void		ft_pwd(int *exit_status);
int			ft_export(char ***env, char **args, int *exit_status);
int			ft_unset(char **args, char ***env, int *exit_status);
int			ft_env(char **env, int *exit_status);
void		ft_exit(char **args, int *exit_status);

// cd helper
char		*cur_path(int *exit_status); //changed to non static to use in create_env
void		ch_pwd_oldpwd(char **env, int flag, int *exit_status);
char		*cd_home(char **env, int *exit_status);

// env helper ft
char		**create_env(void);
int			varlen(char **env);
char		**cpy_env(char **env);
void		change_shlvl_oldpwd(char ***env, char *key1, char *key2);
int			find_env_var(char **env, const char *key);
char		*create_newvar(const char *key, char *val);
void		put_var(char ***env, char *n_var);
int			update_env(char ***env, const char *key, char *val, bool flg);
void		mod_val(char **env, char *key, char *val);
void		del_var(char ***env, char *key);
void		del_val(char **env, char *key);
char		*env_var_value(char **env, const char *key);

// export hlper
char		*smallest(char **tmp);
int			nonull_varlen(char **env);
char		**nonull_cpy(char **env, int len);
char		**sort_env(char **env, char **sorted);
int			exp_only(char **env, int *exit_status);
int			exp_with_arg(char ***env, char *arg);
int			withsigh(char ***env, char *arg, char *sign);
int			nosign(char ***env, char *arg);
bool		valid_exp(char *arg);

// unset hpler
bool		valid_unset(char *arg);
int			unset_env(char ***env, char *arg);

// general hlper n' wrapper
char		*safe_join(char *s1, char *s2);
void		*safe_malloc(size_t size);
void		*ft_realloc(void *ptr, size_t old, size_t new);
int			args_nbr(char **arr);

// error, free, clean, exit
// void		ft_exit_status(int exit_code);
void		print_err(char *s1, char *s2, char *s3);
void		free_env(char **env);

// gc
void		*gc_malloc(size_t size);
t_gc_list	**get_gc_list(void);
void		gc_malloc_error(void);
void		add_gc_list(void *new_alloc);
void		gc_free(void *free_ptr);
void		gc_clean(void);
char		**gc_split(char const *s, char c);
char		*gc_strdup(const char *s1);
char		*gc_strjoin(char const *s1, char const *s2);
char		*gc_substr(char const *s, unsigned int start, size_t len);
char		*gc_strtrim(char const *s1, char const *set);
char		*gc_itoa(int n);

// temporary prototype
// char *ft_strchr(char *s, char c);
// int ft_strncmp(char *s1, char *s2);
// char *ft_strdup(char *s);

// signal_handler
void		init_signal_inter(struct sigaction *sa, struct sigaction *old_sa);
void		signal_handler(int signum);
void		restore_signal(struct sigaction *old_sa);
void		init_signal_exec(void);

//expand_env
char		*expand_env(char *str, int *ex_st);

//utils
int			ft_isspace(char c);

// TO BE DELETED AT THE END
// comprovations
void		print_tokens(t_token *tokens);
void		print_ast(t_astnode *ast_node, int level);

#endif