/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaveux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:11:40 by cdaveux           #+#    #+#             */
/*   Updated: 2022/04/07 14:40:13 by cdaveux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_token(char c)
{
	if (c == '<')
		return (REDIR_IN);
	if (c == '>')
		return (REDIR_OUT);
//	if (c == '\'')
//		return (SIMPLE_QUOTE);
//	if (c == '"')
//		return (DOUBLE_QUOTE);
	if (c == '|')
		return (PIPE);
	return (-1);
}

t_token	*fill_data(token_type token, int len, char *op)
{
	t_token	*new_token;
	int		i;

	i = -1;
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->token = token;
	new_token->data = malloc(sizeof(char) * len + 1);
	if (!new_token->data)
		return (NULL);
	while (op[++i] && i < len)
		new_token->data[i] = op[i];
	new_token->data[len] = '\0';
	printf("data :%s\n", new_token->data);	
	new_token->data_size = len;
	new_token->fd = 1;
	new_token->next = NULL;
	return (new_token);
}

int	ft_name(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while(str[++i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (i);
	}
	return (i);
}

char	*ft_search_env(char *params, t_data *data)
{
	char	**envp;
	int	i;

	i = 0;
	envp = data->envp;
	while (envp[i])
	{
		if (ft_strncmp(&envp[i][ft_name(params)], "=", 1) == 0) //ft_name va au dernier caractere non alphanum ou underscore
		{
			if (ft_strncmp(envp[i], params, ft_name(params)) == 0)
				return(&envp[i][ft_name(params) + 1]);
		}
		i++;
	}
	return (NULL);
}

t_token	*fill_data_quotes(token_type token, char *str, char op, t_data *data)
{
	t_token	*new_token;
	int		i;
	int		j;

	i = 1;
	j = 0;
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->token = token;
	new_token->data = NULL;
	while (str[i] != op)
	{
		if (str[i] == '$' && token == DOUBLE_QUOTE && ft_search_env(&str[i + 1], data))
		{
			j = 0;
			if (i > 1 && !new_token->data) // tout ce qui est avant le $ est mis dans data 
			{
				new_token->data = malloc(sizeof(char) * (i));
				if (!new_token->data)
					return (NULL);
				while (str[++j] && j < i)
					new_token->data[j - 1] = str[j];
				new_token->data[i - 1] = '\0';
			}
			new_token->data = ft_strjoin((const char *)new_token->data, (const char *)ft_search_env(&str[i + 1], data)); //free new_token precedemment alloue dans join
			i += (1 + ft_name(&str[i + 1]));//passer tout le token $machin
		}
		else
			i++;
	}
	if (!new_token->data)
	{
		printf("i :%d\n", i);
		new_token->data = malloc(sizeof(char) * (i));
		if (!new_token->data)
			return (NULL);
		while (str[++j] && j < i)
			new_token->data[j - 1] = str[j];
		new_token->data[i - 1] = '\0';
		printf("data :%s\n", new_token->data);
	}
	new_token->data_size = i + 1;
	printf("token size :%ld\n", new_token->data_size);
	new_token->fd = 1;
	new_token->next = NULL;
	return (new_token);
}

t_token	*other_token(char *str, int io_here)
{
	int		i;
	int		j;
	char	*data;

	i = -1;
	j = -1;
	while (str[++j] && find_token(str[j]) == -1 && str[j] != ' ') //metttre tt isspae3
	{
		if (!io_here && ft_isalnum(str[j]) == 0 && ft_strchr("_$,/.-+=", (int)str[j]) == NULL) //liste arbitrairre de caracteres qui passent : peut etre tester tous les printable sauf isspace3
			break ;	
		//return (NULL); 
	}
	if (j == 0)
		return (NULL);
	data = malloc(sizeof(char) * j + 1);
	if (data)
	{
		while (++i < j)
			data[i] = str[i];
		data[j] = '\0';
		if (!io_here && data[0] == '$' && ft_strchr((const char *)data, '=') == NULL)
			return (fill_data(DOLLAR_SIGN, j, data));
		else if (!io_here && ft_strchr((const char *)data, '=') != NULL)
			return (fill_data(ASSIGN, j, data));
		return (fill_data(WORD, j, data));
	}
	return (NULL);
}

t_token	*scan_token(char *str, int io_here, t_data *data)
{ 
	if (ft_strncmp((const char *)str, "<<", 2) == 0)
		return (fill_data(HEREDOC, 2, "<<"));
	else if (ft_strncmp((const char *)str, ">>", 2) == 0)
		return (fill_data(DOUBLE_GREATER, 2, ">>"));
	else if (ft_strncmp((const char *)str, "\"", 1) == 0)
		return (fill_data_quotes(DOUBLE_QUOTE, str, '\"', data));
	else if (ft_strncmp((const char *)str, "\'", 1) == 0)
		return (fill_data_quotes(SIMPLE_QUOTE, str, '\'', data));// 0 interpretation de meta caracteres 
	else if (find_token(str[0]) != -1)
		return (fill_data(find_token(str[0]), 1, &str[0]));
	else
		return (other_token(str, io_here));
	return (NULL);
}

int	ft_parse(char *str, t_token **head, t_data *data)
{
	int		i;
	int		io_here_flag;
	int		space;
	t_token	*tmp = NULL;
//	t_heads *line = NULL;
  
	(void)data;
	i = 0;
	io_here_flag = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		space = i;
		while (str[i] && (str[i] == '\t' || str[i] == '\v' || str[i] == '\n'
				|| str[i] == '\r' || str[i] == '\f' || str[i] == 32))
			i++;
		if (str[i] == '\0')
			break;
		if (space != i && space != 0)
		{
			tmp = fill_data(SPACE, 1, " ");
			ft_lst_add_back(head, tmp);
		}
		tmp = scan_token(&str[i], io_here_flag, data);
		io_here_flag = 0;
		if (!tmp)
		{
			ft_lst_clear(head, free);
			return (1);
		}
		if (tmp->token == 8)
			io_here_flag = 1;
		ft_lst_add_back(head, tmp);
		i += (int)tmp->data_size;
	}
	ft_print(*head);
//	return (cmd_line_building(head, &line, data));
//		return (1);
	return (0);
}
