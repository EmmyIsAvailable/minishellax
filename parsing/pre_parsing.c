/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaveux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 11:08:19 by cdaveux           #+#    #+#             */
/*   Updated: 2022/05/30 17:48:38 by cdaveux          ###   ########.fr       */
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

void	ft_split_token(t_token **head, t_token *cmd, t_data *data)
{
	char	**spaceless;
	t_token	*tmp;
	int		i;
	int		len;

	spaceless = NULL;
	i = 0;
	len = 0;
	spaceless = ft_split(cmd->data, 32);
	while (spaceless[len])
		len++;
	while (spaceless[i])
	{
		tmp = fill_data(WORD, ft_strlen(spaceless[i]), spaceless[i], data);
		ft_lst_add_back(head, tmp);
		if (i < len - 1)
		{
			tmp = fill_data(SPACE, 1, " ", data);
			ft_lst_add_back(head, tmp);
		}
		free(spaceless[i]);
		i++;
	}
	free(spaceless);
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

void	ft_distrib(t_token **head, t_token *tmp, t_data *data)
{
	if (ft_strchr(tmp->data, 32) && tmp->token == 1)
		ft_split_token(head, tmp, data);
	else
		ft_lst_add_back(head, tmp);
}

void	create_tokens(char *str, t_token **head, t_data *data, int h_flag)
{
	int	i;
	int	space;
	t_token	*tmp;

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
		{
			printf("bash : parsing error\n");
			return (ft_lst_clear(head, free));
		}
		ft_distrib(head, tmp, data);
		h_flag = ft_heredoc(tmp);
		i += (int)tmp->data_size;
	}
}
