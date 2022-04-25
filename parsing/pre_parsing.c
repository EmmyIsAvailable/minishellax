/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaveux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 11:08:19 by cdaveux           #+#    #+#             */
/*   Updated: 2022/04/22 13:48:57 by cdaveux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_heredoc(t_token *tmp)
{
	if (tmp->token != 32)
	{
		if (tmp->token == 8)
			return (1);
		else
			return (0);
	}
	return (0);
}

int	jump_spaces(char *str, int i)
{
	while (str[i] && (str[i] == '\t' || str[i] == '\v' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\f' || str[i] == 32))
		i++;
	return (i);
}

void	create_tokens(char *str, t_token **head, t_data *data, int io_here_flag)
{
	int		i;
	int		space;
	t_token	*tmp;

	i = 0;
	tmp = NULL;
	while (str[i])
	{
		space = i;
		i = jump_spaces(str, i);
		if (str[i] == '\0')
			break ;
		if (space != i && space != 0)
		{
			tmp = fill_data(SPACE, 1, " ", data);
			ft_lst_add_back(head, tmp);
		}
		tmp = scan_token(&str[i], io_here_flag, data);
		if (!tmp)
			return (ft_lst_clear(head, free));
		ft_lst_add_back(head, tmp);
		io_here_flag = ft_heredoc(tmp);
		i += (int)tmp->data_size;
	}
}

int	ft_parse(char *str, t_token **head, t_data *data, t_token **shlvl) 
{
	t_heads	*line;
	int		here_flag;

	line = NULL;
	here_flag = 0;
	create_tokens(str, head, data, here_flag);
	ft_print(*head);
	if (!(*head))
		return (0);
	else
		return (cmd_line_building(head, &line, data, shlvl));
}
