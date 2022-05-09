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

int	ft_cd(t_heads **line, t_data *data)
{
	char	*new_path;
	char	*old_path;
	int		ret;

	new_path = NULL;
	old_path = NULL;
	ret = 0;
	old_path = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
	browse_data_var(old_path, data);
	if ((*line)->cmd->next)
		ret = chdir((*line)->cmd->next->data);
	else
		ret = chdir(getenv("HOME"));
	if (ret == -1)
		return (1);
	new_path = ft_strjoin("PWD=", getcwd(NULL, 0));
	browse_data_var(new_path, data);
//	clear_all_heads(line);
	return (0);
}

int	dispatch_builtins(t_heads **line, t_data *data)
{
	if (ft_strncmp((*line)->cmd->data, "echo", 5) == 0)
	{
		if (!(*line)->cmd->next)
		{
			ft_display("\n");
			printf("%s\n", (char *) NULL);
		}
		ft_free(&(*line)->cmd);
		return (ft_echo((*line)->cmd, data));//envoyer line tt court a terme
	}
	if (ft_strncmp((*line)->cmd->data, "pwd", 4) == 0 && !(*line)->cmd->next)
	{
//		clear_all_heads(line);
		return (ft_pwd());
	}
	if (ft_strncmp((*line)->cmd->data, "env", 4) == 0 && !(*line)->cmd->next)
	{
//		clear_all_heads(line);
		return (ft_env(data));
	}
	if (ft_strncmp((*line)->cmd->data, "export", 7) == 0 && !(*line)->cmd->next)
	{
//		clear_all_heads(line);
		return (ft_solo_export(data));
	}
	return (1);
}

/*int	dispatch_builtins(t_token *token, t_data *data) // a changer
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
}*/

int	non_printable_builtins(t_heads **line, t_data *data)
{
	if (ft_strncmp((*line)->cmd->data, "cd", 3) == 0)
		return (ft_cd(&(*line), data));
	if (ft_strncmp((*line)->cmd->data, "export", 7) == 0 && (*line)->cmd->next)
	{
		ft_free(&(*line)->cmd);
		return (ft_export((*line)->cmd, data)); // a terme envoyer line
	}
	if (ft_strncmp((*line)->cmd->data, "unset", 6) == 0 && (*line)->cmd->next)
		return (ft_unset((*line)->cmd, data)); // a terme envoyer line
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
