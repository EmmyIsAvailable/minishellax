/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaveux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:21:28 by cdaveux           #+#    #+#             */
/*   Updated: 2022/05/31 16:47:00 by cdaveux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_msg(int type, __attribute__((unused))char *str)
{
	if (type == 1)
		write(STDERR_FILENO, "bash: syntax error near unexpected token `newline'\n", 51);
	else if (type == 0)
		write(STDERR_FILENO, "bash: syntax error near unexpected token\n", 41);
	else
		write(STDERR_FILENO, " : command not found\n", 21);
	return (1);
}

t_token	*ft_create_token(t_type token)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->token = token;
	new_token->data = NULL;
	new_token->fd = 1;
	new_token->next = NULL;
	new_token->prev = NULL;
	new_token->shlvl = 0;
	new_token->cmd_env = -1;
	return (new_token);
}

char	*ft_dup(char *data, int i, int diff, char *str)
{
	char	*tmp;
	char	*tmp_bis;
	int		j;

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
	tmp_bis = ft_strdup(data);
	free(data);
	data = ft_strjoin(tmp_bis, tmp);
	free(tmp_bis);
	free(tmp);
	tmp = NULL;
	return (data);
}

void	ft_print(t_token *head)
{
	t_token	*temp;
	int		i;

	temp = head;
	i = 0;
	if (temp)
	{
		while (temp != NULL)
		{
			printf("i : %d, tok : %u, data : %s, ", i, temp->token, temp->data);
			printf("shlvl : %d, cmd_env : %d\n", temp->shlvl, temp->cmd_env);
			i++;
			temp = temp->next;
		}
	}
}

void	ft_print_line(t_heads **line)
{
	t_heads	*temp;
	int		i;

	temp = (*line);
	i = 0;
	while (temp != NULL)
	{
		printf("i : %d\n", i);
		ft_print(temp->cmd);
		ft_print(temp->infile);
		ft_print(temp->outfile);
		i++;
		temp = temp->next;
	}
}
