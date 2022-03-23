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
		(*head_b) = (*head);
		(*head_b)->next = tmpb;
		(*head) = tmp;
	}
}

int	check_word(t_token *tmp, t_heads *list);
int	check_heredoc(t_token *tmp, t_heads *list);
int	check_append(t_token *tmp, t_heads *list);
int	check_infile(t_token *tmp, t_heads *list);
int	check_outfile(t_token *tmp, t_heads *list);

int	check_word(t_token *tmp, t_heads *list)
{
	if (!tmp || tmp->token == 0)
		return (0);
	if (tmp->token == 9)
	{
		//push to cmd
		push(&tmp, &list->cmd); 
		return (check_word(tmp->next, list));
	}
	if (tmp->token == 4)
		return (check_infile(tmp->next, list));
	if (tmp->token == 5)
		return (check_outfile(tmp->next, list));
	if (tmp->token == 7)
		return (check_append(tmp->next, list));
	if (tmp->token == 8)
		return (check_heredoc(tmp->next, list));
	return (1);
}

int	check_dollar(t_token *tmp, t_heads *list) // abandon aussi car opt de export et echo 
{
	if (!tmp)
		return (0);
	if (tmp->token != 9)
		return (1);
	else
		return(check_word(tmp->next, list));
}

int	check_assign(t_token *tmp, t_heads *list) //abandon
{
	if (!tmp)
		return (0);
	if (tmp->token != 9)
		return (1);
	else
		return(check_word(tmp->next, list));
}

int	check_heredoc(t_token *tmp, t_heads *list) // voir comment gerer heredoc
{
	(void)list;
	if (tmp->token == 9)
		return(check_word(tmp->next, list));
/*	if (tmp->token == 6)
		return(check_assign(tmp->next);
	if (tmp->token == 1)
		return(check_dollar(tmp->next);*/ //si on abandonne les $ et =
	return (1);
}

int	check_append(t_token *tmp, t_heads *list)
{
	if (!tmp)
		return (0);
	if (tmp->token != 9)
		return (1);
	else
	{
		//push token to outfile - opt append
		return(check_word(tmp->next, list));
	}
}

int	check_infile(t_token *tmp, t_heads *list)
{
	if (!tmp)
		return (0);
	if (tmp->token != 9)
		return (1);
	else
	{
		//push token to infile list
		return(check_word(tmp->next, list));
	}
}

int	check_outfile(t_token *tmp, t_heads *list)
{
	if (!tmp)
		return (0);
	if (tmp->token != 9)
		return (1);
	else
	{
		//push token to outfile list
		return(check_word(tmp->next, list));
	}
}

int	check_token(t_token **head)
{
	//t_token	*tmp;
	t_heads	list;

//	tmp = *head;
	if ((*head)->token == 4)
		return (check_infile((*head)->next, &list));
	if ((*head)->token == 5)
		return (check_outfile((*head)->next, &list));
	if ((*head)->token == 6)
		return (check_assign((*head)->next, &list));
	if ((*head)->token == 7)
		return (check_append((*head)->next, &list));
	if ((*head)->token == 8)
		return (check_heredoc((*head)->next, &list));
	if ((*head)->token == 9)
		return (check_word((*head)->next, &list));
	printf("cmd : \n");
	ft_print(list.cmd);
	return (1);
}
