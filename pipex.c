/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:02:56 by eruellan          #+#    #+#             */
/*   Updated: 2022/05/06 16:44:01 by cdaveux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	ft_pipex(t_heads **final_line, t_heads **line, t_data *data)
{
	pid_t	pid;
	int		ret;

	if (pipe(data->pipes[0]) == -1)
		return (1);
	ret = ft_no_fork(line, data, final_line);
	if (ret != 2)
		return (ret);
	pid = fork();
	if (pid == 0)
	{
		if (check_infile(final_line, data) || check_outfile(final_line))
		{
			return (1);
		}
		if (((*final_line)->next))
		{
			dup2(data->pipes[0][1], STDOUT_FILENO);
			close(data->pipes[0][0]);
		}
		if (dispatch_builtins(&(*final_line), data) == 1)
			ft_exec((*final_line)->cmd, data);
	}
	else if (pid > 0)
		data->last_pid = pid;
	close(data->pipes[0][1]);
	return (ft_pipex_final(final_line, data));
}

int	ft_pipex_bis(t_heads **line, t_data *data, int mult_pipes)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{	
		if (check_infile(&(*line), data)
			|| check_outfile(&(*line)))
		{
			return (1);
		}
		if (mult_pipes == 0)
			dup2(data->pipes[0][0], STDIN_FILENO);
		else if (mult_pipes == 1)
			dup2(data->pipes[1][0], STDIN_FILENO);
		if (dispatch_builtins(&(*line), data) == 1)
			ft_exec((*line)->cmd, data);
	}
	else if (pid > 0)
		data->last_pid = pid;
	close(data->pipes[0][0]);
	close(data->pipes[0][1]);
	return (0);
}

int	ft_pipex_final(t_heads **line, t_data *data)
{
	int		mult_pipes;
	t_heads	*tmp;

	tmp = (*line)->next;
	free_elem_heads(&(*line));
	(*line) = tmp;
	mult_pipes = 0;
	if ((*line) && (*line)->next)
		mult_pipes = multiple_pipes(line, data);
	if ((*line))
		ft_pipex_bis(line, data, mult_pipes);
	ft_wait(data);
	clear_all_heads(line);
	return (0);
}

int	multiple_pipes(t_heads **line, t_data *data)
{
	pid_t	pid;

	while ((*line) && (*line)->next)
	{
		pipe(data->pipes[1]);
		pid = fork();
		if (pid == 0)
		{	
			if (check_infile(line, data) || check_outfile(line))
			{
				return (1);
			}
			dup2(data->pipes[0][0], STDIN_FILENO);
			dup2(data->pipes[1][1], STDOUT_FILENO);
			close(data->pipes[1][0]);
			if (dispatch_builtins(&(*line), data) == 1)
				ft_exec((*line)->cmd, data);
		}
		else if (pid > 0)
			data->last_pid = pid;
		close(data->pipes[0][0]);
		close(data->pipes[1][1]);
	}
	return (1);
}
