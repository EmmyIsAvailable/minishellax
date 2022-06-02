/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaveux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 11:09:13 by cdaveux           #+#    #+#             */
/*   Updated: 2022/06/02 13:51:48 by cdaveux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_lst_last(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lst_add_back(t_token **alst, t_token *new)
{
	if (alst)
	{
		if (*alst != NULL)
			ft_lst_last(*alst)->next = new;
		else
			*alst = new;
	}
}

void	push(t_token **head, t_token **head_b)
{
	t_token	*tmp;
	t_token	*tmpb;

	if (*head == NULL)
		return ;
	tmpb = NULL;
	tmp = (*head)->next;
	if (*head_b == NULL)
	{
		(*head_b) = (*head);
		(*head_b)->next = tmpb;
		(*head) = tmp;
	}
	else
	{
		tmpb = (*head_b);
		(*head)->next = NULL;
		ft_lst_last(tmpb)->next = (*head);
		(*head) = tmp;
	}
}

void	ft_lst_add(t_token **alst, t_token *new)
{
	if (alst)
	{
		if (*alst)
			new -> next = *alst;
		*alst = new;
	}
}

t_token	*fill_data_exit(t_type token, int len, t_data *data)
{
	t_token	*new_token;
	char	*tmp;

	tmp = ft_itoa(data->exit_status);
	new_token = ft_create_token(token);
	new_token->data = ft_strdup(tmp);
	if (!new_token->data)
		return (NULL);
	free(tmp);
	new_token->data_size = len;
	return (new_token);
}
