/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:31:26 by eruellan          #+#    #+#             */
/*   Updated: 2022/04/14 16:13:43 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait(t_data *data)
{
	pid_t	pid;
	int	wait_status;

	wait_status = 0;
	pid = 0;
	while (pid != -1)
	{
		pid = wait(&wait_status);
		if (pid == data->last_pid)
			return ;
	} 
}

int	check_in_outfile(t_heads **line, t_data *data)
{
	t_token	*tmp_in;
	t_token	*tmp_out;

	tmp_in = (*line)->infile;
	tmp_out = (*line)->outfile;
	while (tmp_in)
	{
		if (tmp_in->token == 8)
			is_heredoc(tmp_in->data, data);
		tmp_in->fd = open(tmp_in->data, O_RDONLY);
		if (tmp_in->fd < 0)
		{
			perror("Open infile failed");
			return (1);
		}
		else
		{
			dup2(tmp_in->fd, STDIN_FILENO);
			close(tmp_in->fd);
			if (tmp_in->token == 8)
				unlink(tmp_in->data);
		}
		tmp_in = tmp_in->next;
	}
	while (tmp_out)
	{
		if (tmp_out->token == 5)
			tmp_out->fd = open(tmp_out->data, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		else if (tmp_out->token == 7)
			tmp_out->fd = open (tmp_out->data, O_WRONLY | O_CREAT | O_APPEND, 0664);
		if (tmp_out->fd < 0)
		{
			perror("Open outfile failed");
			return (1);
		}
		else
		{
			dup2(tmp_out->fd, STDOUT_FILENO);
			close(tmp_out->fd);
		}
		tmp_out = tmp_out->next;
	}
	return (0);
}

int     ft_pipex(t_heads **line, t_data *data, t_token **shlvl)
{
	pid_t	pid;
	(void)shlvl;

        data->pipes[0] = data->pipe0;
        data->pipes[1] = data->pipe1;
	if (pipe(data->pipes[0]) == -1)
		return (1);
	if (is_non_print_builtins((*line)->cmd) == 0)
	{
		if (!(*line)->next)
		{
			non_printable_builtins((*line)->cmd, data);
        		return (0);
		}
		else
			(*line) = (*line)->next;
	}
	pid = fork();
	if (pid == 0)
        {
		if (check_in_outfile(line, data) == 1)
			return (1);
		if (((*line)->next))
		{
                	dup2(data->pipes[0][1], STDOUT_FILENO);
                	close(data->pipes[0][0]);
		}
               	if (dispatch_builtins((*line)->cmd, data) == 1)
			ft_exec((*line)->cmd, data);
        }
	else if (pid > 0)
		data->last_pid = pid;
	close(data->pipes[0][1]);
	return (ft_pipex_bis(line, data));
}

int	ft_pipex_bis(t_heads **line, t_data *data)
{
	pid_t	pid;
	int	mult_pipes;

	mult_pipes = 0;
	if ((*line)->next && (*line)->next->next)
		mult_pipes = multiple_pipes(line, data);
	if ((*line)->next)
        {
		pid = fork();
		if (pid == 0)
        	{	
			if (check_in_outfile(&(*line)->next, data) == 1)
				return (1);
			if (mult_pipes == 0)
                		dup2(data->pipes[0][0], STDIN_FILENO);
			else if (mult_pipes == 1)
				dup2(data->pipes[1][0], STDIN_FILENO);
			if (dispatch_builtins((*line)->next->cmd, data) == 1)
         	    		ft_exec((*line)->next->cmd, data);
        	}
		else if (pid > 0)
			data->last_pid = pid;
		close(data->pipes[0][0]);
		close(data->pipes[0][1]);
	}
	ft_wait(data);
        return (0);
}

int	multiple_pipes(t_heads **line, t_data *data)
{
	pid_t	pid;

	while ((*line)->next && (*line)->next->next)
       	{
		(*line) = (*line)->next;
       	        pipe(data->pipes[1]);
       	        pid = fork();
		if (pid == 0)
       	        {	
			if (check_in_outfile(line, data) == 1)
				return (1);
               	        dup2(data->pipes[0][0], STDIN_FILENO);
               	        dup2(data->pipes[1][1], STDOUT_FILENO);
              		close(data->pipes[1][0]);
			if (dispatch_builtins((*line)->cmd, data) == 1)
				ft_exec((*line)->cmd, data);
       		}
		else if (pid > 0)
			data->last_pid = pid;
               	close(data->pipes[0][0]);
              	close(data->pipes[1][1]);
       	}
	return (1);
}
