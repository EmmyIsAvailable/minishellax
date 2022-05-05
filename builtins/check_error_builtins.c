/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_builtins.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:03:19 by eruellan          #+#    #+#             */
/*   Updated: 2022/05/05 15:48:58 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_export(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (check_assign(tmp->data) != 0)
			printf("-bash: export: '%s': not a valid identifier\n", tmp->data);
		tmp = tmp->next;
	}
	return (0);
}

int	error_cd(t_token *token)
{
	struct stat	*buf;

	buf = NULL;
	if (token->next && token->next->next)
		printf("-bash: cd: too many arguments\n");
	else if (token->next && stat(token->next->data, buf) == -1)
		printf("-bash: cd: %s: No such file or directory\n", token->next->data);
	return (0);
}
