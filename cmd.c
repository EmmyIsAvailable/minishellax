/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:20:14 by eruellan          #+#    #+#             */
/*   Updated: 2022/07/07 12:31:24 by cdaveux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_path_cmd(char *cmd)
{
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

char	*get_binary(char *cmd, char **env_path)
{
	char	*tmp;
	char	*cmd_path;
	int		i;

	i = -1;
	tmp = NULL;
	cmd_path = NULL;
	if (cmd[0] == '/')
		return (check_path_cmd(cmd));
	while (env_path[++i])
	{
		tmp = ft_strjoin(env_path[i], "/");
		if (!tmp)
			return (NULL);
		cmd_path = ft_strjoin(tmp, cmd);
		if (!cmd_path)
			return (NULL);
		free(tmp);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	return (NULL);
}

char	*pass_path(t_token *token)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (token->data[i])
	{
		if (token->data[i] == '/')
			j = i;
		i++;
	}
	if (token->data[j + 1] != '\0')
		return (&token->data[j + 1]);
	return (NULL);
}

char	**fill_token_tab(t_token *token)
{
	char	**tab;
	int		i;

	i = 0;
	tab = (char **)malloc(sizeof(char *) * (count_token(token) + 1));
	if (!tab)
		return (NULL);
	while (token)
	{
		if (i == 0 && token->data[0] == '/')
			tab[i] = ft_strdup(pass_path(token));
		else
			tab[i] = ft_strdup(token->data);
		if (!tab[i])
			return (NULL);
		i++;
		token = token->next;
	}
	tab[i] = NULL;
	return (tab);
}

int	ft_exec(t_token *token, t_data *data)
{
	char	**env_path;
	char	*binary;
	char	**cmd;

	cmd = fill_token_tab(token);
	if (!cmd)
		return (-1);
	env_path = ft_split(getenv("PATH"), ':');
	binary = get_binary(cmd[0], env_path);
	if (!binary)
	{
		write(STDERR_FILENO, "bash: ", 6);
		write(STDERR_FILENO, token->data, ft_strlen(token->data));
		write(STDERR_FILENO, ": command not found\n", 20);
		free(binary);
		free_tab(cmd);
		return (-1);	
	}
	free_tab(env_path);
	if (execve(binary, cmd, data->envp) == -1)
	{
		free(binary);
		free_tab(cmd);
		return (-1);
	}
	return (0);
}
