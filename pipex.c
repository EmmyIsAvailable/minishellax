/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:02:56 by eruellan          #+#    #+#             */
/*   Updated: 2022/06/21 12:19:52 by cdaveux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	child(t_data *data, t_heads **line, int i)
{
	check_heredoc(line, data);
	if (check_outfile(line) || check_infile(line))
		return (-1);
	if (i % 2 == 1)
	{
		dup2(data->pipes[0], STDIN_FILENO);
		close(data->pipes[1]);
	}
	else if (i % 2 == 0 && i != 0)
	{
		data->tmp_fd = open("pipe", O_RDONLY, 0777);
		if (dup2(data->tmp_fd, STDIN_FILENO) == -1)
			return (0);
		close(data->tmp_fd);
	}
	if ((*line)->next && i % 2 == 0)
	{
		dup2(data->pipes[1], STDOUT_FILENO);
		close(data->pipes[0]);
	}
	else if ((*line)->next && i % 2 == 1)
	{
		data->tmp_fd = open("pipe", O_WRONLY | O_TRUNC, 0777);
		if (dup2(data->tmp_fd, STDOUT_FILENO) == -1)
			return (0);
		close(data->tmp_fd);
	}
	event_ctrl_c(2);
	ft_exec((*line)->cmd, data);
	return (0);
}

void	parent(t_data *data, int i)
{
	int	status;

	status = 0;
	close(data->pipes[1]);
	if (i % 2 == 1)
		close (data->pipes[0]);
	event_ctrl_c(3);
	if (data->pid1 > 0)
	{
		waitpid(data->pid1, &status, 0);
		if (WTERMSIG(status) == 3)
		{
			g_global = 2;
			printf("Quit (core dumped)\n");
		}
		if (WIFEXITED(status) || WIFSIGNALED(status))
			return ;
	}
}

int	ft_pipex(t_data *data, t_heads **final_line, int i)
{
	t_heads	*next;
	int		val_ret;

	next = NULL;
	val_ret = 0;
	if (!(*final_line)->cmd)
		return (check_outfile_bis(final_line));
	if (check_infile_bis(final_line) == 1)
		return (1);
	while ((*final_line))
	{
		if (i % 2 == 0)
			pipe(data->pipes);
		if (dispatch_builtins(final_line, data) == 1)
		{
			data->pid1 = fork();
			if (data->pid1 == 0)
				val_ret = child(data, final_line, i);
		}
		parent(data, i);
		next = (*final_line)->next;
		free_elem_heads(final_line);
		(*final_line) = next;
		i++;
		if (val_ret == -1)
		{
			clear_all_heads(final_line);
			close_fds(data);
			return (1);
		}
	}
	close_fds(data);
	return (0);
}

int	ft_exit(t_heads **line)
{
	int		i;
	int		tmp;
	t_token	*cmd;

	i = -1;
	cmd = (*line)->cmd;
	while (cmd->next->data[++i])
	{
		if (i == 0 && cmd->next->data[i] == '-')
			i++;
		if (!ft_isdigit(cmd->next->data[i]))
			return (ft_exit_message(1, line));
	}
	if (cmd->next->next)
		return (ft_exit_message(2, line));
	if (ft_atoi(cmd->next->data) < 0)
	{
		clear_all_heads(line);
		return (255);
	}
	tmp = ft_atoi(cmd->next->data) % 256;
	clear_all_heads(line);
	return (tmp);
}
