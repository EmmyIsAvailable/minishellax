/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaveux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:24:01 by cdaveux           #+#    #+#             */
/*   Updated: 2022/06/09 15:58:30 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_token(t_token **head, t_token **inf, t_token **out, t_token **cmd)
{
	if ((*head) == NULL)
		return (0);
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
	int		i;

	final_line = NULL;
	create_shlvl(count, &(*line)->cmd, data, shlvl);
	if ((*line)->infile && (*line)->infile->token == 8 && !(*line)->cmd)
	{
		is_heredoc((*line)->infile->data, data);
		unlink((*line)->infile->data);
		clear_all_heads(line);
		return (0);
	}
	i = ft_no_fork(line, data, &final_line);
	if (i != -1)
	{
		data->exit_status = i;
		return (0);
	}
	data->tmp_fd = open("pipe", O_CREAT | O_RDWR | O_TRUNC, 0777);
	i = 0;
	data->exit_status = ft_pipex(data, &final_line, i);
	if (data->tmp_fd > 0)
		close(data->tmp_fd);
	unlink("pipe");
	return (0);
}

void	no_leaks_combo(t_heads **tmp, t_token **head, t_heads **line)
{
	free_elem_heads(tmp);
	ft_lst_clear(head, free);
	clear_all_heads(line);
}

int	cmd_line(t_token **head, t_heads **line, t_data *data, t_token **shlvl)
{
	int			j;
	int			count;
	t_heads		*tmp;

	count = 0;
	j = 0;
	while (j != 1)
	{
		tmp = tmp_init();
		if ((*head)->token == PIPE)
		{
			error_msg(0, "|");
			break ;
		}
		j = check_token(head, &tmp->infile, &tmp->outfile, &tmp->cmd);
		if (j != 1)
			push_heads(&tmp, line);
		if (j == -1)
			count += clear_head(head);
		else if (j == 0)
			return (no_pipe(count, line, data, shlvl));
	}
	no_leaks_combo(&tmp, head, line);
	return (1);
}

int	ft_parse(char *str, t_token **head, t_data *data, t_token **shlvl)
{
	int		here_flag;
	t_heads	*line;

	here_flag = 0;
	line = NULL;
	create_tokens(str, head, data, here_flag);
	if (!(*head))
		return (0);
	else
		return (cmd_line(head, &line, data, shlvl));
}
