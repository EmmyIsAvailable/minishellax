/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_dispatch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:24:49 by eruellan          #+#    #+#             */
/*   Updated: 2022/04/07 13:27:38 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(t_token *token, t_data *data)
{
	getcwd(data->oldpwd, 0);
	if (chdir(token->data) == -1)
		return (1);
	getcwd(data->pwd, 0);
	return (0);
}

int	dispatch_builtins(t_token *token, t_data *data)
{
	if (ft_strncmp(token->data, "echo", 5) == 0)
	{
		if (!token->next)
		{
			displayOnTerm("\n");
			printf("%s\n", (char *)NULL);
		}
		return (ft_echo(token->next, data));
	}
	if (ft_strncmp(token->data, "pwd", 4) == 0 && !token->next)
		return (ft_pwd());
	if (ft_strncmp(token->data, "env", 4) == 0 && !token->next)
		return (ft_env(data));
	if (ft_strncmp(token->data, "cd", 3) == 0 && !token->next->next)
	{
		ft_cd(token->next, data);
		return (0);
	}
	if (ft_strncmp(token->data, "exit", 6) == 0 && !token->next)
	{
		//free les futurs trucs a free
		return (-1);
	}
	if (ft_strncmp(token->data, "export", 7) == 0 && token->next)
		return (ft_export(token->next, data));
	if (ft_strncmp(token->data, "export", 7) == 0 && !token->next)
		return (ft_solo_export(data));
	if (ft_strncmp(token->data, "unset", 6) == 0 && token->next)
		return (ft_unset(token->next, data));
	return (1);
}
