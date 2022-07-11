/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:52:49 by eruellan          #+#    #+#             */
/*   Updated: 2022/07/07 12:04:13 by cdaveux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_global(void)
{
	if (g_global == 1)
		return (130);
	else if (g_global == 2)
		return (131);
	return (0);
}

int	minishell(t_data *data, t_token *head, t_token *shlvl)
{
	char	*history;
	char	*ret;

	history = NULL;
	while (data->shlvl != -1)
	{
		event_ctrl_c(1);
		head = NULL;
		history = readline("$> ");
		ret = ft_shlvl(data, history, &shlvl);
		if (!ret)
			break ;
		else if (ft_strncmp(ret, "history", 7) == 0)
			history = ft_strdup("");
		data->exit_status = ft_global();
		if (g_global == 1 || g_global == 2)
			g_global = 0;
		if (history && ft_cmp_line(history, "./minishell") != 0)
			ft_parse(history, &head, data, &shlvl);
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
	minishell(&data, head, shlvl);
	free_tab(data.envp);
//	close_fds(&data);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
//	if (data.tmp_fd > 0)
//		close(data.tmp_fd);
	return (0);
}
