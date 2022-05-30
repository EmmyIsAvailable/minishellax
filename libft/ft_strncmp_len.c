/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:11:31 by eruellan          #+#    #+#             */
/*   Updated: 2022/05/30 15:19:35 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_len(const char *s1, size_t n)
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

int	ft_strncmp_len(const char *s1, const char *s2, size_t n)
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
}
