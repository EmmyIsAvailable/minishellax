/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:11:15 by eruellan          #+#    #+#             */
/*   Updated: 2021/11/23 16:33:56 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*cast_s;

	i = 0;
	cast_s = (char *)s;
	while (cast_s[i])
	{
		if (cast_s[i] == c)
			return (&cast_s[i]);
		i++;
	}
	if (c == '\0')
		return (&cast_s[i]);
	return (NULL);
}
