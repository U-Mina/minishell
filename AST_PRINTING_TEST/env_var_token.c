/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:05:00 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/14 15:47:34 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//extracts a quote (delimited by quote_symbol (" or ')) from the input and fills the token variables according to this
void	make_env_var_token(t_token *token, char *input)
{
	t_env_var	env_var;
	char		*env_var_val;

	env_var_val = get_env_val(input, &env_var, 0);
	// if (!env_var_val)
	// 	gc_malloc_error();
	token->value = env_var_val;
	token->i_len = env_var.end - env_var.start;
}

//expands the environmental variable to its value and returns a pointer to the allocated string representing the value
char	*get_env_val(char *input, t_env_var *env_var, int i_start)
{
	int		i;
	char	*env_val;
	char	*alloc_val;

	env_var->start = i_start;
	i = i_start + 1;
	// if (input[i] == '?')
		//expand to the exit status of the most recently executed foreground pipeline (as int or as char* ???)
	// else
	// {
		while (ft_isalnum(input[i]) || input[i] == '_')
			i++;
		env_var->end = i;
		env_var->name_len = env_var->end - env_var->start - 1;
	// }
	env_val = getenv(gc_substr(input, i_start + 1, env_var->name_len));
	if (!env_val)//proper error check!!!
	{
		printf("Non valid envvar\n");
		exit (1);
	}
	env_var->val_len = ft_strlen(env_val);
	alloc_val = gc_malloc(env_var->val_len + 1);
	// if (!env_val)
	// 	gc_malloc_error();
	ft_strlcpy(alloc_val, env_val, env_var->val_len + 1);
	env_var->val_len = ft_strlen(env_val);
	return (alloc_val);
}
