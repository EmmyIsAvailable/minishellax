/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 12:24:43 by eruellan          #+#    #+#             */
/*   Updated: 2022/05/10 11:44:53 by cdaveux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_display(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(STDOUT_FILENO, str, len);
	return (0);
}

int	variables_in_echo(char *params, t_data *data)
{
	char	**envp;
	int		i;

	i = 0;
	envp = data->envp;
	while (envp[i])
	{
		if (ft_strncmp(&envp[i][ft_strlen(params)], "=", 1) == 0)
		{
			if (ft_strncmp(envp[i], params, ft_strlen(params)) == 0)
			{
				ft_display(&envp[i][ft_strlen(params) + 1]);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	ft_echo(t_token *token, t_data *data)
{
	int		option;
	int		print;
	t_token		*tmp;

	option = 0;
	print = 0;
	tmp = token;
	if (ft_strncmp(tmp->data, "-n", 3) == 0)
	{
		option = 1;
		tmp = tmp->next;
	}
	while (tmp)
	{
		if (tmp->token == ECHO)
			print = ft_display(ft_itoa(data->exit_status));
		else
			print = ft_display(tmp->data);
		if (tmp->next && print == 0)
			ft_display(" ");
		tmp = tmp->next;
	}
	if (option == 0)
		ft_display("\n");
	printf("%s\n", (char *) NULL);
	return (0);
}

int	ft_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		ft_display(data->envp[i]);
		ft_display("\n");
		i++;
	}
	printf("%s\n", (char *) NULL);
	return (0);
}

int	ft_pwd(void)
{
	ft_display(getcwd(NULL, 0));
	ft_display("\n");
	printf("%s\n", (char *) NULL);
	return (0);
}
