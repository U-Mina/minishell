/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:01:57 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/26 14:00:51 by ipuig-pa         ###   ########.fr       */
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
	env_val = NULL;
	if (str[i] == '?')
	{
		env_var->val = gc_itoa(data->exit_status);
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
		if (i == i_start + 1)
			env_val = gc_strdup("$");
		env_var->end = i;
		env_var->name_len = env_var->end - env_var->start - 1;
		if (!env_val)
			env_val = env_var_value(data->env, gc_substr(str, i_start + 1, env_var->name_len));//"leak" the gc_substr
		if (!env_val)
			env_val = gc_strdup("");
		env_var->val_len = ft_strlen(env_val);
		env_var->val = env_val;
	}
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

	env_val(str, &env_var, *i, data);
	tmp = gc_malloc((ft_strlen(str) + env_var.val_len + 1) * sizeof(char));
	// if (!tmp)
	// 	gc_malloc_error();
	comb_lit_env(tmp, str, &env_var);
	gc_free(str);
	(*i) = (*i) + env_var.val_len;
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
			str = expanded_str(str, &i, data);
		i++;
	}
	return (str);
}
