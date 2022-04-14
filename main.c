/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:52:49 by eruellan          #+#    #+#             */
/*   Updated: 2022/04/14 12:28:02 by eruellan         ###   ########.fr       */
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
	return (0);
}

int main(int ac, char **av, char **envp)
{
	char	*history;
	t_data	data;
	t_token	*head;

	(void)av;
	history = NULL;
	if (ac != 1)
	{
		ft_putstr_fd("./minishell: too many arguments\n", 1);
		return (1);
	}
	init_envp(&data, envp);
	event_ctrl_c();
	data.exit = 1;
	while (data.exit != -1)
	{
		printf("statut %d\n", data.exit);
		head = NULL;
		history = readline("> ");
		if (data.exit == 1 && history == NULL)
			break ;
		else if (data.exit != 1 && history == NULL)
			displayOnTerm("exit/n");
		else if (data.exit == 1 && ft_strncmp(history, "exit", 6) == 0)
			break ;
		else if (ft_strncmp(history, "./minishell", 11) == 0)
			data.exit++;
		else if (data.exit > 1 && ft_strncmp(history, "exit", 6) == 0)
		{
			data.exit--;
			displayOnTerm("exit\n\0");
			//printf("%s\n)", (char *)NULL);
		}
		if (ft_parse(history, &head, &data))
			return (1);
		add_history(history);
	}
	return (0);
}
