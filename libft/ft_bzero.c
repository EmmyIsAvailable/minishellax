/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bzero.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:50:52 by eruellan          #+#    #+#             */
/*   Updated: 2021/11/23 10:51:30 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*cast_s;

	i = 0;
	cast_s = (unsigned char *)s;
	while (i < n)
	{
		cast_s[i] = 0;
		i++;
	}
}
