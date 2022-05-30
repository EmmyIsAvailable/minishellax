/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:19:27 by eruellan          #+#    #+#             */
/*   Updated: 2022/05/30 15:14:24 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_global;

void	sig_int(int code)
{
	(void)code;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	g_global = 1;
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
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sig_quit, NULL);
	return (0);
}

int	ft_message(char *history, char *str)
{
	char	**tab;

	tab = ft_split_bis(history, "\f\n\r\t\v ");
	if (!tab || ft_strncmp_len(tab[0], str, ft_strlen(str)) != 0)
	{
		if (tab)
			free_tab(tab);
		return (1);
	}
	if (ft_strncmp_len(tab[0], "./minishell", 11) == 0 && tab[1])
	{
		printf("minishell: %s: No such file or directory\n", tab[1]);
		free_tab(tab);
		return (1);
	}
	return (ft_message_bis(tab));
}

int	ft_message_bis(char **tab)
{
	if (ft_strncmp_len(tab[0], "exit", 4) == 0)
	{
		printf("exit\n");
		if (tab[1] && !check_exit_args(tab[1]) && tab[2])
		{
			free_tab(tab);
			return (1);
		}
	}
	free_tab(tab);
	return (0);
}

int	ft_exit_message(int i, t_heads **line)
{
	t_token	*cmd;

	cmd = (*line)->cmd;
	if (i == 1)
	{
		printf("bash: exit: %s: numeric argument required\n", cmd->next->data);
		clear_all_heads(line);	
		return (2);
	}
	if (i == 2)
	{
		printf("bash: exit: %s: too many arguments\n", cmd->next->data);
		clear_all_heads(line);
		return (1);
	}
	return (0);
}
