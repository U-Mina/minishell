/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_make_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:05:00 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/15 13:57:16 by ipuig-pa         ###   ########.fr       */
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

//combines literal text from quotes with expanded env var value
void	comb_quote_env(char *quote, char *input, t_env_var *env_var)
{
	ft_strlcpy(quote, input, env_var->start + 1);
	ft_strlcpy(quote + env_var->start, env_var->val, env_var->val_len + 1);
	ft_strlcpy(quote + env_var->start + env_var->val_len, input + env_var->end, quote_len - env_var->end + 1);
	gc_free(env_var->val);
}

//expands the environmental variable found at the i_start position of a string (input) to its value
//fills a t_env_var structure with the info about the start, end and len of the variable in the input string
//returns a pointer to the allocated string representing the value
void	get_env_val(char *input, t_env_var *env_var, int i_start)
{
	int		i;
	char	*env_val;

	env_var->start = i_start;
	i = i_start + 1;
	//if (input[i] == '?')
	//	env_var->val = gc_itoa(data->exit_status);
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
		exit (1);//manage correctly
	}
	env_var->val_len = ft_strlen(env_val);
	env_var->val = gc_malloc(env_var->val_len + 1);
	// if (!env_var->val)
	// 	gc_malloc_error();
	ft_strlcpy(alloc_val, env_val, env_var->val_len + 1);
	env_var->val_len = ft_strlen(env_val);
}

