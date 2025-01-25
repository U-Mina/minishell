/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:01:57 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/25 11:26:15 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//expands the environmental variable found at the i_start position of a string (str) to its value
//fills a t_env_var structure with the info about the start, end and len of the variable in the str string
//returns a pointer to the allocated string representing the value
static void	env_val(char *str, t_env_var *env_var, int i_start, t_data *data)
{
	int		i;
	char	*env_val;

	env_var->start = i_start;
	i = i_start + 1;
	if (str[i] == '?')
	{
		env_var->val = gc_itoa(data->exit_status); // (as int or as char* ???)
		// if (!env_var->val)
		// 	gc_malloc_error();
		env_var->end = i + 1;
		env_var->name_len = env_var->end - env_var->start - 1;
		env_var->val_len = ft_strlen(env_var->val);
	}
	else
	{
		while (ft_isalnum(str[i]) || str[i] == '_')
			i++;
		env_var->end = i;
		env_var->name_len = env_var->end - env_var->start - 1;
		env_val = env_var_value(data->env, gc_substr(str, i_start + 1, env_var->name_len));//"leak" the gc_substr
		if (!env_val)// is this the expected behavior!?!
			env_val = "\0";
		env_var->val_len = ft_strlen(env_val);
		env_var->val = gc_malloc(env_var->val_len + 1);
		// if (!env_var->val)
		// 	gc_malloc_error();
		ft_strlcpy(env_var->val, env_val, env_var->val_len + 1);
	}
}

//combines literal text from quotes with expanded env var value
static void	comb_lit_env(char *lit, char *str, t_env_var *env_var)
{
	ft_strlcpy(lit, str, env_var->start + 1);
	ft_strlcpy(lit + env_var->start, env_var->val, env_var->val_len + 1);
	ft_strlcpy(lit + env_var->start + env_var->val_len, str + env_var->end, \
											ft_strlen(lit) - env_var->end + 1);
	gc_free(env_var->val);
}

char	*expand_env(char *str, t_data *data)
{
	int			i;
	int			str_len;
	char		*tmp;
	t_env_var	env_var;
	int			d_quote_st;
	int			d_quote_end;

	str_len = ft_strlen(str);
	i = 0;
	d_quote_st = ft_strlen(str);
	d_quote_end = -1;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' && i < d_quote_st && i > d_quote_end)
		{
			d_quote_st = i;
			if (quote_len(str, i) >= 0)
				d_quote_end = i + quote_len(str, i);
		}
		if (str[i] == '\'' && i < d_quote_st && i > d_quote_end)
		{
			if (quote_len(str, i) >= 0)
				i = i + quote_len(str, i);
		}
		if (str[i] == '$')
		{
			env_val(str, &env_var, i, data);
			tmp = gc_malloc((str_len + env_var.val_len + 1) * sizeof(char));
			// if (!tmp)
			// 	gc_malloc_error();
			comb_lit_env(tmp, str, &env_var);
			gc_free(str); //gc will have to check that str is really in gc list, because for the content in redir heredoc, it is allocated with readline, and will not be in gc list
			str = tmp;
			i = i + env_var.val_len;
			str_len = ft_strlen(str);
		}
		i++;
	}
	return (str);
}
