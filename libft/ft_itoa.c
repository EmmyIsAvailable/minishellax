/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:53:54 by eruellan          #+#    #+#             */
/*   Updated: 2021/11/23 10:54:33 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nb_digits(long int n)
{
	int	digits;

	digits = 0;
	if (n < 0)
	{
		n *= (-1);
		digits++;
	}
	while (n > 9)
	{
		n = n / 10;
		digits++;
	}
	return (digits + 1);
}

static char	*fill_numbers(long int n, char *tofill, int len)
{
	if (n > 9)
		fill_numbers((n / 10), tofill, (len - 1));
	tofill[len - 1] = n % 10 + 48;
	return (tofill);
}

char	*ft_itoa(int n)
{
	char		*number;
	int			digits;
	long int	nb;

	nb = n;
	digits = nb_digits(nb);
	number = (char *)malloc(sizeof(char) * (digits + 1));
	if (!number)
		return (NULL);
	if (nb < 0)
	{
		number[0] = '-';
		nb *= (-1);
	}
	fill_numbers(nb, number, digits);
	number[digits] = '\0';
	return (number);
}
