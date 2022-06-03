/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:02:56 by eruellan          #+#    #+#             */
/*   Updated: 2022/06/02 15:24:38 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	child(t_data *data, t_heads **line, int i)
{
	check_heredoc(line, data);
	if ((*line)->next && i % 2 == 0)
		dup2(data->pipes[1], STDOUT_FILENO);
	else if ((*line)->next && i % 2 == 1)
	{
		close(data->tmp_fd);
		data->tmp_fd = open("pipe", O_WRONLY | O_TRUNC, 0777);
		if (dup2(data->tmp_fd, STDOUT_FILENO) == -1)
			return ;
		close(data->tmp_fd);
	}
	if (i % 2 == 1)
		dup2(data->pipes[0], STDIN_FILENO);
	else if (i % 2 == 0 && i != 0)
	{
		data->tmp_fd = open("pipe", O_RDONLY, 0777);
		if (dup2(data->tmp_fd, STDIN_FILENO) == -1)
			return ;
		close(data->tmp_fd);
	}
	if (check_outfile(line) || check_infile(line))
		return ;
	ft_exec((*line)->cmd, data);
}

void	parent(t_data *data)
{
	close(data->pipes[1]);
	if (data->pid1 > 0)
		if (waitpid(data->pid1, NULL, 0) == -1)
			return ;
}

int	ft_pipex(t_data *data, t_heads **final_line, t_heads **line)
{
	int		i;
	t_heads	*next;

	next = NULL;
	i = ft_no_fork(line, data, final_line);
	if (i != -1)
		return (i);
	i = 0;
	while ((*final_line))
	{
		if (i % 2 == 0)
			pipe(data->pipes);
		if (dispatch_builtins(final_line, data) == 1)
		{
			data->pid1 = fork();
			if (data->pid1 == 0)
				child(data, final_line, i);
		}
		parent(data);
		next = (*final_line)->next;
		free_elem_heads(final_line);
		(*final_line) = next;
		i++;
	}
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
