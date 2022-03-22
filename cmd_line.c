/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaveux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:23:36 by cdaveux           #+#    #+#             */
/*   Updated: 2022/03/22 16:31:08 by cdaveux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	push(t_list **head, t_list **head_b)
{
	t_list	*tmp;
	t_list	*tmpb;

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
		(*head_b) = (*head);
		(*head_b)->next = tmpb;
		(*head) = tmp;
	}
}

int	check_word(t_token *tmp)
{
	if (!tmp)
		return (0);
	if (tmp->next->token == 9)
		return (check_word(tmp->next->next));
	if (tmp->next->token == 4)
		return ( //a finir
}

int	check_dollar(t_token *tmp)
{
	if (!tmp)
		return (0);
	if (tmp->token != 9)
		return (1);
	else
		return(check_word(tmp->next);
}

int	check_assign(t_token *tmp)
{
	if (!tmp)
		return (0);
	if (tmp->token != 9)
		return (1);
	else
		return(check_word(tmp->next);
}

// ok a partir de la 
int	check_heredoc(t_token *tmp)
{
	if (!tmp)
		return (0);
	if (tmp->token == 9)
		return(check_word(tmp->next);
	if (tmp->token == 6)
		return(check_assign(tmp->next);
	if (tmp->token == 1)
		return(check_dollar(tmp->next);
	return (1);
}

int	check_append(t_token *tmp)
{
	if (!tmp)
		return (0);
	if (tmp->token != 9)
		return (1);
	else
		return(check_word(tmp->next);
}

int	check_infile(t_token *tmp)
{
	if (!tmp)
		return (0);
	if (tmp->token != 9)
		return (1);
	else
		return(check_word(tmp->next);
}

int	check_outfile(t_token *tmp)
{
	if (!tmp)
		return (0);
	if (tmp->token != 9)
		return (1);
	else
		return(check_word(tmp->next);
}

void	check_token(t_token **head)
{
	t_token	*tmp;

	tmp = *head;
	if (tmp->token == 4)
		return (check_infile(tmp->next));
	if (tmp->token == 5)
		return (check_outfile(tmp->next));
	if (tmp->token == 6)
		return (check_assign(tmp->next));
	if (tmp->token == 7)
		return (check_append(tmp->next));
	if (tmp->token == 8)
		return (check_heredoc(tmp->next));
	if (tmp->token == 9)
		return (check_word(tmp->next));
	return (1);
}
