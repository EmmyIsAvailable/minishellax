/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:12:39 by eruellan          #+#    #+#             */
/*   Updated: 2021/11/25 14:43:41 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len_s1;
	int		len_s2;
	char	*join;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	i = -1;
	join = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!join)
		return (NULL);
	while (++i < len_s1)
		join[i] = s1[i];
	i = -1;
	while (++i < len_s2)
		join[len_s1 + i] = s2[i];
	join[len_s1 + len_s2] = '\0';
	return (join);
}
