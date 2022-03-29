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
	else //on veut push in the back : essai ne marche pas 
	{
		/*tmpb = (*head_b);
		while (tmpb->next != NULL)
			tmpb = tmpb->next;
		tmpb->next = (*head);
		(*head) = tmp;*/
		tmpb = (*head_b);
		(*head_b) = (*head);
		(*head_b)->next = tmpb;
		(*head) = tmp;
	}
	printf("push done\n");
}

int	check_quote(t_token **tmp, t_token **infile, t_token **outfile, t_token **cmd);
int	check_word(t_token **tmp, t_token **infile, t_token **outfile, t_token **cmd);
int	check_infile(t_token **tmp, t_token **infile, t_token **outfile, t_token **cmd);
int	check_outfile(t_token **tmp, t_token **infile, t_token **outfile, t_token **cmd);
int	check_dollar(t_token **tmp, t_token **infile, t_token **outfile, t_token **cmd);
//int	check_heredoc(t_token *tmp, t_heads *list);

int	check_dollar(t_token **tmp, t_token **infile, t_token **outfile, t_token **cmd)
{
	if ((*tmp) == NULL)
		return (0);
	if ((*tmp)->token == 0)
		return (-1);
	if ((*tmp)->token != 9)
		return (1);
	//push to cmd
	printf("push to cmd\n");
	push(tmp, cmd);
	ft_print(*cmd);
	return (check_word(tmp, infile, outfile, cmd));
}

/*
int	check_heredoc(t_token *tmp, t_heads *list) // voir comment gerer heredoc
{
	(void)list;
	if (tmp->token == 9)
		return(check_word(tmp->next, list));
	if (tmp->token == 6)
		return(check_assign(tmp->next);
	return (1);
}*/

int	check_double_quote(t_token **tmp, t_token **infile, t_token **outfile, t_token **cmd)
{
	if ((*tmp) == NULL)
		return (0);
	if ((*tmp)->token != 2)
	{
		if ((*tmp)->token != 1)
			(*tmp)->token = 9;
		printf("push to cmd\n");
		push(tmp, cmd);
		ft_print(*cmd);
		return (check_double_quote(tmp, infile, outfile, cmd));
	}
	return (check_token(&(*tmp)->next, *infile, *outfile, *cmd));
}

int	check_quote(t_token **tmp, t_token **infile, t_token **outfile, t_token **cmd)
{
	if ((*tmp) == NULL)
		return (0);
	if ((*tmp)->token != 3)
	{
		(*tmp)->token = 9;
		printf("push to cmd\n");
		push(tmp, cmd);
		ft_print(*cmd);
		return (check_quote(tmp, infile, outfile, cmd));
	}
	return (check_token(&(*tmp)->next, *infile, *outfile, *cmd));
}

int	check_word(t_token **tmp, t_token **infile, t_token **outfile, t_token **cmd)
{
	if (!(*tmp))
		return (0);
	if ((*tmp)->token == 0)
		return (-1);
	if ((*tmp)->token == 9 || (*tmp)->token == 1)
	{
		printf("push to cmd\n");
		push(tmp, cmd);
		ft_print(*cmd);
		return (check_word(tmp, infile, outfile, cmd));
	}
	if ((*tmp)->token == 4)
		return (check_infile(tmp, infile, outfile, cmd));
	if ((*tmp)->token == 5 || (*tmp)->token == 7)
		return (check_outfile(tmp, infile, outfile, cmd));
	if ((*tmp)->token == 3)
		return (check_quote(&(*tmp)->next, infile, outfile, cmd));
	if ((*tmp)->token == 2)
		return (check_double_quote(&(*tmp)->next, infile, outfile, cmd));
//	if (tmp->token == 8)
//		return (check_heredoc(tmp->next, list));
	return (1);
}

int	check_infile(t_token **tmp, t_token **infile, t_token **outfile, t_token **cmd)
{
	if (!(*tmp)->next || (*tmp)->next->token != 9)
		return (1);
	else
	{
		printf("push to infile\n");
		push(&(*tmp)->next, infile);
		ft_print(*infile);
		return(check_word(&(*tmp)->next, infile, outfile, cmd));
	}
}

int	check_outfile(t_token **tmp, t_token **infile, t_token **outfile, t_token **cmd)
{
	if (!(*tmp)->next || (*tmp)->next->token != 9)
		return (1);
	else
	{
		printf("push to outfile\n");
		if ((*tmp)->token == 5)
			(*tmp)->next->token = 5;
		else
			(*tmp)->next->token = 7;
		push(&(*tmp)->next, outfile);
		ft_print(*outfile);
		return(check_word(&(*tmp)->next, infile, outfile, cmd));
	}
}

int	check_token(t_token **head, t_token *infile, t_token *outfile, t_token *cmd)
{
	if ((*head) == NULL)
		return (-1);
	if ((*head)->token == 4) // <
		return (check_infile(head, &infile, &outfile, &cmd));
	if ((*head)->token == 5 || (*head)->token == 7) // > & >>
		return (check_outfile(head, &infile, &outfile, &cmd));
	if ((*head)->token == 9) // WORD
		return (check_word(head, &infile, &outfile, &cmd));
//	if ((*head)->token == 8)
//		return (check_heredoc((*head)->next, &list));
	return (1);
}
