/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_builtins.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:03:19 by eruellan          #+#    #+#             */
/*   Updated: 2022/06/09 15:47:07 by cdaveux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_export(t_token *token)
{
	t_token	*tmp;
	int		err;

	tmp = token;
	err = 0;
	while (tmp)
	{
		if (check_assign(tmp->data) != 0)
		{
			err = 1;
			write(STDERR_FILENO, "bash: export: not a valid identifier\n", 37);
		}
		tmp = tmp->next;
	}
	if (err)
		return (1);
	return (0);
}

int	error_cd(t_token *token)
{
	struct stat	buf;

	if (token->next && token->next->next)
	{
		write(STDERR_FILENO, "bash: cd: too many arguments\n", 29); //pas sure tests a faire
		return (1);
	}
	else if (token->next && stat(token->next->data, &buf) == -1
		&& ft_strncmp(token->next->data, "-", 1) != 0)
	{
		write(STDERR_FILENO, "bash: cd: no such file or directory\n", 36);
		return (1);
	}
	return (0);
}

int	check_error_builtins(t_token *token)
{
	t_token	*tmp;
	int		err;

	tmp = token;
	err = 0;
	if (tmp)
	{
		if (ft_strncmp_len(token->data, "cd", 2) == 0)
			return (error_cd(token));
		if (ft_strncmp_len(token->data, "export", 6) == 0 && token->next)
			return (error_export(token->next));
		if (ft_strncmp_len(token->data, "unset", 5) == 0 && token->next)
		{
			tmp = tmp->next;
			while (tmp)
			{
				if (check_unset(token->next->data) != 0)
				{
					err = 1;
					write(STDERR_FILENO, "bash: unset: not a valid identifier\n", 36);
				}
				tmp = tmp->next;
			}
			if (err)
				return (1);
		}
	}
	return (0);
}
