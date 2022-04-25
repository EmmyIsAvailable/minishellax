/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaveux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:24:01 by cdaveux           #+#    #+#             */
/*   Updated: 2022/04/22 13:48:38 by cdaveux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	join_data(t_token **tmp)
{
	char	*str;

	str = NULL;
	while (((*tmp) && (*tmp)->next)
		&& (((*tmp)->token != SPACE || (*tmp)->token != PIPE)))
	{
		if (((*tmp)->token == WORD && (*tmp)->next->token == WORD)
			|| (*tmp)->next->token == SPACE || (*tmp)->next->token == PIPE)
			break ;
		str = ft_strjoin((*tmp)->data, (*tmp)->next->data);
		(*tmp)->token = SPACE;
		(*tmp) = (*tmp)->next;
		(*tmp)->data = str;
	}
	return (0);
}

int	check_token(t_token **head, t_token **inf, t_token **out, t_token **cmd)
{
	if ((*head) == NULL)
		return (0);
	if ((*head)->token == SPACE)
		(*head) = (*head)->next;
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

t_heads	*tmp_init(void)
{
	t_heads	*tmp;

	tmp = malloc(sizeof(t_heads));
	if (!tmp)
		return (NULL);
	tmp->infile = NULL;
	tmp->outfile = NULL;
	tmp->cmd = NULL;
	return (tmp);
}

void	clear_head(t_token **head)
{
	while ((*head) && (*head)->token != 0)
		ft_free(head);
	ft_free(head);
}

int	ft_parsing_error(char *str)
{
	printf("%s", str);
	return (1);
}

t_token	*ft_duplicate(t_token **cmd, int shell_lvl, int cmd_env)
{
	t_token	*new;

	new = ft_create_token((*cmd)->token);
	if (!new)
		return (NULL);
	new->data = ft_strdup((*cmd)->data);
	new->data_size = (*cmd)->data_size;
	new->shlvl = shell_lvl;
	new->cmd_env = cmd_env;
	return (new);
}

int	ft_bool(char *str)
{
	if (!ft_strncmp(str, "export", ft_strlen(str)))
		return (0);
	if (!ft_strncmp(str, "unset", ft_strlen(str)))
		return (1);
	return (-1);
}

int	cmd_line_building(t_token **head, t_heads **line, t_data *data, t_token **shlvl)
{
	int			j;
	int			count;
	t_heads		*tmp;
	t_token		*cmd_env;

	count = 0;
	tmp = NULL;
	cmd_env = NULL;
//	(void)shlvl;
//	(void)data;
	while (1)
	{
		j = 1;
		tmp = tmp_init();
		if (!tmp)
			break ;
		if ((*head)->token != PIPE)
			j = check_token(head, &tmp->infile, &tmp->outfile, &tmp->cmd);
		if (j == -1)
		{
			push_heads(&tmp, line);
			clear_head(head);
			count++;
		}
		else if (j == 0)
		{
			if (count == 0 && ft_bool(tmp->cmd->data) != -1)
			{
				printf("bool : %d\n", ft_bool(tmp->cmd->data));
				cmd_env = ft_duplicate(&tmp->cmd->next, data->shlvl, ft_bool(tmp->cmd->data));
				push(&cmd_env, shlvl);
				printf("shlvl: \n");
				ft_print(*shlvl);
			}
			push_heads(&tmp, line);
			ft_print_line(line);
			//ft_print_line(line);
			//is_heredoc(line);
//			return (ft_pipex(line, data, shlvl));
			return (0);		
		}
		else if (j == 1)
			return (ft_parsing_error("parsing error\n"));
	}
	return (1);
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
