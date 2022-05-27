/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrimone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:41:05 by eruellan          #+#    #+#             */
/*   Updated: 2022/05/27 15:41:08 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrimone(char *str, char c)
{
	char	*ret;
	int		i;

	i = 0;
	if (ft_check(str, c) == 0)
		return (NULL);
	ret = malloc(sizeof(char) * ft_strlen(str));
	if (!ret)
		return (NULL);
	while (str[i] && str[i] != c)
	{
		ret[i] = str[i];
		i++;
	}
	while (str[i] && str[i + 1])
	{
		ret[i] = str[i + 1];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
