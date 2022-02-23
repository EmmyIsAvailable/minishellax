/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:07:05 by eruellan          #+#    #+#             */
/*   Updated: 2021/11/23 11:07:20 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*cast_dest;
	unsigned char	*cast_src;

	i = 0;
	if (!dest && !src)
		return (NULL);
	cast_dest = (unsigned char *)dest;
	cast_src = (unsigned char *)src;
	while (i < n)
	{
		cast_dest[i] = cast_src[i];
		i++;
	}
	return (dest);
}
