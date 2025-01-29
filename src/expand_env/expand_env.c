/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:01:57 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/29 12:42:38 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//PART OF ENV_VAL (see later)
static int	env_val_name(char *str, t_env_var *env_var, int i, t_data *data)
{
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (i == env_var->start + 1)
	{
		env_var->val = gc_strdup("$");
		if (!env_var->val)
			return (set_malloc_error(data), 0);
	}
	env_var->end = i;
	env_var->name_len = env_var->end - env_var->start - 1;
	if (!env_var->val)
	{
		env_var->val = gc_substr(str, env_var->start + 1, env_var->name_len);
		if (!env_var->val)
			return (set_malloc_error(data), 0);
		env_var->val = env_var_value(data->env, env_var->val);
	}
	if (!env_var->val)
		env_var->val = gc_strdup("");
	if (!env_var->val)
		return (set_malloc_error(data), 0);
	env_var->val_len = ft_strlen(env_var->val);
	return (1);
}

//Together with env_val_name, expands the environmental variable found at the i_start position of a string (str) to its value
//fills a t_env_var structure with the info about the start, end and len of the variable in the str string
//returns a pointer to the allocated string representing the value
static int	env_val(char *str, t_env_var *env_var, int i_start, t_data *data)
{
	int		i;

	env_var->start = i_start;
	i = i_start + 1;
	env_var->val = NULL;
	if (str[i] == '?')
	{
		env_var->val = gc_itoa(data->exit_status);
		if (!env_var->val)
			return (set_malloc_error(data), 0);
		env_var->end = i + 1;
		env_var->name_len = env_var->end - env_var->start - 1;
		env_var->val_len = ft_strlen(env_var->val);
		return (1);
	}
	else
		return (env_val_name(str, env_var, i, data));
}

//combines literal text from quotes with expanded env var value
static void	comb_lit_env(char *lit, char *str, t_env_var *env_var)
{
	ft_strlcpy(lit, str, env_var->start + 1);
	ft_strlcpy(lit + env_var->start, env_var->val, env_var->val_len + 1);
	ft_strlcpy(lit + env_var->start + env_var->val_len, str + env_var->end, \
											ft_strlen(str) - env_var->end + 1);
	gc_free(env_var->val);
}

static char	*expanded_str(char *str, int *i, t_data *data)
{
	t_env_var	env_var;
	char		*tmp;

	if (!env_val(str, &env_var, *i, data))
		return (set_malloc_error(data), NULL);
	tmp = gc_malloc((ft_strlen(str) + env_var.val_len + 1) * sizeof(char));
	if (!tmp)
		return (set_malloc_error(data), NULL);
	comb_lit_env(tmp, str, &env_var);
	gc_free(str);
	(*i) = (*i) + env_var.val_len - 1;
	return (tmp);
}

char	*expand_env(char *str, t_data *data)
{
	int		i;
	bool	d_quote_flag;

	i = 0;
	d_quote_flag = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
			d_quote_flag = !d_quote_flag;
		if (str[i] == '\'' && !d_quote_flag)
		{
			if (quote_len(str, i) >= 0)
				i = i + quote_len(str, i);
		}
		if (str[i] == '$')
		{
			str = expanded_str(str, &i, data);
			if (!str)
				return (set_malloc_error(data), NULL);
		}
		i++;
	}
	return (str);
}
