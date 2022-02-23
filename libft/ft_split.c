/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:10:11 by eruellan          #+#    #+#             */
/*   Updated: 2021/11/26 12:10:06 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nb_words(char const *s, char c)
{
	int	i;
	int	count;
	int	len;

	i = 0;
	count = 0;
	while (s[i])
	{
		len = 0;
		while (s[i + len] && s[i + len] != c)
			len++;
		if (len)
			count++;
		else
			len = 1;
		i += len;
	}
	return (count);
}

static char	*ft_strncpy(char *dest, const char *src, int n)
{
	int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	**fill_words(char **res, char const *s, char c)
{
	int	i;
	int	len;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		len = 0;
		while (s[i + len] && s[i + len] != c)
			len++;
		if (len)
		{
			res[j] = (char *)malloc(sizeof(char) * (len + 1));
			if (!res[j])
				return (NULL);
			ft_strncpy(res[j], &s[i], len);
			j++;
		}
		else
			len = 1;
		i += len;
	}
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		words;

	words = nb_words(s, c);
	split = (char **)malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (NULL);
	fill_words(split, s, c);
	split[words] = NULL;
	return (split);
}
