/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaveux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 11:08:19 by cdaveux           #+#    #+#             */
/*   Updated: 2022/05/31 18:24:48 by cdaveux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	jump_spaces(char *str, int i)
{
	while (str[i] && (str[i] == '\t' || str[i] == '\v' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\f' || str[i] == 32))
		i++;
	return (i);
}

int	check_error(int i, char *str)
{
	i = jump_spaces(str, i);
	if (str[i] == '\0' || !ft_strncmp(str, "\"\"", 2))
	{
		if (!ft_strncmp(str, "\"\"", 2))
			error_msg(2, NULL);
		return (-1);
	}
	return (i);
}

int	distrib_token(t_token **head, t_token *tmp, t_data *data, char **spaceless)
{
	int		j;
	int		len;

	j = -1;
	len = 0;
	if (ft_strchr(tmp->data, 32) && tmp->token == 1)
	{
		spaceless = ft_split(tmp->data, 32);
		ft_lst_delone(tmp, free);
		while (spaceless[len])
			len++;
		while (spaceless[++j])
		{
			tmp = fill_data(WORD, ft_strlen(spaceless[j]), spaceless[j], data);
			ft_lst_add_back(head, tmp);
			if (j < len - 1)
				ft_lst_add_back(head, fill_data(SPACE, 1, " ", data));
			free(spaceless[j]);
		}
		free(spaceless);
	}
	else
		ft_lst_add_back(head, tmp);
	return (ft_heredoc(tmp));
}

int	check_tmp(t_token **head, t_token *tmp, t_data *data, int i)
{
	if (!tmp)
	{
		printf("bash : parsing error\n");
		ft_lst_clear(head, free);
		return (-1);
	}
	if (!tmp->data)
	{
		ft_lst_add_back(head, fill_data(SPACE, 1, " ", data));
		i += 2;
	}
	else
	i += (int)tmp->data_size;
	return (i);
}

void	create_tokens(char *str, t_token **head, t_data *data, int h_flag)
{
	int			i;
	int			space;
	t_token		*tmp;
	char		**spaceless;

	i = 0;
	tmp = NULL;
	while (str[i])
	{
		spaceless = NULL;
		space = i;
		i = check_error(i, str);
		if (i == -1)
			break ;
		if (space != i && space != 0)
			ft_lst_add_back(head, fill_data(SPACE, 1, " ", data));
		tmp = scan_token(&str[i], h_flag, data);
		i = check_tmp(head, tmp, data, i);
		if (i == -1)
			return ;
		if (tmp->data)
			h_flag = distrib_token(head, tmp, data, spaceless);
	}
}
