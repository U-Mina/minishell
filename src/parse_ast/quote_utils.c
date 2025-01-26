/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:35:25 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/26 16:13:13 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//returns the length of a quoted chunk
int	quote_len(char *str, int i)
{
	int	j;

	j = 1;
	while (str[i + j] != str[i])
		j++;
	if (j >= (int)ft_strlen(str + i))
		return (-1);
	return (j);
}

//removes the quotes of a given string at a position o and its pair, returning the index of the first char after the last removed quote
static int	del_quotes(char **str, int o)
{
	int		rv;
	char	quote;
	int		i;
	int		j;

	i = o;
	rv = -1;
	quote = (*str)[i];
	j = 1;
	while ((*str)[i + j] != '\0')
	{
		if ((*str)[i + j] == quote && j == 1)
		{
			rv = rv + i + j - o;
			j = 2;
		}
		(*str)[i] = (*str)[i + j];
		i++;
	}
	(*str)[i] = '\0';
	return (rv);
}

//handle the quotes of a string, deleting pairs of quotes
int	handle_quotes(char **str)
{
	char	*res;
	int		i;
	int		o_len;
	int		q_len;

	o_len = ft_strlen(*str);
	i = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] == '\'' || (*str)[i] == '\"')
		{
			q_len = del_quotes(str, i);
			if (q_len < 0)
				return (-1);
			i = i + q_len;
		}
		else
			i++;
	}
	if (o_len == i)
		return (0);
	res = gc_malloc((i + 1) * sizeof(char));
	ft_strlcpy(res, *str, i + 1);
	gc_free((*str));
	*str = res;
	return (1);
}
