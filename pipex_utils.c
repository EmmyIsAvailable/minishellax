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

void	ft_free_path(char **path)
{
	int	i;

	i = -1;
	while (path[++i])
		free(path[i]);
	free(path);
}

/*int	first_round(t_heads **tmp, t_data *data, char **path)
{
	t_heads *trash;

	trash = NULL;
	while (*tmp)
	{
		if (is_non_print_builtins((*tmp)->cmd) == 0 && (*tmp)->next)
		{	
				push_heads(&(*tmp), &trash); //free_elem_heads(&(*tmp));
				return (first_round(&(*tmp), data, path));
		}
		if (!get_binary((*tmp)->cmd->data, path))
		{
			if (ft_strncmp((*tmp)->cmd->data, "exit", 4) == 0)
				return (1);
			printf("-bash: %s: command not found\n", (*tmp)->cmd->data);
			if ((*tmp)->next)
			{
				push_heads(&(*tmp), &trash); //free_elem_heads(&(*tmp));
				return (first_round(&(*tmp), data, path));
			}
			else
				return (127);
		}
		(*tmp) = (*tmp)->next;
	}
	return (2);
}

int	ft_no_fork(t_heads **line, t_data *data)
{
	char 	**path;
	int		ret;
	t_heads	*tmp;

	//utiliser un tmp pour parcourir toute la liste et ne laisser
	//que les derniers elem si ils sont bons
	// si une cmd bonne n'est pas la derniere ou la premiere des bonnes 
	// alors on la push trash aussi 

	tmp = *line;
	path = ft_split(getenv("PATH"), ':');
	ret = first_round(&tmp, data, path);
	//ft_print_line(&tmp);
	ft_free_path(path);
	line = &tmp;
	
	if (is_non_print_builtins(tmp->cmd) == 0)
	{
		if (!tmp->next)
			return (non_printable_builtins(tmp->cmd, data));
		else
		{
			push_heads(&tmp, &trash); //(*line) = (*line)->next;
			return (ft_no_fork(&(tmp), data));
		}
	}
	return (ret);
}*/


int	ft_no_fork(t_heads **line, t_data *data, t_heads **final_line)
{
	char **path;
	t_heads	**tmp;

	tmp = line;
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
	if (!get_binary((*line)->cmd->data, path))
	{
		ft_free_path(path);
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
	if ((*line)->next)
	{
		push_heads(&(*line), &(*final_line));
		return (ft_no_fork(&(*line), data, &(*final_line)));
	}
	return (2);
}
