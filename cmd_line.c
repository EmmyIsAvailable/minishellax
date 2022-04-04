/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaveux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:23:36 by cdaveux           #+#    #+#             */
/*   Updated: 2022/03/31 13:54:43 by cdaveux          ###   ########.fr       */
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


int	check_heredoc(t_token **tmp, t_token **infile, t_token **outfile, t_token **cmd)
{
	t_token *temp;

	temp = NULL;
	if (!(*tmp)->next || (*tmp)->next->token != 9)
		return (1);
	else
	{
		temp = (*tmp);
		(*tmp) = (*tmp)->next;
		free(temp);
		(*tmp)->token = 8;
		push(&(*tmp), cmd);
		if (!(*tmp))
			return (0);		
		if ((*tmp)->token == 0)
			return (-1);
		return(check_word(&(*tmp), infile, outfile, cmd));
	}
}

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
	if (!(*tmp)->next)
		return (0);
	if ((*tmp)->next->token == 0)
		return (-1);
	return (check_word(&(*tmp)->next, infile, outfile, cmd));
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
	if (!(*tmp)->next)
		return (0);
	if ((*tmp)->next->token == 0)
		return (-1);
	return (check_word(&(*tmp)->next, infile, outfile, cmd));
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
	if ((*tmp)->token == 8)
		return (check_heredoc(&(*tmp)->next, infile, outfile, cmd));
	return (1);
}

int	check_infile(t_token **tmp, t_token **infile, t_token **outfile, t_token **cmd)
{
	t_token *temp;

	temp = NULL;
	if (!(*tmp)->next || (*tmp)->next->token != 9)
		return (1);
	else
	{
		temp = (*tmp);
		(*tmp) = (*tmp)->next;
		free(temp);
		(*tmp)->token = 4;
		push(&(*tmp), infile);
		if (!(*tmp))
			return (0);		
		if ((*tmp)->token == 0)
			return (-1);
		return(check_word(&(*tmp), infile, outfile, cmd));
	}
}

int	check_outfile(t_token **tmp, t_token **infile, t_token **outfile, t_token **cmd)
{
	t_token *temp;

	temp = NULL;
	if (!(*tmp)->next || (*tmp)->next->token != 9)
		return (1);
	else
	{
		if ((*tmp)->token == 5)
		{
			temp = (*tmp);
			(*tmp) = (*tmp)->next;
			free(temp);
			(*tmp)->token = 5;
		}
		else
		{
			temp = (*tmp);
			(*tmp) = (*tmp)->next;
			free(temp);
			(*tmp)->token = 7;
		}
		push(&(*tmp), outfile);
		if (!(*tmp))
			return (0);
		if ((*tmp)->token == 0)
			return (-1);
		return(check_word(&(*tmp), infile, outfile, cmd));
	}
}

int	check_token(t_token **head, t_token **infile, t_token **outfile, t_token **cmd)
{
	if ((*head) == NULL)
		return (0);
	if ((*head)->token == 4)
		return (check_infile(head, infile, outfile, cmd));
	if ((*head)->token == 5 || (*head)->token == 7)
		return (check_outfile(head, infile, outfile, cmd));
	if ((*head)->token == 9)
		return (check_word(head, infile, outfile, cmd));
	if ((*head)->token == 8)
		return (check_heredoc(head, infile, outfile, cmd));
	return (1);
}
