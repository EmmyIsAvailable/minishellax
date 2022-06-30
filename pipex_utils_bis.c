/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:25:22 by eruellan          #+#    #+#             */
/*   Updated: 2022/06/09 12:08:58 by eruellan         ###   ########.fr       */
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
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
}

void	sig_slash(int code)
{
	(void)code;
	printf("Quit (core dumped)\n");
	g_global = 2;
	return ;
}

void	sig_int2(int code)
{
	(void)code;
	write(1, "\n", 1);
	rl_on_new_line();
//	rl_replace_line("", 1);
	g_global = 1;
	return ;
}
