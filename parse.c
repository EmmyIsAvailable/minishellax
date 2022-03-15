#include "minishell.h"

int	is_alphanum(char *str, int len)
{
	int	i;
	char c;

	i = -1;
	c = 0;
	while (str[++i] && i < len)
	{
		c = str[i];
		if ((c < '0' || c > '9') && (c < 'A' || c > 'Z')
			&& (c < 'a' || c > 'z'))
			return (0);
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
	new_token = (t_token *)malloc(sizeof(t_token));
	new_token->token = token;
	new_token->data = malloc(sizeof(char) * 3);
	if (!new_token->data)
			return (NULL);
	while (op[++i])
		new_token->data[i] = op[i];
	new_token->data[len] = '\0';
	new_token->data_size = len;
	new_token->next = NULL;
	free(op);
	return (new_token);
}

int	check_token(char c)
{
	if (c == SPACE)
		return (SPACE);
	if (c == PIPE)
		return (PIPE);
	if (c == DOLLAR_SIGN)
		return (DOLLAR_SIGN);
	return (-1);
}

t_token	*scan_token(char *str)
{
//	t_token	*new_token;
//	token_type	tokens;
	int		i;
	int		len;
	char	*data;

	i = -1;
	len = 1;
	data = NULL;
	while (str[++i] != ' ' && str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
			return (fill_data(HEREDOC, 2, "<<"));
		else if (str[i] == '>' && str[i] == '>')
			return (fill_data(DOUBLE_GREATER, 2, ">>"));
		else if (check_token(str[i]) != -1 && check_token(str[i]) < 13)
			return (fill_data(check_token(str[i]), 1, &str[i]));
		len++;
	}
	if (str[i] != 0 && is_alphanum(str, len))
	{
		i = -1;
		data = malloc(sizeof(char) * len + 1);
		while (++i < len)
			data[i] = str[i];
		data[len] = '\0';
		return (fill_data(WORD, len, data));
	}
	return (NULL);
}

int	ft_parse(char *str, t_token **head)
{
	int	i;
	t_token	*tmp;

	i = 0;
	if (!str)
		return (1);
	while (str[i]) // (str[i] != EOF || str[i] != '\n')
	{
		tmp = scan_token(&str[i]);
		printf("%d\n", i);	
		i += (int)tmp->data_size;
		ft_lst_add_back(head, tmp);
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

	head = NULL;
	ft_parse(av[1], &head);
//	ft_print(head);
	return (0);
}
