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

int	check_word(t_token **tmp, t_token **infile, t_token **outfile, t_token **cmd);
int	check_infile(t_token **tmp, t_token **infile, t_token **outfile, t_token **cmd);
int	check_outfile(t_token **tmp, t_token **infile, t_token **outfile, t_token **cmd);
//int	check_heredoc(t_token *tmp, t_heads *list);

/*int	check_dollar(t_token *tmp, t_heads *list) // abandon aussi car opt de export et echo 
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
	if (tmp->token == 6)
		return(check_assign(tmp->next);
	if (tmp->token == 1)
		return(check_dollar(tmp->next); //commenter si on abandonne les $ et =
	return (1);
}*/

int	check_word(t_token **tmp, t_token **infile, t_token **outfile, t_token **cmd)
{
	if ((*tmp) == NULL || (*tmp)->token == 0)
		return (0);
	if ((*tmp)->token == 9)
	{
		//push to cmd
		printf("push to cmd\n");
		push(tmp, cmd);
		ft_print(*cmd);
		return (check_word(tmp, infile, outfile, cmd));
	}
	if ((*tmp)->token == 4)
		return (check_infile(tmp, infile, outfile, cmd));
	if ((*tmp)->token == 5 || (*tmp)->token == 7)
		return (check_outfile(tmp, infile, outfile, cmd));
//	if (tmp->token == 8)
//		return (check_heredoc(tmp->next, list));
	return (1);
}

int	check_infile(t_token **tmp, t_token **infile, t_token **outfile, t_token **cmd)
{
	if ((*tmp) == NULL || (*tmp)->next->token == 0)
		return (0);
	if ((*tmp)->next->token != 9)
		return (1);
	else
	{
		//push token to infile list
		printf("push to infile\n");
		push(&(*tmp)->next, infile);
		ft_print(*infile);
		return(check_word(&(*tmp)->next, infile, outfile, cmd));
	}
}

int	check_outfile(t_token **tmp, t_token **infile, t_token **outfile, t_token **cmd)
{
	if ((*tmp) == NULL || (*tmp)->next->token == 0)
		return (0);
	if ((*tmp)->next->token != 9)
		return (1);
	else
	{
		//push token to outfile list
		printf("push to outfile\n");
		push(&(*tmp)->next, outfile);
		ft_print(*outfile);
		return(check_word(&(*tmp)->next, infile, outfile, cmd));
	}
}

int	check_token(t_token **head, t_token *infile, t_token *outfile, t_token *cmd)
{
	//t_token	*tmp;
//	t_heads	list;

//	tmp = *head;
	if ((*head)->token == 4) // <
		return (check_infile(head, &infile, &outfile, &cmd));
	if ((*head)->token == 5 || (*head)->token == 7) // > & >>
		return (check_outfile(head, &infile, &outfile, &cmd));
	if ((*head)->token == 9) // WORD
		return (check_word(head, &infile, &outfile, &cmd));
//	if ((*head)->token == 6) 
//		return (check_assign((*head)->next, &list));
//	if ((*head)->token == 8)
//		return (check_heredoc((*head)->next, &list));
	return (1);
}
