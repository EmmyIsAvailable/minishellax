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

void	event_ctrl_c(t_data *data)
{
	struct sigaction sa;
	struct sigaction sig_quit;
	
	sa.sa_handler = sig_int; 
	sa.sa_flags = 0;
	sig_quit.sa_flags = 0;
	sig_quit.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &sa, NULL) == 0)
		data->exit_status = 130;
	sigaction(SIGQUIT, &sig_quit, NULL);
}
