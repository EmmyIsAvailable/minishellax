/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:49:39 by eruellan          #+#    #+#             */
/*   Updated: 2022/05/30 16:11:28 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_heredoc(char *deli, t_data *data)
{
	char	*tmp;
	int		heredoc;
	char	*buffer;

	tmp = NULL;
	heredoc = open(deli, O_WRONLY | O_CREAT | O_APPEND, 0777);
	buffer = readline("> ");
	if (ft_strncmp(buffer, deli, (ft_strlen(deli) + 1)) != 0)
	{
		while (1)
		{
			tmp = readline("> ");
			if (buffer)
				buffer = join_elems(buffer, "\n");
			if (tmp && ft_strncmp(tmp, deli, (ft_strlen(deli) + 1)) == 0)
				break ;
			if (tmp)
				buffer = join_elems(buffer, tmp);
			free(tmp);
		}
		free(tmp);
		env_in_heredoc(heredoc, buffer, data);
	}
	return (ft_close_heredoc(heredoc, buffer));
}

int	ft_close_heredoc(int heredoc, char *buffer)
{
	close(heredoc);
	free(buffer);
	return (0);
}

char	*env_in_heredoc(int heredoc, char *buffer, t_data *data)
{
	int		i;
	char	*ret;
	char	*tmp;

	i = 0;
	ret = NULL;
	while (buffer[i])
	{
		tmp = NULL;
		while (buffer[i] && buffer[i] != '$')
		{
			write(heredoc, &buffer[i], 1);
			i++;
		}
		if (buffer[i] == '$')
		{
			i++;
			tmp = ft_search_env(&buffer[i], data);
			write(heredoc, tmp, ft_strlen(tmp));
		}
		i += ft_name(&buffer[i]);
	}
	return (ret);
}

int	check_heredoc(t_heads **line, t_data *data)
{
	t_token	*tmp_in;

	tmp_in = (*line)->infile;
	while (tmp_in)
	{
		if (tmp_in->token == 8)
			is_heredoc(tmp_in->data, data);
		tmp_in = tmp_in->next;
	}
	return (0);
}
