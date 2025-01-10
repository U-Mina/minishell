/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:23:28 by ewu               #+#    #+#             */
/*   Updated: 2025/01/10 19:15:04 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h> // for read()
# include <limits.h>
# include <readline/history.h> //readline()
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>

typedef enum e_tokentype
{
	WORD, //Will be disambiguated to Command_builtin, Command_binary, argument or filename in the parser
	COMMAND,
	ARGUMENT,
	ENV_VAR,
	QUOTE,
	REDIRECTION, //Will be disambiguated to input, output, append or heredoc
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
	t_tokentype			type;
	char				*value;
}						t_token;

// typedef struct s_astnode
// {
// 	t_token				*token;
// 	struct s_astnode	*right;
// 	struct s_astnode	*left;
// 	struct s_astnode	*next_arg;
// 	t_nodetype			node_type;
// }						t_astnode;

struct s_astnode;

typedef struct s_redir
{
	t_redirtype			type;
	int					fd;
	char				*arg;
	struct s_astnode	*right; //??
	struct s_astnode	*left; //??
}				t_redir;

typedef struct s_cmd
{
	t_cmdtype	type;
	int			arg_nb;
	char		**argv;
	char		*path;
	int			*exit_status;
	//char		*cmd;//???
	//char		**cmd_array;//???
	char		**env; //or wherever it is
}				t_cmd;

//dont know what we need in this case
typedef struct s_pipe
{
	struct s_astnode	*right;
	struct s_astnode	*left;

}				t_pipe;

typedef union u_nodetype
{
	t_redir	*redirect;
	t_cmd	*cmd;
	t_pipe	*pipe;
}			t_nodetype;

typedef struct s_astnode
{
	t_token		*token;
	t_nodetype	node_type;
}				t_astnode;

//gc_list
typedef struct s_gc_list
{
	void				*allocated;
	struct s_gc_list	*next;
}	t_gc_list;

// main and init
void init_env(char **envp, t_cmd *cmd, int *exit_status);

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
char **create_env(void);
size_t					varlen(char **env);
char					**cpy_env(char **env);
void change_shlvl_oldpwd(char ***env, char *key1, char *key2);
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

// error, free, clean, exit 
//void					ft_exit_status(int exit_code);
void					print_err(char *s1, char *s2, char *s3);
void free_env(char **env);
t_gc_list				*gc_list_init(t_gc_list *gc_list);
void					*gc_malloc(size_t size, t_gc_list *gc_list);
void					*add_gc_list(void *new_alloc, t_gc_list *gc_list);
void					gc_free(void *free_ptr, t_gc_list *gc_list);
void					gc_clean(t_gc_list *gc_list);
void					*handle_error(t_gc_list *gc_list);

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

//lexer
t_token		*tokenizer(char *input, t_gc_list *gc_list);
int			count_token_max(char *input);
t_token		create_token(t_tokentype type, char *value, t_gc_list *gc_list);
char		*get_word(char *input, t_gc_list *gc_list);
char		*get_quote(char *input, char symbol, t_gc_list *gc_list);
void		free_tokens(t_token *tokens, t_gc_list *gc_list);
int			ft_isspace(char c);

//parser
t_astnode	*parse(t_token *tokens, t_gc_list *gc_list);
t_astnode	*create_astnode(t_token *token, t_gc_list *gc_list);
t_astnode	*parse_command(t_token *tokens, int *current_token, t_gc_list *gc_list);
char		**get_command_args(t_astnode *command_node, t_token *tokens, int *current_token, t_gc_list *gc_list);
t_cmdtype	get_command_type(char *command);
t_astnode	*parse_pipe(t_token *tokens, int *current_token, t_astnode *left_node, t_gc_list *gc_list);
t_astnode	*parse_redirection(t_token *tokens, int *current_token, t_astnode *left_node, t_gc_list *gc_list);
t_redirtype	get_redir_type(char *redir);
void		free_double_pointer(char **str);
//void		free_ast(t_astnode *root);

//TO BE DELETED AT THE END
//comprovations
void		print_tokens(t_token *tokens);
void		print_ast(t_astnode* ast_node, int level);

#endif