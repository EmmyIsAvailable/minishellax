/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaveux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 11:08:19 by cdaveux           #+#    #+#             */
/*   Updated: 2022/06/02 11:11:54 by cdaveux          ###   ########.fr       */
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

int	distrib_token(t_token **head, t_token *tmp, t_data *data, int len)
{
	int		j;
	char	**spaceless;

	j = -1;
	spaceless = NULL;
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

void	routine_supp(t_token **head)
{
	printf("bash : parsing error\n");
	ft_lst_clear(head, free);
}

void	create_tokens(char *str, t_token **head, t_data *data, int h_flag)
{
	int			i;
	int			space;
	t_token		*tmp;

	i = 0;
	tmp = NULL;
	while (str[i])
	{
		space = i;
		i = check_error(i, str);
		if (i == -1)
			break ;
		if (space != i && space != 0)
			ft_lst_add_back(head, fill_data(SPACE, 1, " ", data));
		tmp = scan_token(&str[i], h_flag, data);
		if (!tmp)
			return (routine_supp(head));
		i += (int)tmp->data_size;
		if (tmp->data)
			h_flag = distrib_token(head, tmp, data, i);
		else
			ft_lst_delone(tmp, free);
	}
}
