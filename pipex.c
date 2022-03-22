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

int     main(int ac, char **av, char **envp)
{
        int     i;
        t_data data;
        int     status;

        i = 2;
        if (ac < 3)
                return (ft_error("Wrong number of arguments"));
        data.envp = envp;
        data.pipes[0] = data.pipe0;
        data.pipes[1] = data.pipe1;
        pipe(data.pipes[0]);
        if (fork() == 0)
        {
                dup2(data.pipes[0][1], 1);
                close(data.pipes[0][0]);
                ft_exec(av[1], &data);
        }
        close(data.pipes[0][1]);
        while (av[i + 1])
        {
                pipe(data.pipes[1]);
                if (fork() == 0)
                {
                        dup2(data.pipes[0][0], 0);
                        dup2(data.pipes[1][1], 1);
                        close(data.pipes[1][0]);
                        ft_exec(av[i], &data);
                }
                close(data.pipes[0][0]);
                close(data.pipes[1][1]);
                i++;
        }
        if (fork() == 0)
        {
                dup2(data.pipes[1][0], 0);
                ft_exec(av[i], &data);
        }
        close(data.pipes[1][0]);
        while (wait(&status) != -1) {};
        return (0);
}

