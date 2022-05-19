/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaveux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:48:32 by cdaveux           #+#    #+#             */
/*   Updated: 2022/05/19 15:07:48 by cdaveux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lst_delone(t_token *lst, void (*del)(void *))
{
	if (!del || !lst)
		return ;
	if (lst)
	{
		(*del)(lst->data);
		free(lst);
	}
}

void	ft_lst_clear(t_token **lst, void (*del)(void *))
{
	t_token	*temp;

	if (!del || !lst || !*lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_lst_delone(*lst, del);
		(*lst) = temp;
	}
}

void	ft_free(t_token **head)
{
	t_token	*tmp;

	tmp = (*head);
	(*head) = (*head)->next;
	free(tmp->data);
	free(tmp);
}

int	clear_head(t_token **head)
{
	while ((*head) && (*head)->token != 0)
		ft_free(head);
	ft_free(head);
	if ((*head) && (*head)->token == 0)
		ft_free(head);
	return (1);
}
