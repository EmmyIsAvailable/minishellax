/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaveux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:42:16 by cdaveux           #+#    #+#             */
/*   Updated: 2022/05/30 17:45:52 by cdaveux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_name(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (i);
	}
	return (i);
}

char	*ft_search_env(char *params, t_data *data)
{
	char	**envp;
	int		i;

	i = -1;
	envp = data->envp;
	while (envp[++i])
	{
		if (ft_strncmp(&envp[i][ft_name(params)], "=", 1) == 0)
		{
			if (ft_strncmp(envp[i], params, ft_name(params)) == 0)
				return (&envp[i][ft_name(params) + 1]);
		}
	}
	return (NULL);
}

int	join_data(t_token **tmp)
{
	int		var_env;
	char	*str;

	str = NULL;
	var_env = 9;
	while (((*tmp) && (*tmp)->next)
		&& (((*tmp)->token != SPACE || (*tmp)->token != PIPE)))
	{
		if ((*tmp)->token == DOLLAR_SIGN)
			var_env = 1;
		if ((*tmp)->next->token == SPACE || (*tmp)->next->token == PIPE)
			break ;
		str = ft_strjoin((*tmp)->data, (*tmp)->next->data);
		ft_free(tmp);
		free((*tmp)->data);
		(*tmp)->data = ft_strdup(str);
		(*tmp)->token = var_env;
		free(str);
	}
	return (0);
}

int	ft_heredoc(t_token *tmp)
{
	if (tmp->token != 32)
	{
		if (tmp->token == 8)
			return (1);
		else
			return (0);
	}
	return (0);
}
