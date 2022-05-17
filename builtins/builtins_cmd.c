/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 12:24:43 by eruellan          #+#    #+#             */
/*   Updated: 2022/05/16 13:51:56 by cdaveux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(t_token *token, t_data *data, t_heads **line)
{
	int		option;
	char	*str;

	option = 0;
	str = NULL;
	if (ft_strncmp(token->data, "-n", 3) == 0)
	{
		option = 1;
		token = token->next;
	}
	while (token)
	{
		if (token->token == ECHO)
			str = ft_strjoin(str, ft_itoa(data->exit_status));
		else
			str = ft_strjoin(str, token->data);
		if (token->next)
			str = ft_strjoin(str, " ");
		token = token->next;
	}
	if (option == 0)
		str = ft_strjoin(str, "\n");
	write_outfile(line, str);
	free(str);
	return (0);
}

int	ft_env(t_data *data, t_heads **line)
{
	int		i;
	char	*env;

	i = 0;
	env = NULL;
	while (data->envp[i])
	{
		env = ft_strjoin(env, data->envp[i]);
		env = ft_strjoin(env, "\n");
		i++;
	}
	write_outfile(line, env);
	free(env);
	return (0);
}

int	ft_pwd(t_heads **line)
{
	char	*pwd;

	pwd = NULL;
	pwd = ft_strjoin(getcwd(NULL, 0), "\n");
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
		fd = open("tmp", O_CREAT | O_WRONLY , 0664);
		write(fd, str, ft_strlen(str));
		tmp = ft_create_token(WORD);
		tmp->fd = fd;
		tmp->data = ft_strdup("tmp");
		push(&tmp, &(*line)->next->infile);
		ft_print_line(line);
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
