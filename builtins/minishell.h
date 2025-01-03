/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:23:28 by ewu               #+#    #+#             */
/*   Updated: 2025/01/01 20:28:12 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h> // for read()
# include <limits.h>
# include <readline/history.h> //readline()
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_cmd
{
	char	*cmd;
	char	**cmd_array;
	char	*path;
	int		arg_nb;

}			t_cmd;

typedef struct s_table
{
	// int		*exit_status;

}			t_table;

// typedef struct s_env // todo: necessary or not?
// {
// 	char **envar;
// 	char *shlv; // not sure
// 	int var_nb;

// }			t_env;

// builtin ft
void		ft_echo(char **args);
int			ft_cd(char **args, char ***env);
void		ft_pwd(void);
int ft_export(char ***env, char **args);
int			ft_unset(char **args, char ***env);
int			ft_env(char **env);
void		ft_exit(char **args);

// cd helper
static char	*cur_path(void); // check or int* exit_status as arg?
void		ch_pwd_oldpwd(char **env, int flag);
char		*cd_home(char **env);

// env helper ft
size_t		varlen(char **env);
char		**cpy_env(char **env);
void		env_shl(char ***env, char *key);
int			find_env_var(char **env, const char *key);
char		*create_var(const char *key, char *val);
void		put_var(char ***env, char *n_var);
int			update_env(char ***env, const char *key, char *val, bool flg);
void		mod_val(char **env, char *key, char *val);
void		del_var(char ***env, char *key);
void		del_val(char **env, char *key);
char		*env_value(char **env, const char *key);

// export hlper
char		*smallest(char **tmp);
size_t		nonull_varlen(char **env);
char		**nonull_cpy(char **env, size_t len);
char		**sort_env(char **env);
void		exp_only(char **env);
int		exp_arg(char ***env, char *arg);
int			withsigh(char ***env, char *arg, char *sign);
int			nosign(char ***env, char *arg);
bool		valid_exp(const char *arg);

// unset hpler
bool		valid_unset(const char *arg);
int			unset_env(char ***env, char *arg);

// general hlper n' wrapper
char		*safe_join(char *s1, char *s2);
void		*safe_malloc(size_t size);
void		*ft_realloc(void *ptr, size_t old, size_t new);
size_t		args_nbr(char **arr);

// error, free, exit
void		ft_exit_status(int exit_code);
void		print_err(char *s1, char *s2, char *s3);

// temporary prototype
// char *ft_strchr(char *s, char c);
// int ft_strncmp(char *s1, char *s2);
// char *ft_strdup(char *s);

#endif