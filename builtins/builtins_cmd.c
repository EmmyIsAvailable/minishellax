/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 12:24:43 by eruellan          #+#    #+#             */
/*   Updated: 2022/06/02 09:48:49 by cdaveux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_data *data, t_heads **line)
{
	int		i;
	char	*env;

	i = 0;
	env = NULL;
	while (data->envp[i])
	{
		env = join_elems(env, data->envp[i]);
		env = join_elems(env, "\n");
		i++;
	}
	write_outfile(line, env);
	free(env);
	return (0);
}

int	ft_pwd(t_heads **line)
{
	char	*pwd;
	char	*cwd;

	pwd = NULL;
	cwd = getcwd(NULL, 0);
	pwd = ft_strjoin(cwd, "\n");
	free(cwd);
	write_outfile(line, pwd);
	free(pwd);
	return (0);
}

int	write_outfile(t_heads **line, char *str)
{
	t_token	*tmp_out;
	int		fd;
	t_token	*tmp;

	fd = 0;
	tmp_out = (*line)->outfile;
	if (!tmp_out && !(*line)->next)
	{
		printf("%s", str);
		return (-1);
	}
	if (!tmp_out && (*line)->next)
	{
		fd = open("tmp", O_CREAT | O_WRONLY, 0664);
		write(fd, str, ft_strlen(str));
		tmp = ft_create_token(WORD);
		tmp->fd = fd;
		tmp->data = ft_strdup("tmp");
		push(&tmp, &(*line)->next->infile);
		return (fd);
	}
	return (write_outfile_bis(tmp_out, str));
}

int	write_outfile_bis(t_token *tmp_out, char *str)
{
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
			write(tmp_out->fd, str, ft_strlen(str));
			close(tmp_out->fd);
		}
		if (tmp_out->next)
			tmp_out = tmp_out->next;
		else
			break ;
	}
	return (tmp_out->fd);
}
