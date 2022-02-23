/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:06:08 by eruellan          #+#    #+#             */
/*   Updated: 2021/11/23 11:06:23 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*cast_s;
	size_t			i;

	cast_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (cast_s[i] == (unsigned char)c)
			return ((void *)&cast_s[i]);
		i++;
	}
	return (NULL);
}
