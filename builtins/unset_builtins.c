/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:31:22 by eruellan          #+#    #+#             */
/*   Updated: 2022/05/05 11:27:22 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_existence(char *str, char *env)
{
	int	i;

	i = 0;
	if (ft_strncmp(str, env, ft_strlen(str)) == 0) //pr unset qq chose qui ne ocntient pas de = 
		return (1);
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

void	ft_exec_unset(t_token *token, char **envp, int i)
{
	while (envp[++i])
	{
		if (check_existence(token->data, envp[i]) == 1)
		{
			while (envp[i] && envp[i + 1])
			{
				envp[i] = ft_strdup(envp[i + 1]);
				i++;
			}
			free(envp[i]);
			envp[i] = NULL;
		}
	}
}

int	ft_unset(t_token *token, t_data *data)
{
	int		i;
	char	**envp;
	int		ret;
	t_token	*tmp;

	envp = data->envp;
	ret = 0;
	tmp = token;
	while (tmp)
	{
		i = -1;
		if (check_unset(tmp->data) == 0)
			ft_exec_unset(tmp, envp, i);
		else
			ret = 1;
		tmp = tmp->next;
	}
	return (ret);
}
