/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:20:14 by eruellan          #+#    #+#             */
/*   Updated: 2022/04/14 10:46:46 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	**ft_free_tab(char **data)
{
	int	i;

	i = -1;
	while (data[++i])
	{
		free(data[i]);
		data[i] = NULL;
	}
	return (NULL);
}

int	ft_error(char *str)
{
	perror(str);
	return (EXIT_FAILURE);
}
char    *get_binary(char *cmd, char **env_path)
{
        char    *tmp;
        char    *cmd_path;
        int             i;

        i = -1;
        tmp = NULL;
        cmd_path = NULL;
        while (env_path[++i])
        {
                tmp = ft_strjoin(env_path[i], "/");
                if (!tmp)
                        ft_error("Join failed");
                cmd_path = ft_strjoin(tmp, cmd);
                if (!cmd_path)
                        ft_error("Cmd_path join failed");
                free(tmp);
                if (access(cmd_path, F_OK) == 0)
                        return (cmd_path);
                free(cmd_path);
        }
        return (NULL);
}

char	**fill_token_tab(t_token *token)
{
	char	**tab;
	int	i;
	t_token	*tmp;

	tmp = token;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	tab = (char **)malloc(sizeof(char *) * (i + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (token)
	{
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
        char    **env_path;
        char    *binary;
        char    **cmd;

        cmd = fill_token_tab(token);
        if (!cmd)
                ft_error("Split failed");
	env_path = ft_split(getenv("PATH"), ':');
        binary = get_binary(cmd[0], env_path);
	ft_free_tab(env_path);
        if (execve(binary, cmd, data->envp) == -1)
        {
                free (binary);
                ft_free_tab(cmd);
        }
	return (0);
}
