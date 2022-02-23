/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:08:07 by eruellan          #+#    #+#             */
/*   Updated: 2021/11/23 11:08:19 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*cast_s;	

	i = 0;
	cast_s = (char *)s;
	while (i < n)
	{
		cast_s[i] = c;
		i++;
	}
	return (cast_s);
}
