/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:31:26 by eruellan          #+#    #+#             */
/*   Updated: 2022/05/05 14:46:18 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait(t_data *data)
{
	pid_t	pid;
	int		wait_status;

	wait_status = 0;
	pid = 0;
	while (pid != -1)
	{
		pid = wait(&wait_status);
		if (pid == data->last_pid)
			return ;
	}
}

int	check_infile(t_heads **line, t_data *data)
{
	t_token	*tmp_in;

	tmp_in = (*line)->infile;
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
	return (0);
}

int	check_outfile(t_heads **line)
{
	t_token	*tmp_out;

	tmp_out = (*line)->outfile;
	while (tmp_out)
	{
		if (tmp_out->token == 5)
			tmp_out->fd = open(tmp_out->data, O_WRONLY
					| O_CREAT | O_TRUNC, 0664);
		else if (tmp_out->token == 7)
			tmp_out->fd = open (tmp_out->data, O_WRONLY
					| O_CREAT | O_APPEND, 0664);
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

int	ft_no_fork(t_heads **line, t_data *data, t_heads **final_line)
{
	char	**path;
	char	*tmp_binary;
	t_heads	**tmp;

	tmp = line;
	tmp_binary = NULL;
	if (*line)
	{
		path = ft_split(getenv("PATH"), ':');
		if (is_non_print_builtins((*line)->cmd) == 0)
		{
			if (!(*line)->next)
				return (non_printable_builtins((*line)->cmd, data));
			else
			{
				free_elem_heads(&(*tmp));
				return (ft_no_fork(&(*line), data, &(*final_line)));
			}
		}
		tmp_binary = get_binary((*line)->cmd->data, path);
		free_tab(path);
		if (!tmp_binary)
		{
			if (ft_strncmp((*line)->cmd->data, "exit", 4) == 0)
				return (1);
			printf("-bash: %s: command not found\n", (*line)->cmd->data);
			if ((*line)->next)
			{
				free_elem_heads(&(*tmp));
				return (ft_no_fork(&(*line), data, &(*final_line)));
			}
			else
				return (127);
		}
		free(tmp_binary);
		if ((*line))
		{
			push_heads(tmp, final_line);
			return (ft_no_fork(&(*line), data, &(*final_line)));
		}
	}
	return (2);
}
