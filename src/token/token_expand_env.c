/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:05:00 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/16 13:04:53 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//expands the environmental variable found at the i_start position of a string (input) to its value
//fills a t_env_var structure with the info about the start, end and len of the variable in the input string
//returns a pointer to the allocated string representing the value
void	env_val(char *input, t_env_var *env_var, int i_start, int *ex_st)
{
	int		i;
	char	*env_val;

	env_var->start = i_start;
	i = i_start + 1;
	if (input[i] == '?')
		env_var->val = gc_itoa(*ex_st); // (as int or as char* ???)
	else
	{
		while (ft_isalnum(input[i]) || input[i] == '_')
			i++;
		env_var->end = i;
		env_var->name_len = env_var->end - env_var->start - 1;
	}
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
	ft_strlcpy(env_var->val, env_val, env_var->val_len + 1);
}

//combines literal text from quotes with expanded env var value
void	comb_lit_env(char *lit, char *input, t_env_var *env_var)
{
	ft_strlcpy(lit, input, env_var->start + 1);
	ft_strlcpy(lit + env_var->start, env_var->val, env_var->val_len + 1);
	ft_strlcpy(lit + env_var->start + env_var->val_len, input + env_var->end, ft_strlen(lit) - env_var->end + 1);
	gc_free(env_var->val);
}

//include this function in libft?? or in utils??
//check if the passed character is an space
int	ft_isspace(char c)
{
	unsigned char	u_c;

	u_c = (unsigned char)c;
	if (u_c != c)
		return (0);
	if ((u_c >= 9 && u_c <= 13) || u_c == 32)
		return (1);
	return (0);
}