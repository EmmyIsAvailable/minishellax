/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaveux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:54:43 by cdaveux           #+#    #+#             */
/*   Updated: 2022/04/22 13:13:48 by cdaveux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_in(char const *s, char *c, int i)
{
	int	len;
	int	k;

	len = 0;
	k = 0;
	while (s[i + len])
	{
		k = 0;
		while (c[k] && s[i + len] != c[k])
			k++;
		if (c[k] != '\0')
			break ;
		len++;
	}
	return (len);
}

static int	nb_words(char const *s, char *c)
{
	int	i;
	int	count;
	int	len;

	i = 0;
	count = 0;
	while (s[i])
	{
		len = is_in(s, c, i);
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

static char	**fill_words(char **res, char const *s, char *c)
{
	int	i;
	int	len;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		len = is_in(s, c, i);
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

char	**ft_split_bis(char const *s, char *c)
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
