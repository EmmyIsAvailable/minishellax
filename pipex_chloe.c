/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_chloe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:02:56 by eruellan          #+#    #+#             */
/*   Updated: 2022/07/07 12:48:44 by cdaveux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	clear_elem(t_heads **final_line)
{
	t_heads	*next;

	next = NULL;
	next = (*final_line)->next;
	free_elem_heads(final_line);
	(*final_line) = next;
}

int	child(t_data *data, t_heads **line)
{
	check_heredoc(line, data);
	if (check_outfile(line) || check_infile(line))
		return (-1);
	dup2(data->tmp_fd, STDIN_FILENO);
	close (data->tmp_fd);
	event_ctrl_c(2);
	if (!is_builtin(line, data)) //builtins > on fork avant le pipe
	{
		ft_exec((*line)->cmd, data);
		exit(EXIT_FAILURE);
	}
	else 
		dispatch_builtins(line, data);
	return (0);
}

void	parent(t_data *data, t_heads **line)
{
	int		status;

	status = 0;
	event_ctrl_c(3);
	if (!(*line)->next)
	{
		close (data->tmp_fd);
		while (wait(&status) != -1)
		{
		}
		if (WTERMSIG(status) == 3)
		{
			g_global = 2;
			write(STDERR_FILENO, "Quit (core dumped)\n", 19);
		}
		if (WIFEXITED(status) || WIFSIGNALED(status))
			return ;
		data->tmp_fd = dup(STDIN_FILENO);
	}
	else
	{
		close (data->tmp_fd);
		close(data->pipe_fd[1]);
		data->tmp_fd = data->pipe_fd[0];
	}
}

int	ft_pipex(t_data *data, t_heads **final_line, int i)
{
	(void)i;
	data->tmp_fd = dup(STDIN_FILENO);
	if (!(*final_line)->cmd)
		return (check_outfile_bis(final_line));
	if (check_infile_bis(final_line) == 1)
		return (1);
	while ((*final_line))
	{
		if (is_builtin(final_line, data) && !(*final_line)->next)
			dispatch_builtins(final_line, data);
		else 
		{
			if ((*final_line)->next)
				pipe(data->pipe_fd);
			data->pid1 = fork();
			if (data->pid1 == 0)
			{
				if ((*final_line)->next)
				{
					dup2(data->pipe_fd[1], STDOUT_FILENO);
					close(data->pipe_fd[0]);
					close(data->pipe_fd[1]);
				}
				if (child(data, final_line) == -1)
					return (clear_all_heads(final_line));
			}
			else
				parent(data, final_line);
		}
		clear_elem(&(*final_line));
	}
	close(data->tmp_fd);
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
