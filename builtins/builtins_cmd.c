/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 12:24:43 by eruellan          #+#    #+#             */
/*   Updated: 2022/04/14 16:23:41 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	displayOnTerm(char *str)
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
	int	i;

	i = 0;
	envp = data->envp;
	while (envp[i])
	{
		if (ft_strncmp(&envp[i][ft_strlen(params)], "=", 1) == 0)
		{
			if (ft_strncmp(envp[i], params, ft_strlen(params)) == 0)
			{
				displayOnTerm(&envp[i][ft_strlen(params) + 1]);
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
	char	*param;

	option = 0;
	print = 0;
	if (ft_strncmp(token->data, "-n", 3) == 0)
	{
		option = 1;
		token = token->next;
	}
	while (token)
	{
		if (ft_strncmp(token->data, "$?", 2) == 0)
			displayOnTerm(ft_itoa(data->exit_status));
		else
			param = token->data;
		print = displayOnTerm(param);
		if (token->next && print == 0)
			displayOnTerm(" ");
		token = token->next;
	}
	if (option == 0)
		displayOnTerm("\n");
	printf("%s\n", (char *)NULL);
	return (0);
}

int	ft_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		displayOnTerm(data->envp[i]);
		displayOnTerm("\n");
		i++;
	}
	printf("%s\n", (char *)NULL);
	return (0);
}

int	ft_pwd(void)
{
	displayOnTerm(getcwd(NULL, 0));
	displayOnTerm("\n");
	printf("%s\n", (char *)NULL);
	return (0);
}
