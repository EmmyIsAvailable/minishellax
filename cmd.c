/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:20:14 by eruellan          #+#    #+#             */
/*   Updated: 2022/03/22 14:57:08 by eruellan         ###   ########.fr       */
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
        ft_error("Command not found");
        return (NULL);
}

char	**fill_token_tab(t_token *token)
{
	char	**tab;
	int	i;

	tab = NULL;
	i = 0;
	while (token)
	{
		tab[i] = token->data;
		token = token->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

void    ft_exec(t_token *token, t_data *data)
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
        if (!binary)
                ft_error("Getting binary file failed");
        if (execve(binary, cmd, data->envp) == -1)
        {
                free (binary);
                ft_free_tab(cmd);
                ft_error("Error");
        }
}
