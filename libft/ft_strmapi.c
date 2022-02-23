/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strmapi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:14:51 by eruellan          #+#    #+#             */
/*   Updated: 2021/11/26 11:52:35 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			len;
	char			*new;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	i = -1;
	len = ft_strlen(s);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	while (++i < len)
		new[i] = (char)f(i, s[i]);
	new[i] = '\0';
	return (new);
}
