/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:31:22 by eruellan          #+#    #+#             */
/*   Updated: 2022/06/02 16:17:10 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_existence(char *str, char *env)
{
	int	i;

	i = 0;
	if (ft_strncmp(str, env, ft_strlen(str)) == 0)
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

char	**ft_exec_unset(t_token *token, char **envp)
{
	char	**new;
	int		len;
	int		i;
	int		j;

	len = 0;
	i = -1;
	j = 0;
	while (envp[len])
		len++;
	new = malloc(sizeof(char *) * (len + 1));
	if (!new)
		return (NULL);
	while (envp[++i])
	{
		if (!check_existence(token->data, envp[i]))
		{
			new[j] = ft_strdup(envp[i]);
			j++;
		}
	}
	new[j] = NULL;
	free_tab(envp);
	return (new);
}

int	ft_unset(t_token *token, t_data *data)
{
	int		ret;
	t_token	*tmp;

	ret = 0;
	tmp = token;
	while (tmp)
	{
		if (check_unset(tmp->data) == 0)
			data->envp = ft_exec_unset(tmp, data->envp);
		else
			ret = 1;
		tmp = tmp->next;
	}
	return (ret);
}
