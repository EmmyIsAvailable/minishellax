/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strrchr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:19:31 by eruellan          #+#    #+#             */
/*   Updated: 2021/11/26 12:12:23 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*cast_s;

	cast_s = (char *)s;
	i = ft_strlen(cast_s);
	if (c == '\0')
		return (&cast_s[i]);
	while (i)
	{
		if (cast_s[i] == c)
			return (&cast_s[i]);
		i--;
	}
	if (cast_s[0] == c)
		return (cast_s);
	return (NULL);
}
