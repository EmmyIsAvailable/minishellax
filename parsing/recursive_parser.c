/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaveux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:23:36 by cdaveux           #+#    #+#             */
/*   Updated: 2022/04/22 11:08:08 by cdaveux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_here(t_token **tmp, t_token **inf, t_token **out, t_token **cmd)
{
	if (!(*tmp)->next)
		return (1);
	if ((*tmp)->token == SPACE)
		(*tmp) = (*tmp)->next;
	if ((*tmp)->next)
	{
		(*tmp) = (*tmp)->next;
		if ((*tmp)->token == SPACE)
			(*tmp) = (*tmp)->next;
		if ((*tmp)->token == 9 || (*tmp)->token == 1 || (*tmp)->token == 2
			|| (*tmp)->token == 3 || (*tmp)->token == 6)
		{
			join_data(tmp);
			(*tmp)->token = 8;
			push(tmp, inf);
		}
	}
	else
		return (1);
	if (!(*tmp))
		return (0);
	if ((*tmp)->token == 0)
		return (-1);
	return (check_word(tmp, inf, out, cmd));
}

int	check_word(t_token **tmp, t_token **inf, t_token **out, t_token **cmd)
{
	if (!(*tmp))
		return (0);
	if ((*tmp)->token == SPACE)
		(*tmp) = (*tmp)->next;
	if ((*tmp)->token == PIPE && (*tmp)->next != NULL)
		return (-1);
	if ((*tmp)->token == ECHO) //temporaire
	{
		push(tmp, cmd);
		return (0);
	}
	if ((*tmp)->token == 9 || (*tmp)->token == 1 || (*tmp)->token == 2
		|| (*tmp)->token == 3 || (*tmp)->token == 6)
	{
		join_data(tmp);
		push(tmp, cmd);
		return (check_word(tmp, inf, out, cmd));
	}
	if ((*tmp)->token == 5 || (*tmp)->token == 7
		|| (*tmp)->token == 4 || (*tmp)->token == 8)
		return (check_token(tmp, inf, out, cmd));
	return (1);
}

int	check_infile(t_token **tmp, t_token **inf, t_token **out, t_token **cmd)
{
	if (!(*tmp)->next)
		return (1);
	if ((*tmp)->next->token == SPACE)
		(*tmp) = (*tmp)->next;
	if (!(*tmp)->next || (*tmp)->next->token != 9)
		return (1);
	else
	{
		(*tmp) = (*tmp)->next;
		(*tmp)->token = 4;
		push(&(*tmp), inf);
		if (!(*tmp))
			return (0);
		if ((*tmp)->token == 0)
			return (-1);
		return (check_word(&(*tmp), inf, out, cmd));
	}
}

int	check_outfile(t_token **tmp, t_token **inf, t_token **out, t_token **cmd)
{
	if (!(*tmp)->next)
		return (1);
	if ((*tmp)->token == SPACE)
		(*tmp) = (*tmp)->next;
	if ((*tmp)->next->token == 9 || ((*tmp)->next->token == 10
			&& (*tmp)->next->next->token == 9))
	{
		(*tmp) = (*tmp)->next;
		if ((*tmp)->token == SPACE)
			(*tmp) = (*tmp)->next;
		if ((*tmp)->token == 9)
			(*tmp)->token = 5;
		push(&(*tmp), out);
	}
	else
		return (1);
	if (!(*tmp))
		return (0);
	if ((*tmp)->token == 0)
		return (-1);
	return (check_word(&(*tmp), inf, out, cmd));
}

int	check_append(t_token **tmp, t_token **inf, t_token **out, t_token **cmd)
{
	if (!(*tmp)->next)
		return (1);
	if ((*tmp)->token == SPACE)
		(*tmp) = (*tmp)->next;
	if ((*tmp)->next->token == 9 || ((*tmp)->next->token == 10
			&& (*tmp)->next->next->token == 9))
	{
		(*tmp) = (*tmp)->next;
		if ((*tmp)->token == SPACE)
			(*tmp) = (*tmp)->next;
		if ((*tmp)->token == 9)
			(*tmp)->token = 7;
		push(&(*tmp), out);
	}
	else
		return (1);
	if (!(*tmp))
		return (0);
	if ((*tmp)->token == 0)
		return (-1);
	return (check_word(&(*tmp), inf, out, cmd));
}
