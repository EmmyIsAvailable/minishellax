/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaveux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:24:01 by cdaveux           #+#    #+#             */
/*   Updated: 2022/03/22 15:25:51 by cdaveux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_token(char c)
{
	if (c == '<')
		return (REDIR_IN);
	if (c == '>')
		return (REDIR_OUT);
	if (c == '\'')
		return (SIMPLE_QUOTE);
	if (c == '"')
		return (DOUBLE_QUOTE);
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
	new_token->data_size = len;
	new_token->next = NULL;
	return (new_token);
}

t_token	*other_token(char *str)
{
	int		i;
	int		j;
	char	*data;

	i = -1;
	j = -1;
	while (str[++j] && find_token(str[j]) == -1 && str[j] != ' ')
	{
		if (ft_isalnum(str[j]) == 0 && ft_strchr("_$,=/.-", (int)str[j]) == NULL)
			return (NULL);
	}
	data = malloc(sizeof(char) * j + 1);
	if (data)
	{
		while (++i < j)
			data[i] = str[i];
		data[j] = '\0';
		if (data[0] == '$' && ft_strchr((const char *)data, '=') == NULL)
			return (fill_data(DOLLAR_SIGN, j, data));
		else if (data[0] != '$' && ft_isalpha((int)data[0]) && ft_strchr((const char *)data, '=') != NULL) //pas trop sure la
			return (fill_data(ASSIGN, j, data));
		return (fill_data(WORD, j, data));
	}
	return (NULL);
}

t_token	*scan_token(char *str)
{
	 if (ft_strncmp((const char *)str, "<<", 2) == 0)
		return (fill_data(HEREDOC, 2, "<<"));
	else if (ft_strncmp((const char *)str, ">>", 2) == 0)
		return (fill_data(DOUBLE_GREATER, 2, ">>"));
	else if (find_token(str[0]) != -1)
		return (fill_data(find_token(str[0]), 1, &str[0]));
	else
		return (other_token(str));
	return (NULL);
}

int	cmd_line_building(t_token **head, t_heads **line)
{
	int		j;
	t_heads	*tmp = NULL;
	t_token	*temp;

	j = 0;
	temp = NULL;
	while (1)
	{
		tmp = malloc(sizeof(t_heads));
		if (!tmp)
			return (1);
		tmp->infile = NULL;
		tmp->outfile = NULL;
		tmp->cmd = NULL;	
		j  = check_token(head, &tmp->infile, &tmp->outfile, &tmp->cmd);
		if (j == -1)
		{
			temp = (*head);
			(*head) = (*head)->next;
			free(temp);
			push_heads(&tmp, line);
		}
		else if (j == 0)
		{
			push_heads(&tmp, line);
			ft_print_line(line);
			//ici lancer pipex
			return (0);
		}
		else if (j == 1)
		{
			printf("parsing error\n");
			return (1);
		}
	}
	return (0);
}

int	ft_parse(char *str, t_token **head)
{
	int		i;
	t_token	*tmp = NULL;
	t_heads *line = NULL;
  
	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		while (str[i] && (str[i] == '\t' || str[i] == '\v' || str[i] == '\n'
				|| str[i] == '\r' || str[i] == '\f' || str[i] == 32))
			i++;
		tmp = scan_token(&str[i]);
		if (!tmp)
		{
			ft_lst_clear(head, free);
			return (1);
		}
		ft_lst_add_back(head, tmp);
		i += (int)tmp->data_size;
	}
	if (cmd_line_building(head, &line) == 1)
		return (1);
	return (0);
}

void	ft_print(t_token *head)
{
	t_token	*temp;
	int		i;

	temp = head;
	i = 0;
	while (temp != NULL)
	{
		printf("i : %d, token : %u, data : %s, size : %zu\n", i, temp->token, temp->data, temp->data_size);
		i++;
		temp = temp->next;
	}
}

void	ft_print_line(t_heads **line)
{
	t_heads	**temp;
	int		i;

	temp = line;
	i = 0;
	while ((*temp) != NULL)
	{
		printf("i : %d\n", i);
		ft_print((*temp)->cmd);
		ft_print((*temp)->infile);
		ft_print((*temp)->outfile);
		i++;
		(*temp) = (*temp)->next;
	}
}
