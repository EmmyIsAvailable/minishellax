/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:52:49 by eruellan          #+#    #+#             */
/*   Updated: 2022/06/09 15:37:52 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_shlvl(t_data *data, char c)
{
	char	*new;
	char	*nb_shlvl;

	if (c == '+')
		data->shlvl++;
	else if (c == '-')
		data->shlvl--;
	nb_shlvl = ft_itoa(data->shlvl);
	new = ft_strjoin("SHLVL=", nb_shlvl);
	free(nb_shlvl);
	browse_data_var(new, data);
	free(new);
	return (0);
}

int	ft_cmp_line(char *history, char *str)
{
	int	i;

	i = jump_spaces(history, 0);
	if (ft_strncmp(&history[i], str, ft_strlen(str)) != 0)
		return (1);
	return (0);
}

char	*ft_shlvl(t_data *data, char *history, t_token **shlvl)
{	
	if (!history)
		printf("exit\n");
	if ((data->shlvl == 1 && history == NULL) || (history && data->shlvl == 1
			&& ft_message(history, "exit") == 0))
		return (NULL);
	else if (history && ft_message(history, "./minishell") == 0)
		change_shlvl(data, '+');
	else if (data->shlvl > 1 && ((history && ft_message(history,
					"exit") == 0) || history == NULL))
		ft_prev_envp(shlvl, data);
	if (!history)
		return ("history");
	return (history);
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
		if (g_global == 1)
			data->exit_status = 130;
		else if (g_global == 2){printf("quit\n");
			data->exit_status = 131;}
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
	close_fds(&data);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	if (data.tmp_fd > 0)
		close(data.tmp_fd);
	unlink ("pipe");
	return (0);
}
