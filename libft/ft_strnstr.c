/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:15:51 by eruellan          #+#    #+#             */
/*   Updated: 2021/11/25 15:22:41 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;
	char	*cast_s1;
	char	*cast_s2;

	i = 0;
	cast_s1 = (char *)s1;
	cast_s2 = (char *)s2;
	if (!*cast_s2)
		return (&cast_s1[i]);
	while (cast_s1[i] && i < n)
	{
		j = 0;
		while (cast_s2[j] != '\0' && cast_s1[i + j] == cast_s2[j] && i + j < n)
		{	
			if (cast_s2[j + 1] == '\0')
				return (&cast_s1[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
