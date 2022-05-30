/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:15:17 by eruellan          #+#    #+#             */
/*   Updated: 2022/05/27 15:17:09 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*int	check_len(const char *s1, size_t n)
{
	int		i;
	size_t	len;

	i = 0;
	len = 0;
	while (s1[i] && (s1[i] == ' ' || s1[i] == '\n' || s1[i] == '\f'
			|| s1[i] == '\r' || s1[i] == '\t' || s1[i] == '\v'))
		i++;
	while (ft_isprint(s1[i + len]))
		len++;
	if (len != n)
		return (1);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (check_len(s1, n))
		return (1);
	if (n == 0)
		return (0);
	if (s1)
		while (s1[i] && s1[i] == s2[i] && i < n - 1)
			i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}*/

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char )s1[i] - s2[i]);
		i++;
	}
	return (0);
}
