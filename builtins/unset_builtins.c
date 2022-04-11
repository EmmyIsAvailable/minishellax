/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:31:22 by eruellan          #+#    #+#             */
/*   Updated: 2022/04/07 16:00:27 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_existence(char *str, char *env)
{
	int	i;

	i = 0;
	while (str[i] == env[i])
		i++;
	if (env[i] == '=')
		return (1);
	return (0);
}

int	check_unset(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[0]) == 0 && str[0] != '_')
		return (1);
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int     ft_unset(t_token *token, t_data *data)
{
	int	i;
	char	**envp;

	envp = data->envp;
        while (token)
        {
                i = -1;
		if (check_unset(token->data) == 0)
		{
                	while (envp[++i])
			{
				if (check_existence(token->data, envp[i]) == 1)
				{
					while (envp[i++])
					{
						free(envp[i]);
						if (envp[i + 1])
							envp[i] = ft_strdup(envp[i + 1]);
						else
							envp[i] = NULL;
					}
				}
			}
		}
		else
			printf("unset: %s invalid parameter name\n", token->data);
		token = token->next;
	}
	return (0);
}

