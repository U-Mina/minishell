/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:35:25 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/31 16:45:54 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//returns the length of a quoted chunk
int	quote_len(char *str, int i)
{
	int	j;

	j = 1;
	while (str[i + j] != str[i] && str[i + j] != '\0')
		j++;
	if (j >= (int)ft_strlen(str + i))
		return (-1);
	return (j);
}

//removes the quotes of a given string at a position "o" and its pair
//returning the index of the first char after the last removed quote
static int	del_quotes(char **str, int o)
{
	int		rv;
	char	quote;
	int		i;

	i = o;
	rv = 0;
	quote = (*str)[o];
	while ((*str)[i + 1] != '\0')
	{
		if ((*str)[i + 1] == quote)
		{
			rv = i - o;
			break ;
		}
		(*str)[i] = (*str)[i + 1];
		i++;
	}
	if ((*str)[i] == '\0' && rv == 0)
		return (-1);
	while ((*str)[i + 2] != '\0')
	{
		(*str)[i] = (*str)[i + 2];
		i++;
	}
	return ((*str)[i] = '\0', rv);
}

//handle the quotes of a string, deleting pairs of quotes
static int	get_new_length(char **str)
{
	int		i;
	int		q_len;

	i = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] == '\'' || (*str)[i] == '\"')
		{
			q_len = del_quotes(str, i);
			if (q_len < 0)
				return (-1);
			i = i + q_len - 1;
		}
		i++;
	}
	return (i);
}

//handle the quotes of a string, deleting pairs of quotes
int	handle_quotes(char **str, t_data *data)
{
	char	*res;
	int		n_len;
	int		o_len;

	o_len = ft_strlen(*str);
	n_len = get_new_length(str);
	if (n_len <= 0)
		return (-1);
	if (o_len == n_len)
		return (0);
	res = gc_malloc((n_len + 1) * sizeof(char));
	if (!res)
		return (set_malloc_error(data), -1);
	ft_strlcpy(res, *str, n_len + 1);
	gc_free((*str));
	*str = res;
	return (1);
}
