/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:19:27 by eruellan          #+#    #+#             */
/*   Updated: 2022/06/09 14:28:32 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_global;

void	sig_int(int code)
{
	(void)code;
	write(1, "\n", 1);
	rl_on_new_line();
//	rl_replace_line("", 1);
	rl_redisplay();
	g_global = 1;
	return ;
}

int	event_ctrl_c(int i)
{
	if (i == 1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sig_int);
	}
	if (i == 2)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
	}
	if (i == 3)
	{
		signal(SIGINT, sig_int2);
	}
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
