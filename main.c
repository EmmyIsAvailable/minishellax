/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:52:49 by eruellan          #+#    #+#             */
/*   Updated: 2022/05/19 15:10:05 by cdaveux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmp_line(char *history, char *str)
{
	int	i;

	i = jump_spaces(history, 0);
	if (ft_strncmp(&history[i], str, ft_strlen(str)) != 0)
		return (1);
	return (0);
}

int	ft_shlvl(t_data *data, char *history, t_token **shlvl)
{
	if ((data->shlvl == 1 && history == NULL) || (history && data->shlvl == 1
			&& ft_message(history, "exit") == 0))
		return (0);
	else if (history && ft_message(history, "./minishell") == 0)
		change_shlvl(data, '+');
	else if (data->shlvl > 1 && ((history && ft_message(history,
					"exit") == 0) || history == NULL))
	{
		ft_prev_envp(shlvl, data);
		history = "";
	}
	return (1);
}

int	minishell(t_data data, t_token *head, t_token *shlvl)
{
	char	*history;

	history = NULL;
	event_ctrl_c();
	while (data.shlvl != -1)
	{
		head = NULL;
		history = readline("$> ");
		if (ft_shlvl(&data, history, &shlvl) == 0)
			break ;
		if (history && ft_cmp_line(history, "./minishell") != 0)
			ft_parse(history, &head, &data, &shlvl);
		add_history(history);
		free(history);
	}
	ft_lst_clear(&shlvl, free);
	free(history);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	t_token	*head;
	t_token	*shlvl;

	shlvl = NULL;
	head = NULL;
	(void)av;
	if (ac != 1)
	{
		ft_putstr_fd("./minishell: too many arguments\n", 1);
		return (1);
	}
	init_envp(&data, envp);
	minishell(data, head, shlvl);
	free_tab(data.envp);
	return (0);
}
