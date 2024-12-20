/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:23:28 by ewu               #+#    #+#             */
/*   Updated: 2024/12/19 17:01:25 by ewu              ###   ########.fr       */
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
	char	**cmd_arr;
	char	*path;
	int		arg_nb;
	t_env	*env;

}			t_cmd;

typedef struct s_table
{
	int		*exit_code;

}			t_table;

typedef struct s_env // todo: necessary or not?
{
	char **envar;
	char *shlv; //not sure
	int var_nb;

}			t_env;

// builtin ft

int			ft_pwd(int args);
int ft_env(t_env *cpenv);


// env helper ft
int			varlen(char **env);
char		**cpy_env(char **envp);
t_env		*init_env(char **envp);
void		mod_cpenv_var(t_env *cpenv, char *key, char *val);
void sort_cpenv_var(t_env *cpenv);


// general hlper
void		*safe_malloc(size_t size);

// temporary prototype
// char *ft_strchr(char *s, char c);
// int ft_strncmp(char *s1, char *s2);
// char *ft_strdup(char *s);

#endif