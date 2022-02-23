/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:06:37 by eruellan          #+#    #+#             */
/*   Updated: 2021/11/25 14:19:10 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*cast_s1;
	unsigned char	*cast_s2;
	size_t			i;

	cast_s1 = (unsigned char *)s1;
	cast_s2 = (unsigned char *)s2;
	i = 0;
	if ((!s1 && !s2) || n == 0)
		return (0);
	while (cast_s1[i] == cast_s2[i] && i < n - 1)
		i++;
	return (cast_s1[i] - cast_s2[i]);
}
