/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:11:50 by eruellan          #+#    #+#             */
/*   Updated: 2021/11/26 11:47:25 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new;
	int		length;
	int		i;

	length = ft_strlen(s);
	i = -1;
	new = (char *)malloc(sizeof(char) * (length + 1));
	if (!new)
		return (NULL);
	while (++i < length)
		new[i] = s[i];
	new[i] = '\0';
	return (new);
}
