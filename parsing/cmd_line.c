/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaveux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:24:01 by cdaveux           #+#    #+#             */
/*   Updated: 2022/04/14 15:53:18 by cdaveux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_token(t_token **head, t_token **inf, t_token **out, t_token **cmd)
{
	if ((*head)->token == SPACE)
		(*head) = (*head)->next;
	if ((*head) == NULL)
		return (0);
	if ((*head)->token == REDIR_IN)
		return (check_infile(head, inf, out, cmd));
	if ((*head)->token == REDIR_OUT)
		return (check_outfile(head, inf, out, cmd));
	if ((*head)->token == DOUBLE_GREATER)
		return (check_append(head, inf, out, cmd));
	if ((*head)->token == WORD || (*head)->token == DOUBLE_QUOTE
		|| (*head)->token == SIMPLE_QUOTE || (*head)->token == DOLLAR_SIGN
		|| (*head)->token == ASSIGN || (*head)->token == ECHO)
		return (check_word(head, inf, out, cmd));
	if ((*head)->token == HEREDOC)
		return (check_here(head, inf, out, cmd));
	return (1);
}

int	cmd_line_building(t_token **head, t_heads **line, t_data *data)
{
	int		j;
	t_heads	*tmp = NULL;
	(void)data;

	j = 0;
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
			push_heads(&tmp, line);
			while ((*head)->token != 0)
				ft_free(head);
			ft_free(head);
		}
		else if (j == 0)
		{
			push_heads(&tmp, line);
			ft_print_line(line);
			return (0);
//			return (ft_pipex(line, data));
		}
		else if (j == 1)
		{
			printf("parsing error\n");
			return (1);
		}
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
		printf("i : %d, token : %u, data : %s, size : %zu, fd : %d\n", i, temp->token, temp->data, temp->data_size, temp->fd);
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
