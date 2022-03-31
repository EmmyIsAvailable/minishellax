/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:52:49 by eruellan          #+#    #+#             */
/*   Updated: 2022/03/31 14:07:46 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_data(t_data *data, char **envp)
{
	data->envp = envp;
	data->exit = 0;
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
		ft_putstr_fd("Error format : ./minishell\n", 1);
		return (1);
	}
	init_data(&data, envp);
	event_ctrl_c();
	while (data.exit == 0)
	{
		head = NULL;
		history = readline("> ");
		if (history == NULL) 
			break ;
		if (ft_parse(history, &head, &data) == 1)
			exit(EXIT_FAILURE);
//		printf("%d\n", data.exit);
	//	ft_print(head);
		add_history(history);
	//	if ((dispatch_builtins(head, &data)) == 1)
	//		ft_pipex(head, &data);
//		ft_lst_clear(&head, free);
	}
	return (0);
}
