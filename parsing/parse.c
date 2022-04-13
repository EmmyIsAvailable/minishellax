/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaveux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:11:40 by cdaveux           #+#    #+#             */
/*   Updated: 2022/04/07 16:25:00 by cdaveux          ###   ########.fr       */
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

t_token	*ft_create_token(token_type token)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->token = token;
	new_token->data = NULL;
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

	i = -1;
	envp = data->envp;
	while (envp[++i])
	{
		if (ft_strncmp(&envp[i][ft_name(params)], "=", 1) == 0)
		{
			if (ft_strncmp(envp[i], params, ft_name(params)) == 0)
				return(&envp[i][ft_name(params) + 1]);
		}
	}
	return (NULL);
}

char	*ft_dup(char *data, int i, int diff, char *str)
{
	char	*tmp;
	int	j;

	j = 0;
	tmp = malloc(sizeof(char) * (i - diff + 1));
	if (!tmp)
		return (NULL);
	while (j < i - diff)
	{
		tmp[j] = str[diff + j];
		j++;
	}
	tmp[j] = '\0';
	data = ft_strjoin(data, tmp);
	free(tmp);
	tmp = NULL;
	return (data);
}

char	*ft_create_data(char *str, int i)
{
	char	*data;
	int		j;

	j = 0;
	data = malloc(sizeof(char) * (i));
	if (!data)
		return (NULL);
	while (str[++j] && j < i)
		data[j - 1] = str[j];
	data[i - 1] = '\0';
	return (data);
}

t_token	*fill_data_quotes(token_type token, char *str, char op, t_data *data)
{
	t_token	*new_token;
	int		i;
	int		diff;

	i = 1;
	diff = 1;
	new_token = ft_create_token(token);
	while (str[i] != op)
	{
		if (str[i] == '$' && token == DOUBLE_QUOTE && ft_search_env(&str[i + 1], data))
		{
			if (i > 1 && !new_token->data)
				new_token->data = ft_create_data(str, i);
			else if (diff != i)
				new_token->data = ft_dup(new_token->data, i, diff, str);
			new_token->data = ft_strjoin(new_token->data, (const char *)ft_search_env(&str[i + 1], data));
			i += (1 + ft_name(&str[i + 1]));
			diff = i;
		}
		else
			i++;
	}
	if (!new_token->data)
		new_token->data = ft_create_data(str, i);
	else if (diff != i)
		new_token->data = ft_dup(new_token->data, i, diff, str);
	new_token->data_size = i + 1;
	return (new_token);
}

char	*ft_split_var(char *str)
{
	char	**data;
	char	*tmp;
	int		i;

	i = -1;
	data = ft_split(str, 32);
	if (!str)
		return (NULL);
	while (data[++i] != NULL && data[i + 1] != NULL)
	{
	//	printf("%s\n", data[i]);
		tmp = ft_strjoin(data[i], data[i + 1]); // il faut join en inserant un espce ! pas le cas ici
		if (!tmp)
		{
			//free tout
			return (NULL);
		}
	}
	free(data);
	return (tmp);
}

t_token	*fill_data(token_type token, int len, char *op, t_data *data)
{
	t_token	*new_token;
//	char	*tmp; // sert pour spliter les var dans "" mais bug
	int		i;

	i = -1;
	new_token = ft_create_token(token);
	if (token == DOLLAR_SIGN && ft_search_env(&op[1], data)) //$ en dehors quotes
	{
			new_token->data = ft_strdup((const char *)ft_search_env(&op[1], data));
		/*	tmp = ft_strdup((const char *)ft_search_env(&op[1], data));
			if (!tmp)
				return (NULL);
			new_token->data = ft_split_var(tmp);
			free(tmp);*/
			new_token->data_size = ft_name(&op[1]) + 1;
			return (new_token);
	}
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

t_token	*other_token(char *str, int io_here, t_data *datas)
{
	int		i;
	int		j;
	char	*data;

	i = -1;
	j = -1;
	if (!str)
		return (NULL);
	while (str[++j] && find_token(str[j]) == -1 && (str[j] != '\t' || str[j] != '\v'
		|| str[j] != '\n' || str[j] != '\r' || str[j] != '\f' || str[j] != 32))
	{
		if (!io_here && ft_isalnum(str[j]) == 0 && ft_strchr("_,/.-+$=*", (int)str[j]) == NULL) //liste arbitrairre
			break ;	
	}
	data = malloc(sizeof(char) * j + 1);
	if (!data)
		return (NULL);
	while (++i < j)
	data[i] = str[i];
	data[j] = '\0';
	if (!io_here && ft_strchr((const char *)data, '=') != NULL)
		return (fill_data(ASSIGN, j, data, datas));
	return (fill_data(WORD, j, data, datas));
	return (NULL);
}

t_token	*scan_token(char *str, int io_here, t_data *data)
{ 
	if (ft_strncmp((const char *)str, "<<", 2) == 0)
		return (fill_data(HEREDOC, 2, "<<", data));
	else if (ft_strncmp((const char *)str, ">>", 2) == 0)
		return (fill_data(DOUBLE_GREATER, 2, ">>", data));
	else if (ft_strncmp((const char *)str, "\"", 1) == 0)
		return (fill_data_quotes(DOUBLE_QUOTE, str, '\"', data));
	else if (ft_strncmp((const char *)str, "\'", 1) == 0)
		return (fill_data_quotes(SIMPLE_QUOTE, str, '\'', data));
	else if (ft_strncmp((const char *)str, "$", 1) == 0)
		return (fill_data(DOLLAR_SIGN, 0, &str[0], data));
	else if (find_token(str[0]) != -1)
		return (fill_data(find_token(str[0]), 1, &str[0], data));
	else
		return (other_token(str, io_here, data));
	return (NULL);
}

int	ft_parse(char *str, t_token **head, t_data *data)
{
	int		i;
	int		io_here_flag;
	int		space;
	t_token	*tmp = NULL;
	t_heads *line = NULL;
  
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
			tmp = fill_data(SPACE, 1, " ", data);
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
//	ft_print(*head);
	return (cmd_line_building(head, &line, data));
		return (1);
	return (0);
}
