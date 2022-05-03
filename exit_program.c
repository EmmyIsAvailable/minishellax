/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:19:27 by eruellan          #+#    #+#             */
/*   Updated: 2022/03/22 14:19:29 by eruellan         ###   ########.fr       */
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

int	event_ctrl_c(t_data *data)
{
	struct sigaction sa;
	struct sigaction sig_quit;

	sa.sa_handler = sig_int; 
	sa.sa_flags = 0;
	sig_quit.sa_flags = 0;
	sig_quit.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &sa, NULL) == 0)
	{
		data->exit_status = 130;
		return (1);
	}
	sigaction(SIGQUIT, &sig_quit, NULL);
	return (0);
}

int     ft_message_exit(char *history, char *str)
{
        int     i;
        int     vrai;

        vrai = 0;
        i = jump_spaces(history, 0);
        if (ft_strncmp(&history[i], str, ft_strlen(str)) != 0)
                return (1);
        i += ft_strlen(str);
        i = jump_spaces(history, i);
        while (ft_isdigit(history[i]))
        {
                vrai = 1;
                i++;
        }
        i = jump_spaces(history, i);
        if (history[i] != '\0' && vrai == 1)
        {
                printf("exit\n-bash: exit: too many arguments\n");
                return (1);
        }
        else if (!ft_isdigit(history[i]) && vrai == 0 && history[i] != '\0')
                printf("exit\n-bash: exit: numeric argument required\n");
        else if (history[i] == '\0')
                printf("exit\n");
        return (0);
}

