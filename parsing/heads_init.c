/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heads_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaveux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:43:29 by cdaveux           #+#    #+#             */
/*   Updated: 2022/05/06 16:46:13 by cdaveux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_elem_heads(t_heads **lst)
{
	if (!(*lst))
		return ;
	if ((*lst))
	{
		if ((*lst)->cmd)
			ft_lst_clear(&(*lst)->cmd, free);
		if ((*lst)->infile)
			ft_lst_clear(&(*lst)->infile, free);
		if ((*lst)->outfile)
			ft_lst_clear(&(*lst)->outfile, free);
		free(*lst);
	}
}

void	clear_all_heads(t_heads **lst)
{
	t_heads	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		free_elem_heads(lst);
		*lst = tmp;
	}
}

t_heads	*ft_last(t_heads *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	push_heads(t_heads **head, t_heads **head_b)
{
	t_heads	*tmp;
	t_heads	*tmpb;

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
		ft_last(tmpb)->next = (*head);
		(*head) = tmp;
	}
}

t_heads	*tmp_init(void)
{
	t_heads	*tmp;

	tmp = malloc(sizeof(t_heads));
	if (!tmp)
		return (NULL);
	tmp->infile = NULL;
	tmp->outfile = NULL;
	tmp->cmd = NULL;
	return (tmp);
}
