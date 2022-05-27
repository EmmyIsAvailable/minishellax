/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaveux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:24:01 by cdaveux           #+#    #+#             */
/*   Updated: 2022/05/27 16:23:30 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	join_data(t_token **tmp)
{
	int		var_env;
	char	*str;

	str = NULL;
	var_env = 9;
	while (((*tmp) && (*tmp)->next)
		&& (((*tmp)->token != SPACE || (*tmp)->token != PIPE)))
	{
		if ((*tmp)->token == DOLLAR_SIGN)
			var_env = 1;
		if ((*tmp)->next->token == SPACE || (*tmp)->next->token == PIPE)
			break ;
		str = ft_strjoin((*tmp)->data, (*tmp)->next->data);
		ft_free(tmp);
		free((*tmp)->data);
		(*tmp)->data = ft_strdup(str);
		(*tmp)->token = var_env;
		free(str);
	}
	return (0);
}

int	check_token(t_token **head, t_token **inf, t_token **out, t_token **cmd)
{
	if ((*head) == NULL)
		return (0);
	if ((*head)->token == SPACE && !(*head)->next)
	{
		printf("bash: : command not found\n");
		return (1);
	}
	if ((*head)->token == SPACE)
		ft_free(head);
	if ((*head)->token == PIPE)
	{
		error_msg(0, "|");
		return (1);
	}
	if ((*head)->token == REDIR_IN)
		return (check_inf(head, inf, out, cmd));
	if ((*head)->token == REDIR_OUT)
		return (check_out(head, inf, out, cmd));
	if ((*head)->token == DOUBLE_GREATER)
		return (check_out_b(head, inf, out, cmd));
	if ((*head)->token == WORD || (*head)->token == DOUBLE_QUOTE
		|| (*head)->token == SIMPLE_QUOTE || (*head)->token == DOLLAR_SIGN
		|| (*head)->token == ASSIGN || (*head)->token == ECHO)
		return (check_word(head, inf, out, cmd));
	if ((*head)->token == HEREDOC)
		return (check_here(head, inf, out, cmd));
	return (1);
}

int	no_pipe(int count, t_heads **line, t_data *data, t_token **shlvl)
{
	t_heads	*final_line;

	final_line = NULL;
	create_shlvl(count, &(*line)->cmd, data, shlvl);
	if ((*line)->infile && (*line)->infile->token == 8 && !(*line)->cmd)
	{
		is_heredoc((*line)->infile->data, data);
		unlink((*line)->infile->data);
		return (0);
	}
	data->tmp_fd = open("pipe", O_CREAT | O_RDWR | O_TRUNC, 0777);
	data->exit_status = ft_pipex(data, &final_line, line);
	unlink("pipe");
	return (0);
}

int	cmd_line(t_token **head, t_heads **line, t_data *data, t_token **shlvl)
{
	int			j;
	int			count;
	t_heads		*tmp;

	count = 0;
	tmp = NULL;
	while (1)
	{
		j = 1;
		tmp = tmp_init();
		if (!tmp || !tmp->cmd)
			break ;
		if ((*head)->token != PIPE)
			j = check_token(head, &tmp->infile, &tmp->outfile, &tmp->cmd);
		else if ((*head)->token == PIPE)
		{
			error_msg(0, "|");
			break ;
		}	
		if (j == -1 || j == 0)
			push_heads(&tmp, line);
		if (j == -1)
			count += clear_head(head);
		else if (j == 0)
			return (no_pipe(count, line, data, shlvl));
		else if (j == 1)
			break ;
	}
	free_elem_heads(&tmp);
	ft_lst_clear(head, free);
	clear_all_heads(line);
	return (1);
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
