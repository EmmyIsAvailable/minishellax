/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:25:22 by eruellan          #+#    #+#             */
/*   Updated: 2022/06/09 10:26:06 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_token(t_token *token)
{
	int		i;
	t_token	*tmp;

	tmp = token;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	close_fds(t_data *data)
{
	close(data->pipes[0]);
	close(data->pipes[1]);
}
