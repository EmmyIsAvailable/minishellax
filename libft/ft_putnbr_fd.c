/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:09:18 by eruellan          #+#    #+#             */
/*   Updated: 2021/11/25 15:56:46 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_aff_nb(long int nb, int fd)
{
	if (nb > 9)
	{
		ft_aff_nb(nb / 10, fd);
		ft_putchar_fd(nb % 10 + 48, fd);
	}
	else
		ft_putchar_fd(nb % 10 + 48, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	long int	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb *= (-1);
	}
	ft_aff_nb(nb, fd);
}
