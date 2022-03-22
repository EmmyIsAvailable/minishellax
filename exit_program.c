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
}

void	event_ctrl_c(void)
{
	struct sigaction sa;
	
	sa.sa_handler = sig_int; 
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}
