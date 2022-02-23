/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:07:30 by eruellan          #+#    #+#             */
/*   Updated: 2021/11/25 14:18:42 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*cast_dest;
	unsigned char	*cast_src;

	i = -1;
	cast_dest = (unsigned char *)dest;
	cast_src = (unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	if (cast_src > cast_dest)
	{	
		while (++i < n)
			cast_dest[i] = cast_src[i];
	}
	else
	{
		while (n > 0)
		{
			cast_dest[n - 1] = cast_src[n - 1];
			n--;
		}
	}
	return (cast_dest);
}
