/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:23:28 by ewu               #+#    #+#             */
/*   Updated: 2025/01/15 17:17:31 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "token.h"
# include "parse.h"
# include <errno.h>
# include <fcntl.h> // for read()
# include <limits.h>
# include <readline/history.h> //readline()
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>

struct s_data;

// original_state and signal handling
typedef struct s_minishell
{
	struct sigaction	sa[2];
	struct sigaction	old_sa[2];
	struct termios		old_term;
}						t_minishell;

struct s_astnode;

typedef struct s_data
{
	int					*exit_status;
	char				**env;
	struct s_astnode	*ast_root;
}						t_data;

// gc_list
typedef struct s_gc_list
{
	void				*allocated;
	struct s_gc_list	*next;
}						t_gc_list;

// will add into parse_cmd later
void					init_cmd_env(char **envp, t_cmd *cmd, int *exit_status);

// main and init
void					init_minishell(t_minishell *minishell);
void					term_minishell(t_minishell *minishell, int rv);
void					init_data(char **envp, t_data *data, int *exit_status);

// cmd exec ft
void					get_path(t_data *data);

// organize ft
void					exec_at_top(t_data *data);
void exec_with_pipe(t_data *data);
void					exec_after_top(t_data *data);

void					child_proc(t_data *data);
// void	exec_ast(t_astnode *ast_node, int *exit_status);
// int exec_command(t_astnode *astnode, int *exit_status);
int						exec_builtins(t_data *data);

// builtin ft
void					ft_echo(char **args, int *exit_status);
int						ft_cd(char **args, char ***env, int *exit_status);
void					ft_pwd(int *exit_status);
int						ft_export(char ***env, char **args, int *exit_status);
int						ft_unset(char **args, char ***env, int *exit_status);
int						ft_env(char **env, int *exit_status);
void					ft_exit(char **args, int *exit_status);

// cd helper
static char				*cur_path(int *exit_status);
void					ch_pwd_oldpwd(char **env, int flag, int *exit_status);
char					*cd_home(char **env, int *exit_status);

// env helper ft
char					**create_env(void);
size_t					varlen(char **env);
char					**cpy_env(char **env);
void					change_shlvl_oldpwd(char ***env, char *key1,
							char *key2);
int						find_env_var(char **env, const char *key);
char					*create_newvar(const char *key, char *val);
void					put_var(char ***env, char *n_var);
int						update_env(char ***env, const char *key, char *val,
							bool flg);
void					mod_val(char **env, char *key, char *val);
void					del_var(char ***env, char *key);
void					del_val(char **env, char *key);
char					*env_var_value(char **env, const char *key);

// export hlper
char					*smallest(char **tmp);
size_t					nonull_varlen(char **env);
char					**nonull_cpy(char **env, size_t len);
char					**sort_env(char **env);
int						exp_only(char **env, int *exit_status);
int						exp_with_arg(char ***env, char *arg);
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
// void					ft_exit_status(int exit_code);
void					print_err(char *s1, char *s2, char *s3);
void					free_env(char **env);

// gc
void					*gc_malloc(size_t size);
t_gc_list				**get_gc_list(void);
void					gc_malloc_error(void);
void					add_gc_list(void *new_alloc);
void					gc_free(void *free_ptr);
void					gc_clean(void);
char					**gc_split(char const *s, char c);
char					*gc_strdup(const char *s1);
char					*gc_strjoin(char const *s1, char const *s2);
char					*gc_substr(char const *s, unsigned int start,
							size_t len);

// redirect
int						handle_redir_fd(t_data *data);
int						check_redir(t_data *data);
int						ft_out(t_data *data);
int						ft_in(t_data *data);
int						here_doc(char *de, int *exit_status);
//void					exec_redir(t_astnode *astnode, int *exit_status);

// pipe
int						create_pip(int fd[2], int *exit_status);
int						left_node(t_astnode *astnode, int fd[2],
							int *exit_status);
int						right_node(t_astnode *astnode, int fd[2],
							int *exit_status);
void						exec_pipe(t_data *data);

// temporary prototype
// char *ft_strchr(char *s, char c);
// int ft_strncmp(char *s1, char *s2);
// char *ft_strdup(char *s);

// signal_handler
void					init_signal_inter(struct sigaction *sa,
							struct sigaction *old_sa);
void					signal_handler(int signum);
void					restore_signal(struct sigaction *old_sa);
void					init_signal_exec(void);

// TO BE DELETED AT THE END
// comprovations
void					print_tokens(t_token *tokens);
void					print_ast(t_astnode *ast_node, int level);

#endif