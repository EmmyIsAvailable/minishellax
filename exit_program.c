/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:19:27 by eruellan          #+#    #+#             */
/*   Updated: 2022/05/19 14:33:39 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int(int code)
{
	(void)code;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	return ;
}

int	event_ctrl_c(void)
{
	struct sigaction	sa;
	struct sigaction	sig_quit;

	sa.sa_handler = sig_int;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sig_quit.sa_flags = 0;
	sig_quit.sa_handler = SIG_IGN;
	sigemptyset(&sig_quit.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == 0)
		return (1);
	sigaction(SIGQUIT, &sig_quit, NULL);
	return (0);
}

int	ft_message(char *history, char *str)
{
	char	**tab;

	tab = ft_split_bis(history, "\f\n\r\t\v ");
	if (ft_strncmp(tab[0], str, ft_strlen(tab[0])) != 0)
		return (1);
	if (ft_strncmp(str, "./minishell", 11) == 0 && tab[1])
	{
		printf("minishell: %s: No such file or directory\n", tab[1]);
		return (1);
	}
	if (ft_strncmp(str, "exit", 4) == 0)
	{
		printf("exit\n");
		if (tab[1] && !check_exit_args(tab[1]) && tab[2])
			return (1);
	}
	free_tab(tab);
	return (0);
}

int	ft_exit_message(int i, t_token *cmd)
{
	if (i == 1)
	{
		printf("bash: exit: %s: numeric argument required\n", cmd->data);
		return (2);
	}
	if (i == 2)
	{
		printf("bash: exit: %s: too many arguments\n", cmd->data);
		return (1);
	}
	return (0);
}

int	ft_exit(t_token *cmd)
{
	int	i;

	i = -1;
	if (cmd->next)
	{
		while (cmd->next->data[++i])
		{
			if (i == 0 && cmd->next->data[i] == '-')
				i++;
			if (!ft_isdigit(cmd->next->data[i]))
				return (ft_exit_message(1, cmd->next));
		}
		if (cmd->next->next)
			return (ft_exit_message(2, cmd->next));
		if (ft_atoi(cmd->next->data) < 0)
			return (255);
		return (ft_atoi(cmd->next->data) % 256);
	}
	return (0);
}
