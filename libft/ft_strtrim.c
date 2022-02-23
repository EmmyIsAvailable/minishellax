/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:19:58 by eruellan          #+#    #+#             */
/*   Updated: 2021/11/26 11:51:24 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_charset(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	nb_total(char *s1, char *set)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s1[len])
		len++;
	while (s1[len - 1] && is_in_charset(s1[len - 1], set))
		len--;
	if (len)
	{
		while (s1[i] && is_in_charset(s1[i], set))
			i++;
	}
	return (len - i);
}

static char	*fill_str(char *str, char *s1, char *set, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] && is_in_charset(s1[i], set))
		i++;
	while (s1[i] && j < len)
		str[j++] = s1[i++];
	str[len] = '\0';
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str_trimmed;
	char	*cast_s1;
	char	*cast_set;
	int		len;

	if (!s1 || !set)
		return (NULL);
	cast_s1 = (char *)s1;
	cast_set = (char *)set;
	len = nb_total(cast_s1, cast_set);
	str_trimmed = (char *)malloc(sizeof(char) * (len + 1));
	if (!str_trimmed)
		return (NULL);
	fill_str(str_trimmed, cast_s1, cast_set, len);
	return (str_trimmed);
}
