/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_dispatch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:24:49 by eruellan          #+#    #+#             */
/*   Updated: 2022/04/14 16:31:29 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(t_token *token, t_data *data)
{
	char	*new_path;
	char	*old_path;
	int	ret;

	new_path = NULL;
	old_path = NULL;
	ret = 0;
	if (token->next && token->next->next)
	{	
		printf("cd: too many arguments\n");
		return (1);
	}
	old_path = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
	browse_data_var(old_path, data);
	if (token->next)
		ret = chdir(token->next->data);
	else
		ret = chdir(getenv("HOME"));
	if (ret == -1)
	{
		printf("cd: %s: No such file or directory\n", token->next->data);
		return (1);
	}
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
			displayOnTerm("\n");
			printf("%s\n", (char *)NULL);
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
	{	
		ft_cd(token, data); //attention return 1 si trop d'args mais return 1 = execve donc ?
		return (0);
	}
	if (ft_strncmp(token->data, "export", 7) == 0 && token->next)
		return (ft_export(token->next, data));
	if (ft_strncmp(token->data, "unset", 6) == 0 && token->next)
		return (ft_unset(token->next, data));
	return (1);
}

int	is_non_print_builtins(t_token *token)
{
	if (ft_strncmp(token->data, "cd", 3) == 0)
		return (0);
	if (ft_strncmp(token->data, "export", 7) == 0 && token->next)
		return (0);
	if (ft_strncmp(token->data, "unset", 6) == 0 && token->next)
		return (0);
	return (1);
}
