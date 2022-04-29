/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:52:49 by eruellan          #+#    #+#             */
/*   Updated: 2022/04/22 11:36:35 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	return (0);
}

int	init_envp(t_data *data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	data->envp = (char **)malloc(sizeof(char *)* (i + 1));
	if (!data->envp)
		return (1);
	i = 0;
	while (envp[i])
	{
		data->envp[i] = ft_strdup(envp[i]);
		if (!data->envp[i])
			return (1);
		i++;
	}
	data->envp[i] = NULL;
	data->shlvl = 1;
	return (0);
}

int	ft_cmp_line(char *history, char *str)
{
	int	i;

	i = 0;
	while (history[i] == ' ' || history[i] == '\n' || history[i] == '\f' || history[i] == '\r' || history [i] == '\t' || history[i] == '\v')
		i++;
	if (ft_strncmp(&history[i], str, ft_strlen(str)) != 0)
		return (1);
	i += ft_strlen(str);
	while (history[i] == ' ' || history[i] == '\n' || history[i] == '\f' || history[i] == '\r' || history [i] == '\t' || history[i] == '\v')
		i++;
	if (history[i] != '\0')
		return (1);
	return (0);
}

int main(int ac, char **av, char **envp)
{
	char	*history;
	t_token	*head;
	t_token	*shlvl;
	t_data	data;

	(void)av;
	history = NULL;
	shlvl = NULL;
	head = NULL;
	if (ac != 1)
	{
		ft_putstr_fd("./minishell: too many arguments\n", 1);
		return (1);
	}
	init_envp(&data, envp);
	event_ctrl_c();
	while (data.shlvl != -1)
	{
		head = NULL;
		history = readline("$> ");
		if ((data.shlvl == 1 && history == NULL) || (history && data.shlvl == 1 && ft_cmp_line(history, "exit") == 0))
		{
			printf("exit\n");
			break ;
		}
		else if (history && ft_cmp_line(history, "./minishell") == 0)
			data.shlvl++;
		else if (data.shlvl > 1 && ((history && ft_cmp_line(history, "exit") == 0) || history == NULL))
		{
			ft_prev_envp(shlvl, &data); // et il faut free l'envp qu'on quitte
			history = NULL;
			printf("exit\n");
		}
		if (history)
			if (ft_parse(history, &head, &data, &shlvl))
				return (1);
		add_history(history);
//		ft_print(shlvl);
	}
	return (0);
}
