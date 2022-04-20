/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:52:49 by eruellan          #+#    #+#             */
/*   Updated: 2022/04/14 14:41:50 by eruellan         ###   ########.fr       */
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
//	data->prev = NULL;
//	data->next = NULL;
	return (0);
}

t_data	*add_shlvl_envp(t_data *data)
{
	t_data	*new;

	new = NULL;
	init_envp(new, data->envp);
	new->shlvl = data->shlvl + 1;
//	new->prev = data;
//	new->next = NULL;
//	data->next = new;
	return (new);
}

int main(int ac, char **av, char **envp)
{
	char	*history;
	t_token	*head;
	t_data	data;
	t_data	*current;

	(void)av;
	history = NULL;
	current = NULL;
	if (ac != 1)
	{
		ft_putstr_fd("./minishell: too many arguments\n", 1);
		return (1);
	}
	init_envp(&data, envp);
	current = &data;
	event_ctrl_c();
	while (current->shlvl != -1)
	{
		printf("%d\n", current->shlvl);
		head = NULL;
		history = readline("> ");
		if ((current->shlvl == 1 && history == NULL) || (history && current->shlvl == 1 && ft_strncmp(history, "exit", 6) == 0))
		{
			printf("exit\n");
			break ;
		}
		else if (history && ft_strncmp(history, getenv("_"), ft_strlen(getenv("_")) + 1) == 0)
			current = add_shlvl_envp(current);
		else if (current->shlvl > 1 && ((history && ft_strncmp(history, "exit", 6) == 0) || history == NULL))
		{
			//current = current->prev; // et il faut free l'envp qu'on quitte
			//current.shlvl--;
			history = NULL;
			printf("exit\n");
		}
		if (history)
			if (ft_parse(history, &head, current))
				return (1);
		add_history(history);
	}
	return (0);
}
