/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaveux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:11:40 by cdaveux           #+#    #+#             */
/*   Updated: 2022/05/30 18:21:36 by cdaveux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_token(char c)
{
	if (c == '<')
		return (REDIR_IN);
	if (c == '>')
		return (REDIR_OUT);
	if (c == '\'')
		return (SIMPLE_QUOTE);
	if (c == '\"')
		return (DOUBLE_QUOTE);
	if (c == '|')
		return (PIPE);
	if (c == '$')
		return (DOLLAR_SIGN);
	return (-1);
}

t_token	*fill_data(t_type token, int len, char *op, t_data *data)
{
	t_token	*new_token;
	int		i;

	i = -1;
	new_token = ft_create_token(token);
	if (token == DOLLAR_SIGN && ft_search_env(&op[1], data))
		return (split_env(new_token, op, data));
	if (token == DOLLAR_SIGN)
		len = ft_name(&op[1]) + 1;
	new_token->data = malloc(sizeof(char) * len + 1);
	if (!new_token->data)
		return (NULL);
	while (op[++i] && i < len)
		new_token->data[i] = op[i];
	new_token->data[len] = '\0';
	new_token->data_size = len;
	return (new_token);
}

t_token	*fill_data_bis(t_type token, int len, char *op, t_data *data)
{
	t_token	*new_token;
	int		i;

	i = -1;
	new_token = ft_create_token(token);
	if (token == DOLLAR_SIGN && ft_search_env(&op[1], data))
		return (split_env(new_token, op, data));
	if (token == DOLLAR_SIGN)
		len = ft_name(&op[1]) + 1;
	new_token->data = malloc(sizeof(char) * len + 1);
	if (!new_token->data)
		return (NULL);
	while (op[++i] && i < len)
		new_token->data[i] = op[i];
	new_token->data[len] = '\0';
	new_token->data_size = len;
	free(op);
	return (new_token);
}

t_token	*other_token(char *str, int io_here, t_data *datas)
{
	int		i;
	int		j;
	char	*data;

	i = -1;
	io_here = 0;
	j = 0;
	while (str[j] && find_token(str[j]) == -1 && ft_isprint((int)str[j])
		&& ft_strchr("\t\v\n\r ", (int)str[j]) == NULL)
		j++;
	data = malloc(sizeof(char) * j + 1);
	if (!data)
		return (NULL);
	while (++i < j)
	data[i] = str[i];
	data[j] = '\0';
	if (!io_here && ft_strchr((const char *)data, '=') != NULL)
		return (fill_data_bis(ASSIGN, j, data, datas));
	return (fill_data_bis(WORD, j, data, datas));
}

t_token	*scan_token(char *str, int io_here, t_data *data)
{
	if (ft_strncmp((const char *)str, "<<", 2) == 0)
		return (fill_data(HEREDOC, 2, "<<", data));
	else if (ft_strncmp((const char *)str, ">>", 2) == 0)
		return (fill_data(DOUBLE_GREATER, 2, ">>", data));
	else if (ft_strncmp((const char *)str, "$?", 2) == 0)
		return (fill_data(ECHO, 2, "$?", data));
	else if (ft_strncmp((const char *)str, "\"", 1) == 0)
		return (fill_data_quotes(DOUBLE_QUOTE, str, '\"', data));
	else if (ft_strncmp((const char *)str, "\'", 1) == 0)
		return (fill_data_quotes(SIMPLE_QUOTE, str, '\'', data));
	else if (ft_strncmp((const char *)str, "$", 1) == 0 && io_here == 0){printf("dollar token\n");
		return (fill_data(DOLLAR_SIGN, 0, &str[0], data));
	}
	else if (ft_strncmp((const char *)str, "$", 1) == 0 && io_here)
		return (fill_data(WORD, ft_name(&str[1]) + 1, &str[0], data));
	else if (find_token(str[0]) != -1)
		return (fill_data(find_token(str[0]), 1, &str[0], data));
	else
		return (other_token(str, io_here, data));
	return (NULL);
}
