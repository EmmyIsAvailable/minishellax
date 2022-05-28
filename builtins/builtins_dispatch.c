/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_dispatch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:24:49 by eruellan          #+#    #+#             */
/*   Updated: 2022/05/27 16:20:06 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_pwd(int i, t_data *data)
{
	char	*new;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (i == 1)
		new = ft_strjoin("OLDPWD=", cwd);
	else if (i == 2)
		new = ft_strjoin("PWD=", cwd);
	browse_data_var(new, data);
	free(new);
	free(cwd);
}

int	ft_cd(t_heads **line, t_data *data)
{
	int		ret;

	ret = 0;
	change_pwd(1, data);
	if ((*line)->cmd->next)
		ret = chdir((*line)->cmd->next->data);
	else
		ret = chdir(getenv("HOME"));
	if (ret == -1)
		return (1);
	change_pwd(2, data);
	clear_all_heads(line);
	return (0);
}

int	dispatch_builtins(t_heads **line, t_data *data)
{
	if (ft_strncmp((*line)->cmd->data, "echo", 4) == 0)
	{
		if (!(*line)->cmd->next)
		{
			printf("\n");
			return (0);
		}
		ft_free(&(*line)->cmd);
		return (ft_echo(&(*line)->cmd, data, line));
	}
	if (ft_strncmp((*line)->cmd->data, "pwd", 3) == 0 && !(*line)->cmd->next)
		return (ft_pwd(line));
	if (ft_strncmp((*line)->cmd->data, "env", 3) == 0 && !(*line)->cmd->next)
		return (ft_env(data, line));
	if (ft_strncmp((*line)->cmd->data, "export", 6) == 0 && !(*line)->cmd->next)
		return (ft_solo_export(data));
	return (1);
}

int	non_printable_builtins(t_heads **line, t_data *data)
{
	int	ret;

	ret = 1;
	if (ft_strncmp((*line)->cmd->data, "cd", 2) == 0)
		return (ft_cd(&(*line), data));
	if (ft_strncmp((*line)->cmd->data, "export", 6) == 0 && (*line)->cmd->next)
	{
		ft_free(&(*line)->cmd);
		ret = ft_export((*line)->cmd, data);
	}
	if (ft_strncmp((*line)->cmd->data, "unset", 5) == 0 && (*line)->cmd->next)
		ret = ft_unset((*line)->cmd, data);
	clear_all_heads(line);
	return (ret);
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
