#include "minishell.h"

int	check_token(char c)
{
	if (c == '<')
		return (REDIR_IN);
	if (c == '>')
		return (REDIR_OUT);
	if (c == '\'')
		return (SIMPLE_QUOTE);
	if (c == '"')
		return (DOUBLE_QUOTE);
	if (c == '=')
		return (EQ);
	if (c == '|')
		return (PIPE);
	if (c == '$')
		return (DOLLAR_SIGN);
	return (-1);
}

int	is_print_and_no_token(char *str, int len)
{
	int	i;
	char c;

	i = 0;
	c = 0;
	while (str[i] && i < len)
	{
		c = str[i];
		if ((c < 32 || c >= 127) && check_token(str[i]) == -1)
			return (0);
		i++;
	}
	return (1);
}

t_token	*ft_lst_last(t_token *lst)
{
	while (lst -> next)
		lst = lst -> next;
	return (lst);
}

void	ft_lst_add_back(t_token **alst, t_token *new)
{
	if (alst)
	{
		if (*alst)
			ft_lst_last(*alst)->next = new;
		else
			*alst = new;
	}
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
	while (op[++i])
		new_token->data[i] = op[i];
	new_token->data[len] = '\0';
	new_token->data_size = len;
	new_token->next = NULL;
//	free(op);
	return (new_token);
}

t_token	*scan_token(char *str)
{
	int		i;
//	int		j;
	int		len;
	char	*data;

	i = -1;
	len = 1;
//	j = -1;
//	len = 1;
	data = NULL;
	if (ft_strncmp((const char *)str, "<<", 2) == 0)
		return (fill_data(HEREDOC, 2, "<<"));
	else if (ft_strncmp((const char *)str, ">>", 2) == 0)
		return (fill_data(DOUBLE_GREATER, 2, ">>"));
	else if (check_token(str[i + len]) != -1 && check_token(str[i + len]) < 9)
		return (fill_data(check_token(str[i + len]), 1, &str[i + len]));
	else 
	{
		while (str[i + len] && str[i + len] != 32 && is_print_and_no_token(str, len))
			len++;
		data = malloc(sizeof(char) * len + 1);
		while (++i < len)
			data[i] = str[i];
		data[len] = '\0';
		return (fill_data(WORD, len, data));
	}
/*	while (str[i + len] && str[i + len] != 32)
	{
		if (ft_strncmp((const char *)str, "<<", 2) == 0)
			return (fill_data(HEREDOC, 2, "<<"));
		else if (ft_strncmp((const char *)str, ">>", 2) == 0)
			return (fill_data(DOUBLE_GREATER, 2, ">>"));
		else if (check_token(str[i + len]) != -1 && check_token(str[i + len]) < 13)
			return (fill_data(check_token(str[i]), 1, &str[i + len]));
		len++;
	}
	printf("len : %d\n", len);
	if (str[i] && is_print(str, len))
	{
		data = malloc(sizeof(char) * len + 1);
		while (++j < len)
			data[j] = str[i + j];
		data[len] = '\0';
		return (fill_data(WORD, len, data));
	}*/
	return (NULL);
}

int	ft_parse(char *str, t_token **head)
{
	int	i;
	t_token	*tmp;

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
			return (1);
		ft_lst_add_back(head, tmp);
		i += (int)tmp->data_size;
	}
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

int	main(int ac,char **av)
{
	(void)ac;
	t_token	*head;
//	t_token	*tmp;

	head = NULL;
	ft_parse(av[1], &head);
	ft_print(head);
/*	while (head != NULL)
	{
		free(head->data);
		tmp = head;
		free(tmp);
		head = head->next;
	}*/	
	return (0);
}