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

int	check_dollar(t_token **tmp, t_token **infile, t_token **outfile, t_token **cmd)
{
	if ((*tmp) == NULL)
		return (0);
	if ((*tmp)->token == 0)
		return (-1);
	if ((*tmp)->token != 9)
		return (1);
	push(tmp, cmd);
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
		push(tmp, cmd);
		return (check_double_quote(tmp, infile, outfile, cmd));
	}
	return (check_token(&(*tmp)->next, infile, outfile, cmd));
}

int	check_quote(t_token **tmp, t_token **infile, t_token **outfile, t_token **cmd)
{
	if ((*tmp) == NULL)
		return (0);
	if ((*tmp)->token != 3)
	{
		(*tmp)->token = 9;
		push(tmp, cmd);
		return (check_quote(tmp, infile, outfile, cmd));
	}
	return (check_token(&(*tmp)->next, infile, outfile, cmd));
}

int	check_word(t_token **tmp, t_token **infile, t_token **outfile, t_token **cmd)
{
	if (!(*tmp))
		return (0);
	if ((*tmp)->token == 0)
		return (-1);
	if ((*tmp)->token == 9 || (*tmp)->token == 1)
	{
		push(tmp, cmd);
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
		push(&(*tmp)->next, infile);
		return(check_word(&(*tmp)->next, infile, outfile, cmd));
	}
}

int	check_outfile(t_token **tmp, t_token **infile, t_token **outfile, t_token **cmd)
{
	if (!(*tmp)->next || (*tmp)->next->token != 9)
		return (1);
	else
	{
		if ((*tmp)->token == 5)
			(*tmp)->next->token = 5;
		else
			(*tmp)->next->token = 7;
		push(&(*tmp)->next, outfile);
		return(check_word(&(*tmp)->next, infile, outfile, cmd));
	}
}

int	check_token(t_token **head, t_token **infile, t_token **outfile, t_token **cmd)
{
	if ((*head) == NULL)
		return (-1);
	if ((*head)->token == 4) // <
		return (check_infile(head, infile, outfile, cmd));
	if ((*head)->token == 5 || (*head)->token == 7) // > & >>
		return (check_outfile(head, infile, outfile, cmd));
	if ((*head)->token == 9) // WORD
		return (check_word(head, infile, outfile, cmd));
//	if ((*head)->token == 8)
//		return (check_heredoc((*head)->next, &list));
	return (1);
}
