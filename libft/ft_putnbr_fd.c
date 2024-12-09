/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:56:47 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/11/17 12:16:51 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	n_c;

	n_c = n;
	if (n < 0)
	{
		write(fd, "-", 1);
		n_c = -n_c;
	}
	if (n_c >= 10)
	{
		ft_putnbr_fd(n_c / 10, fd);
	}
	ft_putchar_fd('0' + n_c % 10, fd);
}
