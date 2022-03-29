/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:31:26 by eruellan          #+#    #+#             */
/*   Updated: 2022/03/22 14:31:44 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait(t_data *data)
{
	pid_t	pid;
	int	wait_status;

	wait_status = 0;
	pid = 0;
	while (pid != -1)
	{
		pid = wait(&wait_status);
		if (pid == data->last_pid)
			return ;
	} 
}

int     ft_pipex(t_token *token, t_data *data)
{
	pid_t	pid;

        data->pipes[0] = data->pipe0;
        data->pipes[1] = data->pipe1;
        if (pipe(data->pipes[0]) == -1)
		return (1);
        pid = fork();
	if (pid == 0)
        {
                dup2(data->pipes[0][1], 0); 
                close(data->pipes[0][0]);
                if (dispatch_builtins(token, data) == 1)
			ft_exec(token, data);
        }
	else if (pid > 0)
		data->last_pid = pid;
        close(data->pipes[0][1]);
	return (ft_pipex_bis(token, data));
}

int	ft_pipex_bis(t_token *token, t_data *data)
{
	while (token->next && token->next->next)
       	{
		printf("while\n");
       	        pipe(data->pipes[1]);
       	        pid = fork();
		if (pid == 0)
       	        {
               	        dup2(data->pipes[0][0], 0);
               	        dup2(data->pipes[1][1], 0);
              		close(data->pipes[1][0]);
			ft_exec(token, data);
       		}
		else if (pid > 0)
			data->last_pid = pid;
               	close(data->pipes[0][0]);
              	close(data->pipes[1][1]);
		token = token->next;
       	}
	if (token->next)
        {
		pid = fork();
		if (pid == 0)
        	{
                	dup2(data->pipes[1][0], 0);
         	    	ft_exec(token->next, data);
        	}
		else if (pid > 0)
			data->last_pid = pid;
        	close(data->pipes[1][0]);
	}
	ft_wait(data);
        return (0);
}

