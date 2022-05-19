/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:02:56 by eruellan          #+#    #+#             */
/*   Updated: 2022/05/19 14:47:06 by cdaveux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	child(t_data *data, t_heads **line, int i)
{
	int	tmp;

	check_heredoc(line, data);
	if ((*line)->next && i % 2 == 0)
		dup2(data->pipes[1], STDOUT_FILENO);
	else if ((*line)->next && i % 2 == 1)
	{
		close(data->tmp_fd);
		data->tmp_fd = open("pipe", O_WRONLY | O_TRUNC, 0777);
		if (dup2(data->tmp_fd, STDOUT_FILENO) == -1)
			return ;
	}
	if (i == 0 || i % 2 == 1)
		dup2(data->pipes[0], STDIN_FILENO);
	else if (i % 2 == 0)
	{
		tmp = open("pipe", O_RDONLY, 0777);
		if (dup2(tmp, STDIN_FILENO) == -1)
			return ;
	}
	if (check_outfile(line) || check_infile(line))
		return ;
	ft_exec((*line)->cmd, data);
}

void	parent(t_data *data, t_heads **line)
{
	if ((*line)->next)
		close(data->pipes[1]);
	if (data->pid1 > 0)
		if (waitpid(data->pid1, NULL, 0) == -1)
			return ;
}

int	ft_pipex(t_data *data, t_heads **final_line, t_heads **line)
{
	int		ret;
	int		i;
	t_heads		*next;

	i = 0;
	next = NULL;
	ret = ft_no_fork(line, data, final_line);
	if (ret != 2)
		return (ret);
	data->tmp_fd = open("pipe", O_CREAT | O_RDWR | O_TRUNC, 0777);
	while ((*final_line))
	{
		if (i % 2 == 0)
		{
			if (pipe(data->pipes) == -1)
				return (1);
		}
		if (dispatch_builtins(final_line, data) == 1)
		{
			data->pid1 = fork();
			if (data->pid1 == 0)
				child(data, final_line, i);
		}
		parent(data, final_line);
		next = (*final_line)->next;
		free_elem_heads(final_line);
		(*final_line) = next;
		i++;
	}
	unlink("pipe");
	return (0);
}
