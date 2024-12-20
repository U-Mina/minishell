/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 12:25:45 by ewu               #+#    #+#             */
/*   Updated: 2024/11/08 13:37:16 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_write(char c, int *counter)
{
	int	count;

	if (*counter == -1)
		return (-1);
	count = write(1, &c, 1);
	if (count == -1)
		*counter = -1;
	else
		*counter += count;
	return (*counter);
}

/**
 * cannot write: ft_cases(char s, int toprint, int *count)
 * bc 2nd para is not fixed!!,so 'va_list' provide
 * corresponding data type everytime called
 * va_arg每次被call 都move到下一个argument
 * va_arg(toprint, data type)
 * toprint: the va_list that holds all variable args
 * data type: the type of args you expect to extrac from 'toprint'
 * if you call va_arg(toprint, int), it return the next arg in 'toprint'
 * (i.e. the va_list) as an int!!!
 * va_arg(toprint, data type) extract the next argument
 * of the given 'toprint' from 'va_list', and return it as the 'data type'
 * you write in 2nd argument
 *
 * 第一个para是被va_list define了的dynamic argument。
 */
void	ft_cases(char s, va_list toprint, int *count)
{
	if (s == 'c')
		ft_pfchar(va_arg(toprint, int), count);
	else if (s == 's')
		ft_pfstr(va_arg(toprint, char *), count);
	else if (s == 'p')
		ft_pfptr(va_arg(toprint, size_t), count);
	else if (s == 'd' || s == 'i')
		ft_pfid(va_arg(toprint, int), count);
	else if (s == 'u')
		ft_pfu(va_arg(toprint, unsigned int), count);
	else if (s == 'x')
		ft_pflowx(va_arg(toprint, unsigned int), count);
	else if (s == 'X')
		ft_pfhighx(va_arg(toprint, unsigned int), count);
	else if (s == '%')
		ft_pfchar('%', count);
	return ;
}

int	ft_printf(const char *inpt, ...)
{
	va_list	toprint;
	int		count;
	int		i;

	i = 0;
	count = 0;
	va_start(toprint, inpt);
	while (inpt[i])
	{
		if (inpt[i] == '%')
		{
			i++;
			ft_cases(inpt[i], toprint, &count);
		}
		else
			ft_pfchar(inpt[i], &count);
		i++;
	}
	va_end(toprint);
	return (count);
}
//* we dont know how many things user want dispaly
// variadic ft
// va_list the_thing_you_named
// va_start(va_list var, parameterN) = va_start(toprint, inpt)
// purpose: set stage, def which is statble and which will vary
// va_end(toprint);will free mem