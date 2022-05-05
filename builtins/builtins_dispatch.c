/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_dispatch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:24:49 by eruellan          #+#    #+#             */
/*   Updated: 2022/05/05 11:18:18 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(t_token *token, t_data *data)
{
	char	*new_path;
	char	*old_path;
	int		ret;

	new_path = NULL;
	old_path = NULL;
	ret = 0;
	old_path = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
	browse_data_var(old_path, data);
	if (token->next)
		ret = chdir(token->next->data);
	else
		ret = chdir(getenv("HOME"));
	if (ret == -1)
		return (1);
	new_path = ft_strjoin("PWD=", getcwd(NULL, 0));
	browse_data_var(new_path, data);
	return (0);
}

int	dispatch_builtins(t_token *token, t_data *data)
{
	if (ft_strncmp(token->data, "echo", 5) == 0)
	{
		if (!token->next)
		{
			ft_display("\n");
			printf("%s\n", (char *) NULL);
		}
		return (ft_echo(token->next, data));
	}
	if (ft_strncmp(token->data, "pwd", 4) == 0 && !token->next)
		return (ft_pwd());
	if (ft_strncmp(token->data, "env", 4) == 0 && !token->next)
		return (ft_env(data));
	if (ft_strncmp(token->data, "export", 7) == 0 && !token->next)
		return (ft_solo_export(data));
	return (1);
}

int	non_printable_builtins(t_token *token, t_data *data)
{	
	if (ft_strncmp(token->data, "cd", 3) == 0)
		return (ft_cd(token, data));
	if (ft_strncmp(token->data, "export", 7) == 0 && token->next)
		return (ft_export(token->next, data));
	if (ft_strncmp(token->data, "unset", 6) == 0 && token->next)
		return (ft_unset(token->next, data));
	return (1);
}

int	is_non_print_builtins(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (ft_strncmp(token->data, "cd", 3) == 0)
		return (error_cd(token));
	if (ft_strncmp(token->data, "export", 7) == 0 && token->next)
		return (error_export(token->next));
	if (ft_strncmp(token->data, "unset", 6) == 0 && token->next)
	{
		while (tmp)
		{
			if (check_unset(token->next->data) != 0)
				printf("-bash: unset: '%s': not a valid identifier\n",
					token->next->data);
			tmp = tmp->next;
		}
		return (0);
	}
	return (1);
}
